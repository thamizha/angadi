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
    bool intRequired(QString value);
    bool textRequired(QString value,int len);
    bool emailValid(QString value);
    int uniqueValid(QString id, QString value, QString table, QString column);

signals:

public slots:

};

#endif // FORMVALIDATION_H
