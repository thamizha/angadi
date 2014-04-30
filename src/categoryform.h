#ifndef CATEGORYFORM_H
#define CATEGORYFORM_H

#include "models/formvalidation.h"
#include "models/categoriesmodel.h"
#include "models/formvalidation.h"

#include <QWidget>
#include <QValidator>
#include <QIntValidator>
#include <QDataWidgetMapper>
#include <QDateTime>
#include <QEvent>

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
    void clear();

signals:
    void signalName(QString str);
    void signalFromCategoryForm();

public slots:

private:
    Ui::CategoryForm *ui;
    CategoriesModel *categoriesModel;
    QDataWidgetMapper *dataMapper;
    QDateTime m_modifiedDate;
    FormValidation *formValidation;

private slots:
    void save();
    void save1();
    bool codeValid();
    bool nameValid();
    void on_pushButtonAdd_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonDelete_clicked();
    void onNameChanged(QString str);
    bool uniqueValid(QString text, QString field);
    void setSignalFromCategoryForm();
    void setFieldMaxLength();
    //void unsetStyles();
    bool eventFilter(QObject *obj, QEvent *event);
    void resetDataMapper();
};

#endif // CategoryForm_H
