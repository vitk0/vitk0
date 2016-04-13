#include "classeditwindow.h"
#include "ui_classeditwindow.h"

ClassEditWindow::ClassEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClassEditWindow)
{
    ui->setupUi(this);
}

ClassEditWindow::~ClassEditWindow()
{
    delete ui;
}
