#include "planwindow.h"
#include "ui_planwindow.h"

#include <QCheckBox>

#include "classeditwindow.h"
#include "windowchange.h"
#include "connectionsettings.h"
#include <QFile>

PlanWindow::PlanWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlanWindow)
{
//    QFile file("Settings.txt");
//    if(!file.exists()){
//        QByteArray data;
//        data.insert(0,Connect::dbName + QString("\n") + Connect::dbIP + QString("\n") + Connect::dbPort + QString("\n") + Connect::dbLogin + QString("\n") + Connect::dbPassword);

//        file.open(QIODevice::WriteOnly);
//        file.write(data);
//        file.close();
//    }
    QFile file("Settings.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        while (!file.atEnd()) {
           QString str = file.readLine();
           QStringList lst = str.split(" ");
           Connect::dbName = lst.at(0);
           Connect::dbIP = lst.at(1);
           Connect::dbPort = lst.at(2).toInt();
           Connect::dbLogin = lst.at(3);
           Connect::dbPassword = lst.at(4);
           file.close();
        }
    }


    ui->setupUi(this);
    db = new DataBase();
    ui->VkUvcComboBox->addItem(QString("ВК"));
    ui->VkUvcComboBox->addItem(QString("УВЦ"));
}

Ui::PlanWindow *PlanWindow::GetUI()
{
    return ui;
}

PlanWindow::~PlanWindow()
{
    delete ui;

    QFile file("Settings.txt");
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        while (!file.atEnd()) {
           QString str = Connect::dbName + QString(" ") +
                 Connect::dbIP + QString(" ") +
                 Connect::dbPort + QString(" ") +
                 Connect::dbLogin + QString(" ") +
                 Connect::dbPassword ;

                 QByteArray data;
                 data.insert(0,str);
                 file.write(data);
                 file.close();
        }
    }
}

void PlanWindow::on_VkUvcComboBox_currentIndexChanged(int index)
{
    db->GetVuses(index+1);
    ui->VUSComboBox->clear();
    foreach (Platoon* i, db->currentPlatoons)
    {
        ui->VUSComboBox->addItem(QString::number(i->getVus()));
    }
}

void PlanWindow::on_VUSComboBox_currentIndexChanged(int index)
{
    ui->semesterComboBox->clear();
    if (index!= -1)
    {
        db->GetSemesters(ui->VkUvcComboBox->currentIndex()+1, db->currentPlatoons[index]);
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
        db->GetDisciplines(ui->VkUvcComboBox->currentIndex()+1, db->currentPlatoons[ui->VUSComboBox->currentIndex()],
                db->currentSemesters[index]);
        foreach (Discipline* i, db->currentDisciplines)
        {
            ui->disciplineComboBox->addItem(i->getName());
        }
    }
}

void PlanWindow::Fill()
{
    db->GetThematicPlan(ui->VkUvcComboBox->currentIndex()+1, db->currentPlatoons[ui->VUSComboBox->currentIndex()],
            db->currentSemesters[ui->semesterComboBox->currentIndex()], db->currentDisciplines[ui->disciplineComboBox->currentIndex()] );

    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setRowCount(db->currentThematicPlan->classesCount());
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("№")));
    ui->tableWidget->setColumnWidth(0,25);
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Вид занятия")));
    ui->tableWidget->setColumnWidth(1,140);
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Длительность")));
    ui->tableWidget->setColumnWidth(2,85);
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("П.р.")));
    ui->tableWidget->setColumnWidth(3,30);
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("ФИО преподавателя")));
    ui->tableWidget->setColumnWidth(4,160);
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem(QString("П.р.")));
    ui->tableWidget->setColumnWidth(5,30);
    ui->tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem(QString("ФИО преподавателя")));
    ui->tableWidget->setColumnWidth(6,160);
    ui->tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem(QString("П.р.")));
    ui->tableWidget->setColumnWidth(7,30);
    ui->tableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem(QString("ФИО преподавателя")));
    ui->tableWidget->setColumnWidth(8,150);

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
            qobject_cast<QCheckBox*>(ui->tableWidget->cellWidget(i, 3+2*j))->setDisabled(true);
            ui->tableWidget->setItem(i,4+2*j, new QTableWidgetItem(classes[i]->getProfessors()[j]->getName()));
        }
    }

}

void PlanWindow::on_disciplineComboBox_currentIndexChanged(int index)
{
    if (index!=-1)
    {
        Fill();
    }
}

void PlanWindow::on_addButton_clicked()
{
    update = false;

    ClassEditWindow* edit = new ClassEditWindow(this);

    if(edit->exec()==QDialog::Accepted)
    {
        Fill();
    }

}


void PlanWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    ui->tableWidget->selectRow(row);

    update = true;

    ClassEditWindow* edit = new ClassEditWindow(this);

    if(edit->exec()==QDialog::Accepted)
    {
        Fill();
    }

}

void PlanWindow::on_deleteButton_clicked()
{
    if (ui->tableWidget->currentRow()>=0)
    {
        db->currentThematicPlan->getClasses()[ui->tableWidget->currentRow()]->remove();
        Fill();
    }
}

void PlanWindow::on_reportButton_clicked()
{
    db->GenerateReport();
}

void PlanWindow::on_openChangeWindowButton_clicked()
{
    WindowChange* admin = new WindowChange(this);
    admin->show();
}


void PlanWindow::on_toolButton_clicked()
{
    ConnectionSettings* conSettings = new ConnectionSettings(this);
    conSettings->show();
}
