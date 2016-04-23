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
    case 3:
        if (ui->tableWidget->currentRow()>=db->platoons.size())
        {
            Platoon* temp = new Platoon(0,ui->tableWidget->item(row,0)->text().toInt(), ui->tableWidget->item(row, 1)->text().toInt(),
                                            ui->tableWidget->item(row,2)->text().toInt(), ui->tableWidget->item(row, 3)->text().toInt(), ui->tableWidget->item(row, 4)->text().toInt());
            temp->insert(temp);
            db->reload();
            Fill(ui->comboBox->currentIndex());
        }
        else if (ui->tableWidget->currentRow()>=0)
        {
            Platoon* temp = new Platoon(0,ui->tableWidget->item(row,0)->text().toInt(), ui->tableWidget->item(row, 1)->text().toInt(),
                                        ui->tableWidget->item(row,2)->text().toInt(), ui->tableWidget->item(row, 3)->text().toInt(), ui->tableWidget->item(row, 4)->text().toInt());
            db->platoons[row]->update(temp);
        }
        break;
    }

}

void WindowChange::Fill(int index)
{
    DataBase* db = ((PlanWindow*)parent())->db;
    int j = 0;
    ui->tableWidget->clear();
    switch (index)
    {
    case 0:
        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setRowCount(db->professors.size()+1);
        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Звание, ФИО")));
        foreach (Professor* i, db->professors)
        {
            ui->tableWidget->setVerticalHeaderItem(j, new QTableWidgetItem(QString::number(i->getId())));
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(i->getName()));
            j++;
        }
        break;
    case 1:
        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setRowCount(db->disciplines.size()+1);
        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Название")));
        foreach (Discipline* i, db->disciplines)
        {
            ui->tableWidget->setVerticalHeaderItem(j, new QTableWidgetItem(QString::number(i->getId())));
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(i->getName()));
            j++;
        }
        break;
    case 2:
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setRowCount(db->extraDuties.size()+1);
        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Должность")));
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Часовая нагрузка")));
        ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Название")));
        ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("ID")));
        foreach (ExtraDuty* i, db->extraDuties)
        {
            ui->tableWidget->setVerticalHeaderItem(j, new QTableWidgetItem(QString::number(i->getId())));
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
    case 3:
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setRowCount(db->platoons.size()+1);
        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Год поступления")));
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Численность")));
        ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("№ потока")));
        ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Кол-во п/взводов")));
        ui->tableWidget->setColumnWidth(3,110);
        ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("ВУС")));
        ui->tableWidget->setColumnWidth(4,50);

        foreach (Platoon* i, db->platoons)
        {
            ui->tableWidget->setVerticalHeaderItem(j, new QTableWidgetItem(QString::number(i->getId())));
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(QString::number(i->getYear())));
            ui->tableWidget->setItem(j, 1, new QTableWidgetItem(QString::number(i->getManCount())));
            ui->tableWidget->setItem(j, 2, new QTableWidgetItem(QString::number(i->getStreamNumber())));
            ui->tableWidget->setItem(j, 3, new QTableWidgetItem(QString::number(i->getHalfPlatoonsCount())));
            ui->tableWidget->setItem(j, 4, new QTableWidgetItem(QString::number(i->getVus())));
            j++;
        }
        ui->tableWidget->setItem(j, 1, new QTableWidgetItem(QString::number(0)));
        ui->tableWidget->setItem(j, 0, new QTableWidgetItem(QString::number(2000)));
        ui->tableWidget->setItem(j, 3, new QTableWidgetItem(QString::number(0)));
        ui->tableWidget->setItem(j, 2, new QTableWidgetItem(QString::number(0)));
        ui->tableWidget->setItem(j, 4, new QTableWidgetItem(QString::number(0)));
        break;
    }
    ui->tableWidget->setVerticalHeaderItem(j, new QTableWidgetItem(QString("*")));
    //for (int i=0; i<ui->tableWidget->rowCount(); i++)
    //{
    //    for (int j = 0; j < ui->tableWidget->colorCount();j++)
    //    ui->tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
    //}
}

void WindowChange::on_deleteButton_clicked()
{
    DataBase* db = ((PlanWindow*)parent())->db;
    switch (ui->comboBox->currentIndex())
    {
    case 0:
        if (ui->tableWidget->currentRow()<db->professors.size() && ui->tableWidget->currentRow()>=0)
        {
            db->professors[ui->tableWidget->currentRow()]->remove();
        }
        break;
    case 1:
        if (ui->tableWidget->currentRow()<db->disciplines.size() && ui->tableWidget->currentRow()>=0)
        {
            db->disciplines[ui->tableWidget->currentRow()]->remove();
        }
        break;
    case 2:
        if (ui->tableWidget->currentRow()<db->extraDuties.size() && ui->tableWidget->currentRow()>=0)
        {
            db->extraDuties[ui->tableWidget->currentRow()]->remove();
        }
        break;
    case 3:
        if (ui->tableWidget->currentRow()<db->platoons.size() && ui->tableWidget->currentRow()>=0)
        {
            db->platoons[ui->tableWidget->currentRow()]->remove();
        }
        break;
    }

    db->reload();
    Fill(ui->comboBox->currentIndex());

}
