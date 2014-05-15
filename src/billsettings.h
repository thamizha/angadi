/*****************************************************************************
 * billsettings.h
 *
 * Created: 14/05/2014 by vijay
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
 * Vijay @ Dhanasekaran <vijay.kuruntham.gmail.com>
 *****************************************************************************/

#ifndef BILLSETTINGS_H
#define BILLSETTINGS_H

#include <QDialog>
#include <QDir>

namespace Ui {
class BillSettings;
}

class BillSettings : public QDialog
{
    Q_OBJECT

public:
    explicit BillSettings(QWidget *parent = 0);
    ~BillSettings();
    void settranslate();


private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::BillSettings *ui;
    void setLanguage();
};

#endif // BILLSETTINGS_H
