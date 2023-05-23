#include "itemlist.h"
#include <QVBoxLayout>
#include <QListWidget>
#include <QScroller>
#include "dataitem.h"

ItemList::ItemList(QWidget *parent) : QWidget(parent)
{

}

ItemList::ItemList(ItemList::ListType type, QWidget *parent) : QWidget(parent), m_type(type)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    m_itemList = new QListWidget(this);
    m_itemList->setSpacing(2);
    layout->addWidget(m_itemList);

    setStyleSheet("*{color:rgb(210,210,210);}"
              "QListWidget{background:rgb(67,68,69);outline: 0px;}"
              "QListWidget::item{border-bottom:1px solid transparent;height:30px;}"
              "QListWidget::item:hover{border-bottom:1px solid rgb(247,105,0);background: rgb(50,50,50);}"
              "QListWidget::item:selected{border-bottom:1px solid transparent;background: rgb(50,50,50);}"

              "QLineEdit{background:rgb(40,40,40);border:1px solid rgb(105,105,105);}"
              "QLineEdit:hover{background:rgb(40,40,40);border:1px solid rgb(247,105,0);}"
              "QPushButton{border:none;padding:8px;image:url(:/Icons/gray-rotate.svg);}"
              "QPushButton:hover{image:url(:/Icons/orange-rotate.svg);}"

              "QScrollBar:vertical{width:8px;}"
              "QScrollBar::handle:vertical{background:rgb(105,105,105);border-radius:4px;}"
              "QScrollBar::sub-line:vertical{background:transparent;}"//箭头
              "QScrollBar::add-line:vertical{background:transparent;}"
              "QScrollBar::sub-page:vertical{background:transparent;}"//滑动条
              "QScrollBar::add-page:vertical{background:transparent;}"
                  );
}

void ItemList::addItemWidget()
{
    QListWidgetItem *item = new QListWidgetItem(m_itemList);
//    item->setSizeHint(QSize(100, 30));

    switch (m_type) {
    case 0 : {
        DataItem *dataItem = new DataItem("电流电流", "25.0", m_itemList);
        m_itemList->setItemWidget(item, dataItem);
        break;
    }
    case 1: {
        DataItem *dataItem = new DataItem("电流", "25.0", m_itemList);
        m_itemList->setItemWidget(item, dataItem);
        break;
    }
    default :
        break;
    }





}

