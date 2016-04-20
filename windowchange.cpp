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
    DataBase* db = ((PlanWindow*)parent())->db;
    switch (index)
    {
        case 0:
            ui->tableWidget->clear();
            ui->tableWidget->setColumnCount(1);
            ui->tableWidget->setRowCount(db->professors.size()+1);
            int j = 0;
            foreach (Professor* i, db->professors)
            {
                ui->tableWidget->setItem(j, 0, new QTableWidgetItem(i->getName()));
                j++;
            }
    }
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
        } else
        if (ui->tableWidget->currentRow()>=0)
        {
            Professor* temp = new Professor(0,ui->tableWidget->item(row,column)->text());
            db->professors[row]->update(temp);
        }
    }

}
