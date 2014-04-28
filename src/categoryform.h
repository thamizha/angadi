#ifndef CATEGORYFORM_H
#define CATEGORYFORM_H

#include "lssbar.h"
#include "models/formvalidation.h"
#include "models/categoriesmodel.h"

#include <QWidget>
#include <QValidator>
#include <QIntValidator>
#include <QDataWidgetMapper>
#include <QDateTime>

namespace Ui {
class CategoryForm;
}

class CategoryForm : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QDateTime modifiedDate READ modifiedDate WRITE setModifiedDate)

public:
    explicit CategoryForm(QWidget *parent = 0);
    ~CategoryForm();
    void setCodeFocus();
    void setModel(CategoriesModel *model);
    void setMapperIndex(QModelIndex index);
    void search(QString value);
    QDateTime modifiedDate() const;
    void setModifiedDate(QDateTime modifiedDate);

signals:

public slots:

private:
    Ui::CategoryForm *ui;
    CategoriesModel *categoriesModel;
    QDataWidgetMapper *dataMapper;
    Lssbar *lssbar;
    void clear();
    QDateTime m_modifiedDate;

private slots:
    void save();
    bool codeValid();
    bool nameValid();
    void on_pushButtonAdd_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonDelete_clicked();
};

#endif // CategoryForm_H
