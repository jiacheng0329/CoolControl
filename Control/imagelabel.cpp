#include "imagelabel.h"

ImageLabel::ImageLabel(QWidget *parent) : QLabel(parent), m_backColor(Qt::gray)
{
    m_scaleValue = 1;
    m_isPressed = false;

}

void ImageLabel::setImage(const QImage &image) {
    m_pdfImage = image;
}

void ImageLabel::initDraw()
{
    double scaleW = 1.0 * m_pdfImage.width() / width();
    double scaleH = 1.0 * m_pdfImage.height() / height();
    double scale = qMax(scaleH, scaleW);
    m_initSize = QSize(m_pdfImage.width() / scale, m_pdfImage.height() / scale);
    m_drawPoint = QPointF(width() / 2 - m_pdfImage.width() / scale / 2
                          , height() /2 - m_pdfImage.height() / scale / 2);
    //qDebug() << m_drawPoint << size() << m_pdfImage.size() << scale << m_pdfImage.width() / width();

}

void ImageLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);

    initDraw();

}

void ImageLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainter painter(this);
    painter.setBrush(m_backColor);
    painter.drawRect(this->rect());

    painter.drawPixmap(m_drawPoint, QPixmap::fromImage(m_pdfImage.scaled(width() * m_scaleValue
                                                                         , height() * m_scaleValue
                                                                         , Qt::KeepAspectRatio)));
}

void ImageLabel::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << "mousemove";
    QLabel::mouseMoveEvent(event);
    if (m_isPressed) {
        m_drawPoint = event->pos() - m_pressedPoint + m_drawPoint;
        m_pressedPoint = event->pos();
        update();
    }
}

void ImageLabel::mousePressEvent(QMouseEvent *event)
{
    QLabel::mousePressEvent(event);

    m_isPressed = true;
    m_pressedPoint = event->pos();
}

void ImageLabel::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);
    m_isPressed = false;
}

void ImageLabel::wheelEvent(QWheelEvent *event)
{
    QLabel::wheelEvent(event);
    double scale = m_scaleValue;

    if (event->delta() > 0 && m_scaleValue <10) {
        m_scaleValue *= 1.1;
    } else if (event->delta() < 0 && m_scaleValue >0.1){
        m_scaleValue *= 0.9;
    } else {
        return;
    }

    double scaleRatio = m_scaleValue / scale;
    QRectF rectPixmap(m_drawPoint.x(), m_drawPoint.y()
                      , m_initSize.width() * scale, m_initSize.height() * scale);

    //qDebug() << "old draw point " << m_drawPoint << scale << m_scaleValue;

    if (rectPixmap.contains(event->pos())) {
        double x = event->pos().x() - ((event->pos().x() - m_drawPoint.x()) * scaleRatio);
        double y = event->pos().y() - ((event->pos().y() - m_drawPoint.y()) * scaleRatio);
        m_drawPoint = QPointF(x, y);
    } else {
        double x = m_drawPoint.x() - (this->width() * (m_scaleValue - scale)) / 2;
        double y = m_drawPoint.y() - (this->height() * (m_scaleValue - scale)) / 2;
        m_drawPoint = QPointF(x, y);qDebug() << "new draw point " << event->pos() << rectPixmap << m_pdfImage.size();
    }
    update();


}
