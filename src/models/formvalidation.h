#ifndef FORMVALIDATION_H
#define FORMVALIDATION_H

#include <QObject>
#include <QValidator>
#include <QDebug>
#include <QSqlQuery>

class FormValidation : public QObject
{
    Q_OBJECT
public:
    explicit FormValidation(QObject *parent = 0);
    bool isInteger(QString value);
    bool emailValid(QString value);
    int uniqueValid(QString id, QString value, QString table, QString column);
    bool isDouble(QString value);

signals:

public slots:

};

#endif // FORMVALIDATION_H
