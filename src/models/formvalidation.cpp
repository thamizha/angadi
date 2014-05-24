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

// Mysql
/*int FormValidation::uniqueValid(QString id, QString value, QString table ,QString column)
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
}*/

// Sqlite
int FormValidation::uniqueValid(QString id, QString value, QString table ,QString column)
{
    int numRows = 0;
    QSqlQuery query;
    QString queryText;
    queryText = "SELECT COUNT (*) FROM ";
    queryText.append(table);
    queryText.append(" WHERE ");
    queryText.append("UPPER(" + column + ")");
    queryText.append(" ='");
    queryText.append("UPPER(" + value + ")");
    queryText.append(" AND status = 'A' AND id !=");
    queryText.append(id);
    query.exec(queryText);
    if(query.next()){
        numRows = query.value(0).toInt();
    }else{
        numRows = 0;
    }
    return numRows;
}

bool FormValidation::isDouble(QString value)
{
    int pos = 0;
    bool status = false;
    QDoubleValidator *isDoubleValid = new QDoubleValidator(this);
    isDoubleValid->setRange(0.000, 1000000.000, 3);
    qint8 state = isDoubleValid->validate(value,pos);
    if(state == 2)
        status = true;
    return status;
}

// Mysql
/*bool FormValidation::isRecordFound(QString table, QString column, QString value)
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
}*/

// Sqlite
bool FormValidation::isRecordFound(QString table, QString column, QString value)
{
    bool status = false;
    int numRows = 0;
    QSqlQuery query;
    QString queryText;
    queryText = "SELECT COUNT (*) FROM ";
    queryText.append(table);
    queryText.append(" WHERE ");
    queryText.append(column);
    queryText.append(" like '%");
    queryText.append(value);
    queryText.append("%' COLLATE NOCASE ");
    queryText.append(" AND status = 'A'");
    query.exec(queryText);
    if(query.next()){
        numRows = query.value(0).toInt();
    }else{
        numRows = 0;
    }
    if(numRows > 0){
        status = true;
    }
    return status;
}

QString FormValidation::convertDouble(QString value)
{
    double number = value.toDouble();
    return QString::number(number,'f',2);
}
