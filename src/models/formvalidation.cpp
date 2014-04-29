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
