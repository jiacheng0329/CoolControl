#include "dataitem.h"
#include "ui_dataitem.h"
#include <QDateTime>

DataItem::DataItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataItem)
{
    ui->setupUi(this);
}

DataItem::DataItem(const QString &name, const QString &value, QWidget *parent)
    : QWidget(parent), ui(new Ui::DataItem), m_name(name), m_value(value)
{
    ui->setupUi(this);
    QDateTime dateTime= QDateTime::currentDateTime();
    QString strTime = dateTime .toString("yyyy-MM-dd hh:mm:ss");

    ui->time->setText(strTime);
    ui->moment->setText("刚刚");
    ui->name->setText(name);
    ui->value->setText(value);

    m_count = 0;
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(refreshMoment()));
    m_timer->start(60000);

    connect(ui->request, SIGNAL(clicked()), this, SIGNAL(requested()));

}

DataItem::~DataItem()
{
    delete ui;
}

void DataItem::refreshValue(const QString &value)
{
    ui->value->setText(value);

    ui->moment->setText("刚刚");
    m_count = 0;
    m_timer->stop();
    m_timer->start(60000);

}

void DataItem::refreshMoment()
{
    ++m_count;
    QString strMom = QString("%1分钟前").arg(m_count);
    ui->moment->setText(strMom);

}
