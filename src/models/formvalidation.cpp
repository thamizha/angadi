#include "formvalidation.h"

FormValidation::FormValidation(QObject *parent) :
    QObject(parent)
{
}

bool FormValidation::intValid(QString value)
{
    int pos=0;
    QIntValidator v(1,10000,this);
    qint8 vState= v.validate(value,pos);
    if(vState==2)
    {
        bool status = true;
        return status;
    }
    else
    {
        bool status = false;
        return status;
    }
}

bool FormValidation::textValid(QString value,int len)
{
    int Len=value.length();
    if (Len==0)
    {
        bool status = false;
        return status;
    }
    else if (Len <= len)
    {
        bool status = true;
        return status;
    }
    else
    {
        bool status = false;
        return status;
    }
}

bool FormValidation::emailValid(QString value)
{
    bool status = false;
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    qint8 vState= mailREX.exactMatch(value);
    qDebug() << vState;
    if(vState==1)
        status = true;
    else
        status = false;
    return status;
}

//bool FormValidation::dateValid(QString value)
//{
//    return true;
//}

int FormValidation::uniqueValid(int id, QString value, QString table ,QString column)
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
    queryText.append("' AND status = 'A' AND id !='");
    queryText.append(id);
    queryText.append("'");
    query.exec(queryText);
    size = query.size();
    qDebug() << size;
    return size;
}
