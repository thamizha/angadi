#ifndef CATAGORYFORM_H
#define CATAGORYFORM_H

#include <QWidget>

namespace Ui {
class CatagoryForm;
}

class CatagoryForm : public QWidget
{
    Q_OBJECT

public:
    explicit CatagoryForm(QWidget *parent = 0);
    ~CatagoryForm();

private slots:
    void on_cat_save_button_clicked();

private:
    Ui::CatagoryForm *ui;
};

#endif // CATAGORYFORM_H
