/*****************************************************************************
 * productform.h
 *
 * Created: 18/04/2014 by vijay
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
 *
 *****************************************************************************/

#ifndef PRODUCTFORM_H
#define PRODUCTFORM_H

#include <QWidget>
#include <QErrorMessage>
#include <QDataWidgetMapper>

#include "lssbar.h"
#include "models/productsmodel.h"
#include "models/formvalidation.h"
#include "models/formvalidation.h"

namespace Ui {
class ProductForm;
}

class ProductForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductForm(QWidget *parent = 0);
    ~ProductForm();
    void setCodeFocus();
    void clear();
    void setModel(ProductsModel *model);
    void setMapperIndex(QModelIndex index);
    void setFieldMaxLength();

signals:
    void signalName(QString str);
    void signalFromProductForm();

private:
    Ui::ProductForm *ui;
    ProductsModel *productsModel;
    QDataWidgetMapper *dataMapper;
    Lssbar *lssbar;
    FormValidation *formValidation;

private slots:
    void save();
    bool codeValid();
    bool nameValid();
    bool mrpValid();
    bool salePriceValid();
    bool wholeSalePriceValid();
    void on_pushButtonCancel_clicked();
    void on_pushButtonDelete_clicked();
    void onNameChanged(QString str);
    void setSignalFromProductForm();
    bool uniqueValid(QString text, QString field);
};

#endif // PRODUCTFORM_H
