#ifndef BILLFORM_H
#define BILLFORM_H

#include <QWidget>

namespace Ui {
class BillForm;
}

class BillForm : public QWidget
{
    Q_OBJECT

public:
    explicit BillForm(QWidget *parent = 0);
    ~BillForm();
    void clear();
    void setCodeFocus();

private:
    Ui::BillForm *ui;

private slots:


};

#endif // BILLFORM_H
