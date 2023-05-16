#include "pltshower.h"
#include <qfile.h>
#include <qtextstream.h>
#include <qdebug.h>
#include <qregularexpression.h>
#include <QtCore/qmath.h>
#include <mathtool.h>


#define MINIMUM_INCR   5

typedef struct
{
    double ruler_scale[16];
    int    subdivide[5];
}SPRulerMetric;

// Ruler metric for general use.
static SPRulerMetric const ruler_metric = {
    /*相邻刻度（显示数值）的差值*/{ 1, 2, 5, 10, 25, 50, 100, 250, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000 },
    /*单位刻度的刻度数*/{ 1, 5, 10, 50, 100 }
};

PltShower::PltShower(QWidget *parent)
    : QWidget(parent), m_backColor(Qt::gray)
{
    //setWindowTitle(QStringLiteral("PLT文件预览"));
    resize(600, 400);
    setMouseTracking(true);


    m_mode = FreeMode;
    m_sizeInit = true;

    m_scaleFactor = 1;
    m_mousePressed = false;
    m_horMoveDist = 0;
    m_verMoveDist = 0;

    m_lastPressedP = QPoint(0, 0);

    m_pressedNum = 0;
    m_distLineFact = 0;

    //loadPlt();

}

PltShower::~PltShower()
{}

void PltShower::setOperateMode(OperateMode mode)
{
    m_mode = mode;
}

void PltShower::restorePoint()
{
    m_firstPressedFactP = QPoint(0, 0);
    m_secendPressedFactP = QPoint(0, 0);
}

void PltShower::initPltFile(const QString&file)
{
    qDebug() << file;
    m_pltFile = file;
    m_mode = FreeMode;
    m_sizeInit = true;

    m_scaleFactor = 1;
    m_mousePressed = false;
    m_horMoveDist = 0;
    m_verMoveDist = 0;

    m_lastPressedP = QPoint(0, 0);

    m_pressedNum = 0;
    m_distLineFact = 0;
    loadPlt();
    update();
}

void PltShower::savePltAfterChange()
{
    //m_pointOriginalList = m_pointWorkedList;
    QFile file(m_pltFile);
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
        return;
    QTextStream stream(&file);

    bool isStart = false;
    QString pltText;
    pltText.append("IN;SP1");
    foreach(auto p, m_pointWorkedList) {
        if (p.x() < 0) {
            //(-1,-1)一次切割的开始，下一个点为起点PU....
            isStart = true;
            //去掉多余的","
            if (pltText.at(pltText.size() - 1) == ",")
                pltText = pltText.left(pltText.size() - 1);
            continue;
        }
        else {
            //起点
            if (isStart) {
                pltText.append(";PU" + QString::number(p.x() * 40) + "," + QString::number(p.y() * 40) + ";PD");
                isStart = false;
            }
            //其它点
            else
                pltText.append(QString::number(p.x() * 40) + "," + QString::number(p.y() * 40) + ",");
        }

    }
    pltText.append(";PU;SP0;PG;");
    stream << pltText;
    file.close();
    //qDebug() << pltText;
}

void PltShower::drawPointGather(QPainter *painter)
{
    if (!m_pointWorkedList.size())
        return;

    painter->save();
    //绘制轮廓点
    QPoint moveDist(m_horMoveDist, m_verMoveDist);
    painter->setPen(QPen(QBrush(Qt::red), 3));

    m_pointDrawedList.clear();
    foreach(auto p, m_pointWorkedList) {
        QPoint pointDrawed = p * m_scaleFactor + moveDist;
        if (p.x() > 0) {
            m_pointDrawedList.push_back(pointDrawed);
            painter->drawPoint(pointDrawed);
        }
        else {
            m_pointDrawedList.push_back(QPoint(-1, -1));
        }

    }

    //点连线
    QPoint firstP;
    QPoint curP;
    QPoint nextP;
    painter->setPen(QPen(QBrush(Qt::blue), 1));
    for (int i = 0; i < m_pointWorkedList.size() - 1; ++i) {
        if (m_pointWorkedList.at(i).x() < 0) {
            firstP = m_pointWorkedList.at(i + 1);
            continue;
        }

        if (m_pointWorkedList.at(i + 1).x() < 0) {
            painter->drawLine(m_pointWorkedList.at(i) * m_scaleFactor + moveDist
                              , firstP * m_scaleFactor + moveDist);
            continue;
        }

        painter->drawLine(m_pointWorkedList.at(i) * m_scaleFactor + moveDist
                          , m_pointWorkedList.at(i + 1) * m_scaleFactor + moveDist);
    }

    painter->restore();
}

void PltShower::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);
    if (m_sizeInit) {
        m_horRuler = { RulerBarType::HorRuler, 0, (double)width() };
        m_verRuler = { RulerBarType::VorRuler, 0, (double)height() };
        m_sizeInit = false;
    }

    int w = width();
    int h = height();
    int horPointNum = w / 10;
    int verPointNum = h / 10;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    //背景点
    painter.setBrush(m_backColor);
    painter.drawRect(this->rect());

    for (int i = 1; i <= horPointNum; ++i) {
        for (int j = 1; j <= verPointNum; ++j) {
            //painter.drawPoint(i * 10, j * 10);
        }
    }

    drawPointGather(&painter);
    drawRuleBar(&painter, m_horRuler);
    drawRuleBar(&painter, m_verRuler);

    //painter.drawLine(QPoint(0, m_pressedP.y()), QPoint(width(), m_pressedP.y()));
    //painter.drawLine(QPoint(m_pressedP.x(), 0), QPoint(m_pressedP.x(), height()));

    drawMeasureLine(&painter);

    int index = 0;
    foreach(auto p, m_pointDrawedList) {
        if (MathTool::creatBiggerRect(p, p).contains(m_moveP))
            painter.drawEllipse(p, 5, 5);
        ++index;
    }

    /*刻度尺上鼠标实时位置*/
    painter.setPen(QPen(Qt::red));
    painter.drawLine(QPoint(0, m_moveP.y()), QPoint(20, m_moveP.y()));
    painter.drawLine(QPoint(m_moveP.x(), 0), QPoint(m_moveP.x(), 20));

    painter.fillRect(QRectF(0, 0, 10, 10), Qt::white);
}

void PltShower::wheelEvent(QWheelEvent* event)
{
    QWidget::wheelEvent(event);

    if (event->delta() > 0)
        zoomIn();
    else
        zoomOut();

    /*更新右上角鼠标位置*/
    m_mouseFactPos = QPointF(event->pos() - QPoint(m_horMoveDist, m_verMoveDist)) / m_scaleFactor;
    emit posChanged(m_mouseFactPos.x(), m_mouseFactPos.y());
}

void PltShower::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);

    if (event->button() == Qt::LeftButton) {
        m_pressedP = event->pos();
        m_lastPressedP = event->pos();
        m_mousePressed = true;

        if (m_mode == MeasureMode) {
            m_pressedNum == 2 ? m_pressedNum = 1 : ++m_pressedNum;
            if (m_pressedNum == 1) {
                m_firstPressedFactP = event->pos() / m_scaleFactor;

            }
            else if (m_pressedNum == 2) {
                m_secendPressedFactP = event->pos() / m_scaleFactor;

                double disX = m_secendPressedFactP.x() - m_firstPressedFactP.x();
                double disY = m_secendPressedFactP.y() - m_firstPressedFactP.y();
                m_distLineFact = sqrt(disX * disX + disY * disY);
            }
        }
    }


    /*中键点击删除点*/
    if (event->button() == Qt::MidButton) {
        int index = 0;
        foreach(auto p, m_pointDrawedList) {
            if (MathTool::creatBiggerRect(p, p).contains(m_moveP))
                m_pointWorkedList.removeAt(index);
            ++index;
        }
    }

}

void PltShower::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);
    if (m_mousePressed && m_mode == FreeMode) {
        //一次移动的距离-像素
        int horMove = (event->pos().x() - m_lastPressedP.x());
        int verMove = (event->pos().y() - m_lastPressedP.y());

        //总移动的距离-像素
        m_horMoveDist += horMove;
        m_verMoveDist += verMove;

        //刻度尺的范围-物理
        m_horRuler.upper -= horMove / m_scaleFactor;
        m_horRuler.lower -= horMove / m_scaleFactor;

        m_verRuler.upper -= verMove / m_scaleFactor;
        m_verRuler.lower -= verMove / m_scaleFactor;

        m_lastPressedP = event->pos();
    }
    m_moveP = event->pos();

    m_mouseFactPos = QPointF(event->pos() - QPoint(m_horMoveDist, m_verMoveDist)) / m_scaleFactor;
    emit posChanged(m_mouseFactPos.x(), m_mouseFactPos.y());

    update();

}

void PltShower::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);

    m_mousePressed = false;
}

void PltShower::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    m_horRuler.upper = (m_horRuler.lower + width()) * m_scaleFactor;
    m_verRuler.upper = (m_verRuler.lower + height()) * m_scaleFactor;;

}

void PltShower::drawMeasureLine(QPainter* painter)
{
    if (m_mode == MeasureMode) {
        QPoint m_firstPressedPixP = m_firstPressedFactP * m_scaleFactor;
        QPoint m_secendPressedPixP = m_secendPressedFactP * m_scaleFactor;

        if (m_pressedNum == 1) {
            painter->drawLine(QLine(m_firstPressedPixP, m_moveP));
            painter->drawRect(MathTool::creatBiggerRect(m_firstPressedPixP, m_firstPressedPixP));
            painter->drawRect(MathTool::creatBiggerRect(m_moveP, m_moveP));


        }
        else if (m_pressedNum == 2) {
            painter->drawLine(QLine(m_firstPressedPixP, m_secendPressedPixP));
            painter->drawRect(MathTool::creatBiggerRect(m_firstPressedPixP, m_firstPressedPixP));
            painter->drawRect(MathTool::creatBiggerRect(m_secendPressedPixP, m_secendPressedPixP));

            painter->drawText(m_firstPressedPixP + QPoint(2, -2), QString::number(m_distLineFact));

        }

    }
}

void PltShower::drawRuleBar(QPainter* painter, const RulerBar& ruler)
{
    int i = 0;
    double start = 0, end = 0, cur = 0;
    int pos = 0;
    int width = 0, height = 0;
    double upper = ruler.upper;
    double lower = ruler.lower;

    if (upper == lower) return;
    double increment = 0;//单位刻度对应的像素
    int idealLength = 0;

    if (ruler.type == RulerBarType::HorRuler) {
        width = this->width();
        height = 10;
        increment = (double)width / (upper - lower);
        painter->drawLine(QPoint(0, 0), QPoint(width, 0));

    } else if (ruler.type == RulerBarType::VorRuler){
        width = 10;
        height = this->height();
        increment = (double)height / (upper - lower);
        painter->drawLine(QPoint(0, 0), QPoint(0, height));
    }

    int scale;//相邻显示数值de差1-100000
    QFontMetrics fm(font());
    int digitHeight = fm.height();

    int textSize = QString::number(upper - lower).size() * digitHeight + 1;

    for (scale = 0; scale < sizeof(ruler_metric.ruler_scale) /
         sizeof(ruler_metric.ruler_scale[0]); scale++)
        //缩放时取到合适的值，放大到最大时取1
        if (ruler_metric.ruler_scale[scale] * fabs(increment) > 2 * textSize)
            break;
    //缩小到最小时，取100000
    if (scale == sizeof(ruler_metric.ruler_scale))
        scale = sizeof(ruler_metric.ruler_scale) - 1;

    int length = 0;
    //qDebug() << "scale->" << scale;
    for (i = sizeof(ruler_metric.subdivide) / sizeof(ruler_metric.subdivide[0]) - 1; i >= 0; i--) {
        double subd_incr;//一小格对应的刻度宽（物理单位）
        if (scale == 1 && i == 1)
            subd_incr = 1.0;
        else
            subd_incr = ((double)ruler_metric.ruler_scale[scale] /
                         (double)ruler_metric.subdivide[i]);

        //一格对应的像素宽小于最小值就跳过，画下一个，从密到疏
        if (subd_incr * fabs(increment) <= MINIMUM_INCR)
            continue;

        if (ruler.type == RulerBarType::HorRuler) {
            idealLength = height / (i + 1) - 1;
        }
        else if (ruler.type == RulerBarType::VorRuler) {
            idealLength = width / (i + 1) - 1;

        }

        if (idealLength > ++length)
            length = idealLength;

        if (lower < upper) {
            start = floor(lower / subd_incr) * subd_incr;
            end = ceil(upper / subd_incr) * subd_incr;
        }
        else
        {
            start = floor(upper / subd_incr) * subd_incr;
            end = ceil(lower / subd_incr) * subd_incr;
        }
        int tick_index = 0;
        for (cur = start; cur <= end; cur += subd_incr) {
            pos = int(qRound((cur - lower) * increment + 1e-12));
            if (ruler.type == RulerBarType::HorRuler) {
                painter->drawLine(QPoint(pos, 0), QPoint(pos, length));
            }
            else if (ruler.type == RulerBarType::VorRuler) {
                painter->drawLine(QPoint(0, pos), QPoint(length, pos));

            }

            double label_spacing_px = fabs(increment * (double)ruler_metric.ruler_scale[scale] / ruler_metric.subdivide[i]);
            if (i == 0 &&
                    (label_spacing_px > 6 * digitHeight || tick_index % 2 == 0 || cur == 0) &&
                    (label_spacing_px > 3 * digitHeight || tick_index % 4 == 0 || cur == 0))
            {
                if (ruler.type == RulerBarType::HorRuler) {
                    painter->drawText(QPoint(pos + 5, 10), QString::number(cur));
                }
                else if (ruler.type == RulerBarType::VorRuler) {
                    painter->drawText(QPoint(5, pos + 10), QString::number(cur));

                }

            }
            tick_index++;
        }
    }


}

void PltShower::zoomIn()
{
    //if ((m_scaleFactor > 10))
    //	return;

    m_scaleFactor *= 1.05;

    m_horRuler.upper *= 1 / 1.05;
    m_horRuler.lower *= 1 / 1.05;
    m_verRuler.upper *= 1 / 1.05;
    m_verRuler.lower *= 1 / 1.05;
    update();
}

void PltShower::zoomOut()
{
    //if ((m_scaleFactor < 0.1))
    //	return;

    m_scaleFactor *= 1 / 1.05;

    m_horRuler.upper *= 1.05;
    m_horRuler.lower *= 1.05;
    m_verRuler.upper *= 1.05;
    m_verRuler.lower *= 1.05;
    update();
}

int PltShower::initRulerBar()
{
    m_horRuler = { RulerBarType::HorRuler, 0, (double)width() };
    m_verRuler = { RulerBarType::VorRuler, 0, (double)height() };
    return 0;
}

bool PltShower::loadPlt()
{
    m_scaleFactor = 1;

    QFile file(m_pltFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream txt(&file);
    QString content = txt.readAll();

    QStringList stringList;
    QRegularExpression rx;
    QRegularExpressionMatch match;
    QString matched;

    //读取所有下刀路径字符串
    rx.setPattern("PU[0-9].*?;.*?;");
    QRegularExpressionMatchIterator iter;
    iter = rx.globalMatch(content);
    while (iter.hasNext())
    {
        match = iter.next();
        matched = match.captured(0);
        stringList.append(matched);
    }

    //遍历每一次下刀路径
    rx.setPattern("\\d{2,}[;,]");
    m_pointWorkedList.clear();
    foreach(auto string, stringList) {
        m_pointWorkedList.append(QPoint(-1, -1));
        iter = rx.globalMatch(string);

        bool isX = true;
        int x = 0;
        while (iter.hasNext())
        {
            match = iter.next();
            matched = match.captured(0);
            matched = matched.left(matched.size() - 1);

            isX ? (x = matched.toInt() / 40) : (m_pointWorkedList.append(QPoint(x, matched.toInt() / 40)));
            isX = !isX;
        }
    }
    m_pointWorkedList.append(QPoint(-1, -1));
    //m_pointOriginalList = m_pointWorkedList;

    return true;
}
