#ifndef CONTROLLISTWIDGET_H
#define CONTROLLISTWIDGET_H

#include <QWidget>
#include <QTreeWidget>

//struct StyleString {
//    QString light;
//    QString text;
//    QString back;
//    QString control;
//    QString hover;
//};

class TreeProperty : public QWidget
{
    Q_OBJECT

public:
    enum PropertyControl {
        PropertyButton = 0,
        PropertyEdit
    };
//    enum StyleColor {
//        StyleOrange = 0,
//        StyleRed
//    };
    explicit TreeProperty(QWidget *parent = nullptr);
    ~TreeProperty();

    void addItem(const QString &name, bool unfold = true);
    void insertButtonProperty(const QString &itemName, const QString &propName
                              , const QString &text = "执行");
    void insertEditProperty(const QString &itemName, const QString &propName
                            ,  const QString &text = "");
    void insertComboProperty(const QString &itemName, const QString &propName
                             ,  const QStringList &text);

signals:
    void checked(const QString &name, bool checked);
    void textChanged(const QString &name,  const QString &checked);
    void itemChanged(const QString &name, int index);

private:
    void initStyleSheet();

    QTreeWidget *m_treeWidget;
    QMap<QString, QTreeWidgetItem*>m_itemMap;
    //StyleColor m_styleColor;
};

#endif // CONTROLLISTWIDGET_H
