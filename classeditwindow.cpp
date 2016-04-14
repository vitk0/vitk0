#include "classeditwindow.h"
#include "planwindow.h"
#include "ui_planwindow.h"
#include "ui_classeditwindow.h"


ClassEditWindow::ClassEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClassEditWindow)
{
    ui->setupUi(this);
    DataBase* db = ((PlanWindow*)parent)->db;
    Class* currentClass = db->currentThematicPlan->getClasses()[((PlanWindow*)parent)->GetUI()->tableWidget->currentRow()];
    ui->numberClassEdit->setText(QString::number(currentClass->getNumber()));
}

ClassEditWindow::~ClassEditWindow()
{
    delete ui;
}
