#include "planwindow.h"
#include "ui_planwindow.h"

#include <QCheckBox>

#include "classeditwindow.h"

PlanWindow::PlanWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlanWindow)
{
    ui->setupUi(this);
    db = new DataBase();
    ui->VkUvcComboBox->addItem(QString("ВК"));
    ui->VkUvcComboBox->addItem(QString("УВЦ"));
}

PlanWindow::~PlanWindow()
{
    delete ui;
}

void PlanWindow::on_VkUvcComboBox_currentIndexChanged(int index)
{
    db->GetVuses(index+1);
    ui->VUSComboBox->clear();
    foreach (int i, db->currentVuses)
    {
        ui->VUSComboBox->addItem(QString::number(i));
    }
}

void PlanWindow::on_VUSComboBox_currentIndexChanged(int index)
{
    ui->semesterComboBox->clear();
    if (index!= -1)
    {
        db->GetSemesters(ui->VkUvcComboBox->currentIndex()+1, db->currentVuses[index]);
        foreach (int i, db->currentSemesters)
        {
            ui->semesterComboBox->addItem(QString::number(i));
        }
    }
}

void PlanWindow::on_semesterComboBox_currentIndexChanged(int index)
{
    ui->disciplineComboBox->clear();
    if (index!=-1)
    {
        db->GetDisciplines(ui->VkUvcComboBox->currentIndex()+1, db->currentVuses[ui->VUSComboBox->currentIndex()],
                db->currentSemesters[index]);
        foreach (Discipline* i, db->currentDisciplines)
        {
            ui->disciplineComboBox->addItem(i->getName());
        }
    }
}

void PlanWindow::on_disciplineComboBox_currentIndexChanged(int index)
{
    if (index!=-1)
    {
        db->GetThematicPlan(ui->VkUvcComboBox->currentIndex()+1, db->currentVuses[ui->VUSComboBox->currentIndex()],
                db->currentSemesters[ui->semesterComboBox->currentIndex()], db->currentDisciplines[index] );

        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(9);
        ui->tableWidget->setRowCount(db->currentThematicPlan->classesCount());
        const QVector<Class*> classes = db->currentThematicPlan->getClasses();
        for (int i=0;i < db->currentThematicPlan->classesCount();i++)
        {
            ui->tableWidget->setItem(i,0, new QTableWidgetItem(QString::number(classes[i]->getNumber())));
            ui->tableWidget->setItem(i,1, new QTableWidgetItem(classes[i]->getClassType()->getName()));
            ui->tableWidget->setItem(i,2, new QTableWidgetItem(QString::number(classes[i]->getHours())));
            for (int j=0;j<classes[i]->getProfessors().size();j++)
            {
                ui->tableWidget->setCellWidget(i,3+2*j,new QCheckBox(ui->tableWidget));
                qobject_cast<QCheckBox*>(ui->tableWidget->cellWidget(i, 3+2*j))->setChecked(classes[i]->getProfessors()[j]->getFirstTime());
                ui->tableWidget->setItem(i,4+2*j, new QTableWidgetItem(classes[i]->getProfessors()[j]->getName()));
            }
        }
    }
}

void PlanWindow::on_addButton_clicked()
{
    ClassEditWindow* edit = new ClassEditWindow(this);

    edit->exec();
    //this->ui->centralWidget->setDisabled(true);
}
