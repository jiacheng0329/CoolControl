#include "listbutton.h"

#include <QDebug>
#include <QIcon>
#include <QToolButton>
#include <QVBoxLayout>
#include <QButtonGroup>

ListButton::ListButton(QWidget *parent, int num) :
    QWidget(parent),
    m_buttonNum(num), m_sizeNormal(30), m_sizeChecked(40)
{
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("ListButton QToolButton{border:0px solid red;margin:0px;}"//！防止点击时文字移动
                  "ListButton QToolButton:checked{background:rgb(105,105,105);}");

    m_iconNormal = {};
    m_iconChecked = {};
    m_text = {};

    connect(this, SIGNAL(buttonChecked(int, bool)), this, SLOT(onButtonChecked(int, bool)));
    initButtonList(m_buttonNum);

    //emit buttonChecked(0, true);
    //onButtonChecked(5, true);
}

ListButton::~ListButton()
{

}

void ListButton::onButtonChecked(int index, bool checked)
{
    if (index >= m_button.size())
        return;

    QToolButton *button = m_button.at(index);
    if (checked) {
        changeIconChecked(button, index);
    } else {
        changeIconNormal(button, index);
    }

}

void ListButton::initButtonList(int num)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 6, 0, 6);
    layout->setSpacing(12);

    for (int i = 0; i < num; ++i) {
        QToolButton *button = new QToolButton(this);
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setIconSize(QSize(m_sizeNormal, m_sizeNormal));
        changeIconNormal(button, i);
        changeText(button, i);

        button->setFixedSize(QSize(100, 62));
        button->setCheckable(true);
        button->setAutoExclusive(true);

        connect(button, &QToolButton::toggled, [=] {
            emit buttonChecked(i, button->isChecked());
        });

        m_button.push_back(button);
        layout->addWidget(button);

    }

}

void ListButton::changeIconNormal(QToolButton *button, int index)
{
    QString  iconNormal = index < m_iconNormal.size() ? m_iconNormal.at(index) : ":/Icons/gray-gift.svg";
    button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    button->setIconSize(QSize(m_sizeNormal, m_sizeNormal));
    button->setIcon(QIcon(iconNormal));
}

void ListButton::changeIconChecked(QToolButton *button, int index)
{
    QString iconChecked = index < m_iconChecked.size() ? m_iconChecked.at(index) : ":/Icons/orange-gift.svg";
    button->setToolButtonStyle(Qt::ToolButtonIconOnly);
    button->setIconSize(QSize(m_sizeChecked, m_sizeChecked));
    button->setIcon(QIcon(iconChecked));
}

void ListButton::changeText(QToolButton *button, int index)
{
    QString text = index < m_text.size() ? m_text.at(index) : "未定义";
    button->setText(text);
}

void ListButton::setText(const QVector<QString> &text)
{
    m_text = text;
    for (int index = 0; index < m_button.size(); ++index) {
        QToolButton *button = m_button.at(index);
        changeText(button, index);
    }
}

void ListButton::setIconChecked(const QVector<QString> &iconChecked)
{
    m_iconChecked = iconChecked;
    for (int index = 0; index < m_button.size(); ++index) {
        QToolButton *button = m_button.at(index);
        if (!button->isChecked())
            continue;
        changeIconChecked(button, index);
    }
}

void ListButton::setIconNormal(const QVector<QString> &iconNormal)
{
    m_iconNormal = iconNormal;
    for (int index = 0; index < m_button.size(); ++index) {
        QToolButton *button = m_button.at(index);
        if (button->isChecked())
            continue;
        changeIconNormal(button, index);
    }
}


