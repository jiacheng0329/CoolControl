#pragma once

#include <QWidget>
#include <qpainter.h>
#include <QWheelEvent>
#include "ui_PltShower.h"

//onMeasureBtnClicked
//	ui.widget->setOperateMode(PltShower::MeasureMode);

//onFreeBtnClicked
//	ui.widget->setOperateMode(PltShower::FreeMode);
//	ui.widget->restorePoint();
//	ui.widget->update();

//onSaveBtnClicked
//	ui.widget->saveChangedPlt();

//onPosChanged
//	ui.pos->setText(QStringLiteral("(%1, %2)").arg(QString::number(x, 'f', 2), QString::number(y, 'f', 2)));

//init
//	ui.widget->setPltFile(global::g_rootDirectory + "/123457.plt");


enum RulerBarType {
	HorRuler = 0, 
	VorRuler
};

struct RulerBar {
	RulerBarType type;
	double lower;
	double upper;
};
class PltShower : public QWidget
{
	Q_OBJECT

public:
	enum OperateMode {
		FreeMode = 0,
		MeasureMode
	};
	PltShower(QWidget *parent = nullptr);
	~PltShower();

	void setOperateMode(OperateMode mode);
	void restorePoint();
    void initPltFile(const QString&);
    void savePltAfterChange();

protected:
	void paintEvent(QPaintEvent* event);
	void wheelEvent(QWheelEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void resizeEvent(QResizeEvent *event);

signals:
	void posChanged(double, double);

private slots:
	bool loadPlt();

private:

	void drawMeasureLine(QPainter* p);
	void drawPointGather(QPainter *p);

    int initRulerBar();
	void drawRuleBar(QPainter* p, const RulerBar&);

	void zoomIn();
	void zoomOut();


	QString m_pltFile;
	QList<QPoint>m_pointDrawedList;
	QList<QPoint>m_pointWorkedList;
	//QList<QPoint>m_pointOriginalList;
	bool m_sizeInit;
	QSize m_lastSize;
	QPointF m_mouseFactPos;
	/*缩放*/
	double m_scaleFactor;
	/*移动*/
	bool m_mousePressed;
	int m_horMoveDist;
	int m_verMoveDist;
	QPoint m_lastPressedP;
	QPoint m_pressedP;
	/*刻度*/
	RulerBar m_horRuler;
	RulerBar m_verRuler;
	/*操作*/
	OperateMode m_mode;
	/*测量*/
	QPoint m_firstPressedFactP;
	QPoint m_secendPressedFactP;
	QPoint m_moveP;
	int m_pressedNum;
	double m_distLineFact;

    QColor m_backColor;
	
};
