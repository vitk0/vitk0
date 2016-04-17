#include "classeditwindow.h"
#include "planwindow.h"
#include "ui_planwindow.h"
#include "ui_classeditwindow.h"


ClassEditWindow::ClassEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClassEditWindow)
{
    ui->setupUi(this);

    frames.push_back(ui->professorFrame);
    frames.push_back(ui->professorFrame_2);
    frames.push_back(ui->professorFrame_3);

    DataBase* db = ((PlanWindow*)parent)->db;

    foreach(ClassType* i, db->classTypes)
    {
        ui->typeClassesComboBox->addItem(i->getName());
    }

    foreach(Professor* i, db->professors)
    {
        for (int j=0;j<3;j++)
        {
            ((QComboBox*)frames[j]->children()[0])->addItem(i->getName());
        }
    }
    if (((PlanWindow*)parent)->GetUI()->tableWidget->currentRow()>=0)
    {
        Class* currentClass = db->currentThematicPlan->getClasses()[((PlanWindow*)parent)->GetUI()->tableWidget->currentRow()];
        ui->numberClassEdit->setText(QString::number(currentClass->getNumber()));
        ui->hoursEdit->setText(QString::number(currentClass->getHours()));

        int index = ui->typeClassesComboBox->findText(currentClass->getClassType()->getName());
        ui->typeClassesComboBox->setCurrentIndex(index);

        professorsCount = currentClass->getProfessors().size();
        if (professorsCount==3)
            ui->addProfessorButton->hide();
        if(professorsCount==1)
            ui->deleteProfessorButton->hide();

        for (int i=0; i<professorsCount;i++)
        {
            index = ((QComboBox*)frames[i]->children()[0])->findText(currentClass->getProfessors()[i]->getName());
            ((QComboBox*)frames[i]->children()[0])->setCurrentIndex(index);
            ((QCheckBox*)frames[i]->children()[1])->setChecked(currentClass->getProfessors()[i]->getFirstTime());
            frames[i]->show();
        }
    }
    else
    {
        ui->typeClassesComboBox->setCurrentIndex(0);
        professorsCount = 1;
        ui->deleteProfessorButton->hide();
        for (int i=0; i<professorsCount;i++)
        {
            ((QComboBox*)frames[i]->children()[0])->setCurrentIndex(0);
            ((QCheckBox*)frames[i]->children()[1])->setChecked(false);
            frames[i]->show();
        }
    }
}

ClassEditWindow::~ClassEditWindow()
{
    delete ui;
}

void ClassEditWindow::on_addProfessorButton_clicked()
{
    frames[professorsCount++]->show();
    ui->deleteProfessorButton->show();
    if (professorsCount==3)
        ui->addProfessorButton->hide();
}

void ClassEditWindow::on_deleteProfessorButton_clicked()
{
    frames[--professorsCount]->hide();
    ui->addProfessorButton->show();
    if(professorsCount==1)
        ui->deleteProfessorButton->hide();
}

void ClassEditWindow::on_buttonBox_accepted()
{
    DataBase* db = ((PlanWindow*)parent())->db;
    Class* currentClass ;
    if(((PlanWindow*)parent())->GetUI()->tableWidget->currentRow()>=0)
    {
        currentClass = db->currentThematicPlan->getClasses()[((PlanWindow*)parent())->GetUI()->tableWidget->currentRow()];
    }
    else
    {
        currentClass = new Class();
    }

    Class* temp = new Class(currentClass->getId(),ui->numberClassEdit->text().toInt(), db->classTypes[ui->typeClassesComboBox->currentIndex()],
            ui->hoursEdit->text().toInt(), db->currentThematicPlan->getId());
    temp->clearProfessors();
    for(int i=0; i<professorsCount;i++)
    {
    temp->addProfessor(new classes_professors(0,temp->getId(),((QCheckBox*)frames[i]->children()[1])->checkState()==Qt::Checked,
                       db->professors[((QComboBox*)frames[i]->children()[0])->currentIndex()]->getId(),
            db->professors[((QComboBox*)frames[i]->children()[0])->currentIndex()]->getName()));
    }
    if (((PlanWindow*)parent())->update)
    {
        currentClass->update(temp);
    }
    else
    {
        currentClass->insert(temp);
    }
}
