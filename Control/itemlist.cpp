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
    m_itemList->setSelectionMode(QAbstractItemView::ExtendedSelection);

    setStyleSheet("ItemList QPushButton{background:transparent;border:none;padding:8px;image:url(:/Icons/gray-rotate.svg);}"
                  "ItemList QPushButton:hover{background:transparent;image:url(:/Icons/orange-rotate.svg);}"
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

