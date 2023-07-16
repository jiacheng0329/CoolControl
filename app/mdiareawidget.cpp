#include "mdiareawidget.h"
#include "ui_mdiareawidget.h"
#include "pltshower.h"
#include "imagelabel.h"
#include "itemlist.h"
#include <QDir>
#include <QMdiArea>
#include <QProgressBar>

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


    ItemList *itemList = new ItemList(ItemList::LogList, this);
    itemList->addItemWidget();
    for (int i = 0; i < 15; ++i)
        itemList->addItemWidget();

    mdiArea->addSubWindow(itemList);
    itemList->setWindowTitle("Item列表");

    QProgressBar *progress = new QProgressBar();
    mdiArea->addSubWindow(progress);
    progress->setWindowTitle("实验");
    progress->setRange(0, 100);
    progress->setValue(50);
}

MdiAreaWidget::~MdiAreaWidget()
{

}
