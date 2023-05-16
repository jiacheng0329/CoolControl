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
    setStyleSheet("*{color:rgb(210,210,210);}"
                  "ListButton{background-color:rgb(67,68,69);}"
                  "QToolButton{background:rgb(67,68,69);"
                  "border:0px solid red;"
                  "margin:0px;}"//！！！！！！！！防止点击时文字移动
                  "QToolButton:checked{background:rgb(105,105,105);}");

    m_iconNormal = {":/Icons/gray-broken.svg", ":/Icons/gray-image.svg"};
    m_iconChecked = {":/Icons/orange-broken.svg", ":/Icons/orange-image.svg"};
    m_text = {"点集显示", "图片显示"};

    connect(this, SIGNAL(buttonChecked(int, bool)), this, SLOT(onButtonChecked(int, bool)));
    initButtonList(m_buttonNum);
}

ListButton::~ListButton()
{

}

void ListButton::onButtonChecked(int index, bool checked)
{
    QToolButton *button;
    QString iconNormal, iconChecked, text;
    if (m_button.at(index)) {
         button = m_button.at(index);
         iconNormal = index < m_iconNormal.size() ? m_iconNormal.at(index) : ":/Icons/gray-gift.svg";
         iconChecked = index < m_iconChecked.size() ? m_iconChecked.at(index) : ":/Icons/orange-gift.svg";
    }

    if (checked) {
        button->setToolButtonStyle(Qt::ToolButtonIconOnly);
        button->setIconSize(QSize(m_sizeChecked, m_sizeChecked));
        button->setIcon(QIcon(iconChecked));
    } else {
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setIconSize(QSize(m_sizeNormal, m_sizeNormal));
        button->setIcon(QIcon(iconNormal));
    }

}

void ListButton::initButtonList(int num)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 6, 0, 6);
    layout->setSpacing(12);

    for (int i = 0; i < num; ++i) {
        QString text = i < m_text.size() ? m_text.at(i) : "未定义";
        QString iconNormal = i < m_iconNormal.size() ? m_iconNormal.at(i) : ":/Icons/gray-gift.svg";
        QToolButton *button = new QToolButton(this);

        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setText(text);
        button->setIconSize(QSize(m_sizeNormal, m_sizeNormal));
        button->setIcon(QIcon(iconNormal));
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


