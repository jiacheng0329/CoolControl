#ifndef MATHTOOL_H
#define MATHTOOL_H

#include <QPoint>
#include <QGraphicsItem>
#include <QGraphicsScene>


class MathTool
{
public:
    static void test();

    //测量、选择图元相关
    static QRectF creatBiggerRect(const QPointF& p1, const QPointF& p2, int dis = 3);
    static double calAngle(const QPointF& p1, const QPointF& p2, const QPointF& p3);


private:
    MathTool();

    static QPointF lineAbsorbRect(const QRectF &r, double width, const QPointF &lineCent, bool *is);
    static double isLineAbsorbRect(double rectHW, double rectXY
                            , double lineXY, double dist, bool *ok);




};

#endif // MATHTOOL_H
