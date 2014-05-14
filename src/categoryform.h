#ifndef CATEGORYFORM_H
#define CATEGORYFORM_H

#include "models/formvalidation.h"
#include "models/categoriesmodel.h"

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
    QString statusMsg;

public:
    explicit CategoryForm(QWidget *parent = 0);
    ~CategoryForm();
    void setCodeFocus();
    void setNameFocus();
    void setModel(CategoriesModel *model);
    void setMapperIndex(QModelIndex index);
    void search(QString value);
    QDateTime modifiedDate() const;
    void setModifiedDate(QDateTime modifiedDate);
    void clear();
    int validNameFlag , validCodeFlag;
    void setFieldMaxLength();
    void settranslate();
//    void saveButtonText(qint8);

public slots:

signals:
    void signalName(QString str);
    void signalFromCategoryForm();
    void signalStatusBar(QString str);
    void signalUpdated();

private:
    Ui::CategoryForm *ui;
    CategoriesModel *categoriesModel;
    QDataWidgetMapper *dataMapper;
    QDateTime m_modifiedDate;
    FormValidation *formValidation;

private slots:
    void save();
    bool codeValid();
    bool nameValid();
    void on_pushButtonCancel_clicked();
    void on_pushButtonDelete_clicked();
    void onNameChanged(QString str);
    bool uniqueValid(QString text, QString field);
    void setSignalFromCategoryForm();
    bool eventFilter(QObject *obj, QEvent *event);
    void resetDataMapper();
    void uninstallEventFilter();
    void setAllValidationSuccess();
};

#endif // CategoryForm_H
