#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QVector>
#include <QToolButton>

class ListButton : public QWidget
{
    Q_OBJECT

public:
    //explicit ListButton(QWidget *parent = nullptr);
    ListButton(QWidget *parent = nullptr, int num = 7);
    ~ListButton();

signals:
    void buttonChecked(int index, bool checked);

private slots:
    void onButtonChecked(int index, bool checked);

private:
    void initButtonList(int num);
    int  m_buttonNum;
    QVector<QToolButton *> m_button;
    QVector<QString> m_iconNormal;
    QVector<QString> m_iconChecked;
    QVector<QString> m_text;
    int m_sizeNormal;
    int m_sizeChecked;
};

#endif // LISTWIDGET_H
