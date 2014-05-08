/*****************************************************************************
 * customerform.h
 *
 * Created: 18/04/2014 by selvam
 *
 * Copyright 2014 ThamiZha!. All rights reserved.
 *
 * Visit www.thamizha.com for more information.
 *
 * This file is a part of ThamiZha Angadi application.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *
 * Authors :
 * Selvam <vjpselvam@gmail.com>
 *****************************************************************************/

#ifndef CUSTOMERFORM_H
#define CUSTOMERFORM_H

#include "models/formvalidation.h"
#include "models/customersmodel.h"

#include <QWidget>
#include <QValidator>
#include <QIntValidator>
#include <QDataWidgetMapper>
#include <QDateTime>
#include <QEvent>

namespace Ui {
class CustomerForm;
}

class CustomerForm : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QDateTime modifiedDate READ modifiedDate WRITE setModifiedDate)
    QString statusMsg;

public:
    explicit CustomerForm(QWidget *parent = 0);
    ~CustomerForm();
    void setCodeFocus();
    void setNameFocus();
    void setModel(CustomersModel *model);
    void setMapperIndex(QModelIndex index);
    void search(QString value);
    QDateTime modifiedDate();
    void setModifiedDate(QDateTime modifiedDate);
    void clear();
    int validCodeFlag, validNameFlag, validEmailFlag, validCreditLimitFlag;
    void setFieldMaxLength();

signals:
    void signalName(QString str);
    void signalFromCustomerForm();
    void signalStatusBar(QString str);
    void signalUpdated();

private:
    Ui::CustomerForm *ui;
    CustomersModel *customersModel;
    QDataWidgetMapper *dataMapper;
    QDateTime m_modifiedDate;
    FormValidation *formValidation;

private slots:
    void save();
    bool codeValid();
    bool nameValid();
    bool creditLimitValid();
    bool emailValid();
    bool contactPersonValid();
    bool address1Valid();
    bool address2Valid();
    bool cityValid();
    bool stateValid();
    bool countryValid();
    bool pincodeValid();
    bool phone1Valid();
    bool phone2Valid();
    bool mobile1Valid();
    bool mobile2Valid();
    bool WebsiteValid();

    void on_pushButtonCancel_clicked();
    void on_pushButtonDelete_clicked();
    void onNameChanged(QString str);
    bool uniqueValid(QString text, QString field);
    void setSignalFromCustomerForm();
    bool eventFilter(QObject *obj, QEvent *event);
    void resetDataMapper();
    void uninstallEventFilter();
    void setAllValidationSuccess();
};

#endif // CUSTOMERFORM_H
