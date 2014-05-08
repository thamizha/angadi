#include "formvalidation.h"
#include <QSqlError>

FormValidation::FormValidation(QObject *parent) :
    QObject(parent)
{
}

bool FormValidation::isInteger(QString value)
{
    int pos=0;
    bool status = false;
    if(value.length() > 0){
        QIntValidator v(1,1000000,this);
        qint8 vState= v.validate(value,pos);
        if(vState==2){
            status = true;
        }
    }
    return status;
}

bool FormValidation::emailValid(QString value)
{
    bool status = false;
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    qint8 vState = mailREX.exactMatch(value);
    if(vState == 1)
        status = true;
    return status;
}

int FormValidation::uniqueValid(QString id, QString value, QString table ,QString column)
{
    int size;
    QSqlQuery query;
    QString queryText;
    queryText = "SELECT * FROM ";
    queryText.append(table);
    queryText.append(" WHERE ");
    queryText.append(column);
    queryText.append(" ='");
    queryText.append(value);
    queryText.append("' AND status = 'A' AND id !=");
    queryText.append(id);
    query.exec(queryText);
    size = query.size();
    return size;
}

bool FormValidation::isDouble(QString value)
{
    int pos = 0;
    bool status = false;
    QDoubleValidator *isDoubleValid = new QDoubleValidator(this);
    isDoubleValid->setRange(0.00, 1000000.00, 2);
    qint8 state = isDoubleValid->validate(value,pos);
    if(state == 2)
        status = true;
    return status;
}

bool FormValidation::isRecordFound(QString table, QString column, QString value)
{
    bool status = false;
    int size;
    QSqlQuery query;
    QString queryText;
    queryText = "SELECT * FROM ";
    queryText.append(table);
    queryText.append(" WHERE ");
    queryText.append(column);
    queryText.append(" like '%");
    queryText.append(value);
    queryText.append("%' AND status = 'A'");
    query.exec(queryText);
    size = query.size();
    if(size > 0){
        status = true;
    }
    return status;
}
