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

    void setIconNormal(const QVector<QString> &iconNormal);
    void setIconChecked(const QVector<QString> &iconChecked);
    void setText(const QVector<QString> &text);

signals:
    void buttonChecked(int index, bool checked);

private slots:
    void onButtonChecked(int index, bool checked);

private:
    void initButtonList(int num);
    void changeIconNormal(QToolButton *btn, int index);
    void changeIconChecked(QToolButton *btn, int index);
    void changeText(QToolButton *btn, int index);
    int  m_buttonNum;
    QVector<QToolButton *> m_button;
    QVector<QString> m_iconNormal;
    QVector<QString> m_iconChecked;
    QVector<QString> m_text;
    int m_sizeNormal;
    int m_sizeChecked;
};

#endif // LISTWIDGET_H
