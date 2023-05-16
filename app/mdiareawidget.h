#ifndef MDIAREAWIDGET_H
#define MDIAREAWIDGET_H

#include <QWidget>


class MdiAreaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MdiAreaWidget(QWidget *parent = nullptr);
    ~MdiAreaWidget();

private:

};

#endif // MDIAREAWIDGET_H
