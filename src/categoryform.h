#ifndef CATEGORYFORM_H
#define CATEGORYFORM_H

#include <QWidget>
#include <models/category.h>
#include <QValidator>
#include <QIntValidator>

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

public slots:

private:
    Ui::CategoryForm *ui;

private slots:
    void enableSave(QString value);
    void save();
};

#endif // CategoryForm_H
