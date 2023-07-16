#include "treeProperty.h"

#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QListView>
#include <QDebug>
#include <QHeaderView>

//StyleString styleOrange = {"rgb(247,105,0)", "rgb(210,210,210)", "rgb(67,68,69)"
//                    , "rgb(40,40,40)",  "rgb(50,50,50)"};
//StyleString style2 = {};
//StyleString style3 = {};

TreeProperty::TreeProperty(QWidget *parent) :
    QWidget(parent)
{
    setMinimumWidth(180);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0,0, 0);
    m_treeWidget = new QTreeWidget(this);
    layout->addWidget(m_treeWidget);

    m_treeWidget->setColumnCount(2);
    m_treeWidget->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_treeWidget->header()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_treeWidget->header()->setMinimumWidth(200);

    m_treeWidget->setHeaderHidden(true);

   // m_styleColor = StyleOrange;
    initStyleSheet();

}

TreeProperty::~TreeProperty()
{

}

void TreeProperty::addItem(const QString &name, bool unfold)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    m_treeWidget->addTopLevelItem(item);
    item->setText(0, name);
    item->setExpanded(unfold);

    m_itemMap.insert(name, item);
}

void TreeProperty::insertButtonProperty(const QString &itemName, const QString &propName,  const QString &text)
{
    QTreeWidgetItem *item = m_itemMap.value(itemName);
    QTreeWidgetItem *property = new QTreeWidgetItem(item);
    property->setText(0, propName);

    QPushButton *button = new QPushButton(text, this);
    button->setFixedHeight(25);
    button->setCheckable(true);
    m_treeWidget->setItemWidget(property, 1, button);

}

void TreeProperty::insertEditProperty(const QString &itemName, const QString &propName, const QString &text)
{
    QTreeWidgetItem *item = m_itemMap.value(itemName);
    QTreeWidgetItem *property = new QTreeWidgetItem(item);
    property->setText(0, propName);

    QLineEdit *edit = new QLineEdit(text, this);
    edit->setFixedHeight(25);
    m_treeWidget->setItemWidget(property, 1, edit);
}

void TreeProperty::insertComboProperty(const QString &itemName, const QString &propName, const QStringList &list)
{
    QTreeWidgetItem *item = m_itemMap.value(itemName);
    QTreeWidgetItem *property = new QTreeWidgetItem(item);
    property->setText(0, propName);

    QComboBox *combo = new QComboBox(this);
    combo->addItems(list);
    combo->setFixedHeight(25);
    combo->setView(new  QListView());
    m_treeWidget->setItemWidget(property, 1, combo);
}

void TreeProperty::initStyleSheet()
{
//    QString styleSheet("*{color:[text];background: [back];}"
//                  "QTreeView::branch{padding:3px;padding-bottom:10px;}"
//                  "QTreeView::branch:open:has-children{image:url(:/Icons/gray-down.svg);}"
//                  "QTreeView::branch:closed:has-children{image:url(:/Icons/gray-right.svg);}"
//                  "QTreeView::branch:open:has-children:hover{image:url(:/Icons/orange-down.svg);}"
//                  "QTreeView::branch:closed:has-children:hover{image:url(:/Icons/orange-right.svg);}"
//                  //"QTreeWidget::branch:!has-children{}"

//                  "QTreeWidget{outline:0px;background: [back];border:noe;padding:10px;}"
//                  "QTreeView::item{height:25px;margin-bottom:5px;color:[text];}"
//                  "QTreeView::item{border-bottom:1px solid transparent;}"
//                  "QTreeView::item:hover{color:[text];border-bottom:1px solid [light]"
//                                        ";background: [hover];}"
//                  "QTreeView::item:selected{color:rgb(210,210,210);border-bottom:1px solid [hover]"
//                                        ";background: [hover];}"

//                  "QPushButton{background:[control];border:1px solid rgb(105,105,105);}"
//                  "QPushButton:focus{background:[control];border:1px solid [light];}"
//                  "QLineEdit{background:[control];border:1px solid rgb(105,105,105);}"
//                  "QLineEdit:hover{background:[control];border:1px solid [light];}"

//                  "QComboBox{background:[control];border:1px solid rgb(105,105,105);}"
//                  "QComboBox:checked{background:[control];border:1px solid [light];}"
//                  "QComboBox QAbstractItemView {background:[control];outline: 0px;border:1px solid [light];}"
//                  "QComboBox QAbstractItemView::item{height:25px;}"
//                  "QComboBox QAbstractItemView::item:hover{background:rgb(105,105,105);}"
//                  "QComboBox QAbstractItemView::item:selected{background:rgb(105,105,105);}"

//                  "QScrollBar:vertical{margin-left:8px;width:16px;}"
//                  "QScrollBar::handle:vertical{background:rgb(105,105,105);border-radius:4px;}"
//                  "QScrollBar::sub-line:vertical{background:transparent;}"
//                  "QScrollBar::add-line:vertical{background:transparent;}"
//                  "QScrollBar::sub-page:vertical{background:transparent;}"
//                  "QScrollBar::add-page:vertical{background:transparent;}");

//    StyleString s;
//    switch (m_styleColor) {
//    case 0:
//        s = styleOrange;
//        break;
//    default :
//        break;
//    }


//    styleSheet.replace("[light]", s.light);
//    styleSheet.replace("[text]", s.text);
//    styleSheet.replace("[back]", s.back);
//    styleSheet.replace("[control]", s.control);
//    styleSheet.replace("[hover]", s.hover);

//    setStyleSheet(styleSheet);
}
