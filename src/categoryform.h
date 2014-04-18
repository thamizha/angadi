#ifndef CATEGORYFORM_H
#define CATEGORYFORM_H

#include <QWidget>
#include <models/category.h>

namespace Ui {
class CategoryForm;
}

class CategoryForm : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryForm(QWidget *parent = 0);
    ~CategoryForm();

public slots:

private:
    Ui::CategoryForm *ui;

private slots:
    void save();
};

#endif // CategoryForm_H