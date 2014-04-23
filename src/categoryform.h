#ifndef CATEGORYFORM_H
#define CATEGORYFORM_H

#include <QWidget>
#include <models/formvalidation.h>
#include <models/category.h>
#include <models/categoriesmodel.h>
#include <QValidator>
#include <QIntValidator>
#include "lssbar.h"


namespace Ui {
class CategoryForm;
}

class CategoryForm : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryForm(QWidget *parent = 0);
    ~CategoryForm();
    void setCodeFocus();
    void clear();
    void setModel(CategoriesModel *model);

public slots:

private:
    Ui::CategoryForm *ui;
    CategoriesModel *categoriesModel;

private slots:
    void save();
    void codeValid();
    void nameValid();
};

#endif // CategoryForm_H
