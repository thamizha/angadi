#ifndef TIMEEDITDELEGATE_H
#define TIMEEDITDELEGATE_H

#include <QObject>
#include <QItemDelegate>

class TimeEditDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    TimeEditDelegate(const QString timeFormat = "dd.MM.yyyy hh:mm:ss",QObject *parent = 0) : QItemDelegate(parent)
    {
        this->timeformat = timeFormat;
    };
    void paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index) const;

signals:

public slots:

private:
    QString timeformat;
};

#endif // TIMEEDITDELEGATE_H
