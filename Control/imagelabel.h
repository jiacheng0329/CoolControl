#ifndef PREVIEWLABEL_H
#define PREVIEWLABEL_H

#include<QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QLabel>
#include <QDebug>

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    friend class PreviewDialog;
    ImageLabel(QWidget *parent = nullptr);
    void initDraw();
    void setImage(const QImage &image);

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);

private:
    QImage m_pdfImage;
    double m_scaleValue;
    bool m_isPressed;
    QPointF m_pressedPoint;
    QPointF m_drawPoint;
    QSize m_initSize;

    QColor m_backColor;
//    bool m_isInited;
};

#endif // PREVIEWLABEL_H
