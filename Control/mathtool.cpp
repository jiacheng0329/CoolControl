#include "mathtool.h"
#include <QDebug>

const double M_PI = 3.14;
void MathTool::test()
{
    qDebug() << "test";
}

QRectF MathTool::creatBiggerRect(const QPointF& p1, const QPointF& p2, int dis)
{
    if (dis < 1)
        dis = 1;
    double centX = (p1.x() + p2.x()) / 2;
    double centY = (p1.y() + p2.y()) / 2;
    double width = qAbs(p1.x() - p2.x());
    double height = qAbs(p1.y() - p2.y());
    QRectF newRect = QRectF(centX - width / 2 - dis, centY - height / 2 - dis, width + 2 * dis, height + 2 * dis);
    //qDebug() << p1 << p2 << centX << centY << width << height;
    return newRect;
}

double MathTool::calAngle(const QPointF& p1, const QPointF& p2, const QPointF& p3)
{
    double angle = 0;
    double theta = atan2(p2.x() - p1.x(), p2.y() - p1.y())
        - atan2(p2.x() - p3.x(), p2.y() - p3.y());
    qDebug() << theta;
    if (theta > M_PI) {
        theta -= 2 * M_PI;
    }
    if (theta < -M_PI) {
        theta += 2 * M_PI;
    }
    angle = abs(theta * 180.0 / M_PI);
    return angle;
}

//----------------------------
//fun-�ı��ѡ����
//case 1:������������
//case 2:������������
//---------------------------


MathTool::MathTool()
{

}


QPointF MathTool::lineAbsorbRect(const QRectF &r, double width, const QPointF &lineCent, bool *is)
{
    *is = false;
    bool vOk = false;
    bool hOk = false;

    double moveX = 0;
    double moveY = 0;
    double absorbWidth = width;
    moveY = isLineAbsorbRect(r.height(), r.y(), lineCent.y(), absorbWidth, &vOk);
    moveX = isLineAbsorbRect(r.width(), r.x(), lineCent.x(), absorbWidth, &hOk);

    if (vOk && hOk)
        *is = true;

    QPointF p = QPointF(moveX, moveY);
    return p;


}

double MathTool::isLineAbsorbRect(double rectHW, double rectXY, double lineXY, double dist, bool *ok)
{
    //bool ok = false;
    double hw = rectHW;
    double distEdge = rectXY - lineXY;
    bool isSmall = distEdge > 0 ? 0 : 1;//���������·�
    double move = 0;

    //���Ϸ�
    if (isSmall) {
        //ȫ�����Ϸ�����ý�
        if ((qAbs(distEdge) < dist + hw) && (qAbs(distEdge) > hw)) {
            move = qAbs(distEdge) - hw;
            *ok = false;
        //С�������Ϸ�
        } else if (qAbs(distEdge) < dist) {
            move = qAbs(distEdge);
            *ok = false;
        //�󲿷����Ϸ�
        } else if ((qAbs(distEdge) < hw) && (qAbs(distEdge) > hw - dist)){
            move = -qAbs(hw - qAbs(distEdge));
            *ok = false;
        //ȫ�����Ϸ������Զ
        } else {
            *ok = true;
        }
    //���·�
    } else {
        //ȫ�����·�����ý�
        if (qAbs(distEdge) < dist) {
            move = -qAbs(distEdge);
            *ok = false;
        //ȫ�����·������Զ
        } else {
            *ok = true;
        }

    }
    return move;
}


