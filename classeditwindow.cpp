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
    ui->hoursEdit->setText(QString::number(currentClass->getHours()));

    foreach(ClassType* i, db->classTypes)
    {
        ui->typeClassesComboBox->addItem(i->getName());
    }
    int index = ui->typeClassesComboBox->findText(currentClass->getClassType()->getName());
    ui->typeClassesComboBox->setCurrentIndex(index);

    foreach(Professor* i, db->professors)
    {
        ui->professorComboBox->addItem(i->getName());
        ui->professorComboBox_2->addItem(i->getName());
        ui->professorComboBox_3->addItem(i->getName());
    }
    index = ui->professorComboBox->findText(currentClass->getProfessors()[0]->getName());
    ui->professorComboBox->setCurrentIndex(index);
}

ClassEditWindow::~ClassEditWindow()
{
    delete ui;
}
