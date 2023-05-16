#include "mdiareawidget.h"
#include "ui_mdiareawidget.h"
#include "pltshower.h"
#include "imagelabel.h"
#include <QDir>
#include <QMdiArea>

MdiAreaWidget::MdiAreaWidget(QWidget *parent) :
    QWidget(parent)
{
    QMdiArea *mdiArea = new QMdiArea(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 0, 10, 0);
    layout->addWidget(mdiArea);

    mdiArea->setViewMode(QMdiArea::TabbedView);

    PltShower *pltShower = new PltShower(this);
    pltShower->initPltFile(QDir::currentPath() + "/example/sun.plt");


    ImageLabel *imageLabel = new ImageLabel(this);
    QImage image(QDir::currentPath() + "/example/girl.jpg");
    imageLabel->setImage(image);
    imageLabel->initDraw();

    mdiArea->addSubWindow(pltShower);
    pltShower->setWindowTitle("PLT显示");
    mdiArea->addSubWindow(imageLabel);
    imageLabel->setWindowTitle("图片显示");



}

MdiAreaWidget::~MdiAreaWidget()
{

}
