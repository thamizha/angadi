#include "angadimainwindow.h"
#include "ui_angadimainwindow.h"

AngadiMainWindow::AngadiMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AngadiMainWindow)
{
    ui->setupUi(this);

    //Hide rightdock widget on start
    ui->rightDock->setVisible(false);
}

AngadiMainWindow::~AngadiMainWindow()
{
    delete ui;
}
