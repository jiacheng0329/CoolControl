#ifndef DATAITEM_H
#define DATAITEM_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class DataItem;
}

class DataItem : public QWidget
{
    Q_OBJECT

public:
    explicit DataItem(QWidget *parent = nullptr);
    DataItem(const QString &name, const QString &value, QWidget *parent = nullptr);
    ~DataItem();

    void refreshValue(const QString &);

signals:
    void requested();

private slots:
    void refreshMoment();

private:
    Ui::DataItem *ui;
    QString m_time;
    QString m_name;
    QString m_value;
    QString m_moment;

    QTimer *m_timer;
    int m_count;
};

#endif // DATAITEM_H
