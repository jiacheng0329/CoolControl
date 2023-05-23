#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>


class ItemList : public QWidget
{
    Q_OBJECT
public:
    enum ListType {
        LogList = 0,
        DataList
    };
    explicit ItemList(QWidget *parent = nullptr);
    ItemList(ListType type, QWidget *parent = nullptr);

    void addItemWidget();

signals:

private:
    QListWidget *m_itemList;
    ListType m_type;

};

#endif // ITEMLIST_H
