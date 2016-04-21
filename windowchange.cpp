#include "windowchange.h"
#include "ui_windowchange.h"

#include "planwindow.h"

WindowChange::WindowChange(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowChange)
{
    ui->setupUi(this);
    ui->comboBox->setCurrentIndex(-1);
}

WindowChange::~WindowChange()
{
    delete ui;
}


void WindowChange::on_comboBox_currentIndexChanged(int index)
{
    Fill(index);
}

void WindowChange::on_tableWidget_cellChanged(int row, int column)
{
    DataBase* db = ((PlanWindow*)parent())->db;
    switch (ui->comboBox->currentIndex())
    {
    case 0:
        if (ui->tableWidget->currentRow()>=db->professors.size())
        {
            Professor* temp = new Professor(0,ui->tableWidget->item(row,column)->text());
            temp->insert(temp);
            db->reload();
            Fill(ui->comboBox->currentIndex());
        }
        else if (ui->tableWidget->currentRow()>=0)
        {
            Professor* temp = new Professor(0,ui->tableWidget->item(row,column)->text());
            db->professors[row]->update(temp);
        }
        break;
    case 1:
        if (ui->tableWidget->currentRow()>=db->disciplines.size())
        {
            Discipline* temp = new Discipline(0,ui->tableWidget->item(row,column)->text());
            temp->insert(temp);
            db->reload();
            Fill(ui->comboBox->currentIndex());
        }
        else if (ui->tableWidget->currentRow()>=0)
        {
            Discipline* temp = new Discipline(0,ui->tableWidget->item(row,column)->text());
            db->disciplines[row]->update(temp);
        }
        break;
    case 2:
        if (ui->tableWidget->currentRow()>=db->extraDuties.size())
        {
            ExtraDuty* temp = new ExtraDuty(0,ui->tableWidget->item(row,0)->text(), ui->tableWidget->item(row, 1)->text().toInt(),
                                            ui->tableWidget->item(row,2)->text(), ui->tableWidget->item(row, 3)->text().toInt());
            temp->insert(temp);
            db->reload();
            Fill(ui->comboBox->currentIndex());
        }
        else if (ui->tableWidget->currentRow()>=0)
        {
            ExtraDuty* temp = new ExtraDuty(0,ui->tableWidget->item(row,0)->text(), ui->tableWidget->item(row, 1)->text().toInt(),
                                            ui->tableWidget->item(row,2)->text(), ui->tableWidget->item(row, 3)->text().toInt());
            db->extraDuties[row]->update(temp);
        }
        break;
    }

}

void WindowChange::Fill(int index)
{
    DataBase* db = ((PlanWindow*)parent())->db;
    int j = 0;
    switch (index)
    {
    case 0:
        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setRowCount(db->professors.size()+1);
        foreach (Professor* i, db->professors)
        {
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(i->getName()));
            j++;
        }
        break;
    case 1:
        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setRowCount(db->disciplines.size()+1);
        foreach (Discipline* i, db->disciplines)
        {
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(i->getName()));
            j++;
        }
        break;
    case 2:
        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setRowCount(db->extraDuties.size()+1);
        foreach (ExtraDuty* i, db->extraDuties)
        {
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(i->getDutyName()));
            ui->tableWidget->setItem(j, 1, new QTableWidgetItem(QString::number(i->getDutyHours())));
            ui->tableWidget->setItem(j, 2, new QTableWidgetItem(i->getPositionName()));
            ui->tableWidget->setItem(j, 3, new QTableWidgetItem(QString::number(i->getIdProfessor())));
            j++;
        }
        ui->tableWidget->setItem(j, 1, new QTableWidgetItem(QString::number(1)));
        ui->tableWidget->setItem(j, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(j, 3, new QTableWidgetItem(QString::number(1)));
        ui->tableWidget->setItem(j, 2, new QTableWidgetItem(""));
        break;
    }

}
