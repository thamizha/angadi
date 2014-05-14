#ifndef RIGHTALIGNDELEGATE_H
#define RIGHTALIGNDELEGATE_H

#include <QObject>
#include <QItemDelegate>

class RightAlignDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    RightAlignDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

};

#endif // RIGHTALIGNDELEGATE_H
