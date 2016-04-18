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

Ui::PlanWindow *PlanWindow::GetUI()
{
    return ui;
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

void PlanWindow::Fill()
{
    db->GetThematicPlan(ui->VkUvcComboBox->currentIndex()+1, db->currentVuses[ui->VUSComboBox->currentIndex()],
            db->currentSemesters[ui->semesterComboBox->currentIndex()], db->currentDisciplines[ui->disciplineComboBox->currentIndex()] );
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

           /*
           for (int row=2; query.next(); row++)
           {

               QSqlQuery query1;
               con();
               query1.prepare("SELECT DISTINCT thematic_plan.vk_uvc, thematic_plan.vus, thematic_plan.semester\
                             FROM classes JOIN thematic_plan ON classes.id_thematic_plan = thematic_plan.id_thematic_plan \
                             WHERE (classes.id_professor1=(?)) OR (classes.id_professor2=(?))");
               query1.addBindValue(query.value(0));
               query1.addBindValue(query.value(0));
               query1.exec();
               while (query1.next())
               {

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 2);
               if(query1.value(0).toInt()==1){
               cell->setProperty("Value", QVariant("ВК"));
               }else
               {
               cell->setProperty("Value", QVariant("УВЦ"));
               }
               delete cell;

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 3);
               cell->setProperty("Value", QVariant(query1.value(1).toString()));
               delete cell;

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 4);
               cell->setProperty("Value", QVariant(query1.value(2).toInt()));
               delete cell;

               int currentvk = query1.value(0).toInt();
               QString currentvus = query1.value(1).toString();
               int currentsem = query1.value(2).toInt();
               db.close();
               con();
               QSqlQuery query2;
               query2.prepare("(SELECT id_type, hours, first_class1, id_professor1 FROM classes \
                               JOIN thematic_plan ON classes.id_thematic_plan = thematic_plan.id_thematic_plan\
                               WHERE thematic_plan.vk_uvc = (?) AND thematic_plan.vus = (?) AND thematic_plan.semester = (?) AND id_professor1=(?))\
                               UNION ALL\
                               (SELECT id_type, hours, first_class2, id_professor2 FROM classes \
                                JOIN thematic_plan ON classes.id_thematic_plan = thematic_plan.id_thematic_plan\
                               WHERE thematic_plan.vk_uvc = (?) AND thematic_plan.vus = (?) AND thematic_plan.semester = (?) AND id_professor2=(?))");
               query2.addBindValue(currentvk);
               query2.addBindValue(currentvus);
               query2.addBindValue(currentsem);
               query2.addBindValue(query.value(0));
               query2.addBindValue(currentvk);
               query2.addBindValue(currentvus);
               query2.addBindValue(currentsem);
               query2.addBindValue(query.value(0));
               query2.exec();
               db.close();
               int hourslection = 0;
               int hourspractic = 0;
               int hourslectiontry = 0;
               int hourspractictry = 0;
               int hourshalf = 0;
               int hourscontrol = 0;
               int hourszachet = 0;
               int hoursexam = 0;

               while (query2.next())
               {
                   switch (query2.value(0).toInt())
                   {
                   case 1:
                       hourslection += query2.value(1).toInt();
                       if (query2.value(2).toBool())
                       {
                           hourslectiontry += query2.value(1).toInt()*2;
                       }
                       else
                       {
                           hourslectiontry += query2.value(1).toInt();
                       }
                       break;
                   case 2:
                       hourspractic += query2.value(1).toInt();
                       if (query2.value(2).toBool())
                       {
                           hourspractictry += query2.value(1).toInt()*2;
                       }
                       else
                       {
                           hourspractictry += query2.value(1).toInt();
                       }
                       break;
                   case 3:
                       hourshalf += query2.value(1).toInt();
                       if (query2.value(2).toBool())
                       {
                           hourspractictry += query2.value(1).toInt()*2;
                       }
                       else
                       {
                           hourspractictry += query2.value(1).toInt();
                       }
                       break;
                   case 4:
                       hourscontrol += query2.value(1).toInt();
                       break;
                   case 5:
                       hourszachet += query2.value(1).toInt();
                       break;
                   case 6:
                       hoursexam += query2.value(1).toInt();
                       break;
                   }
               }
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 5);
               cell->setProperty("Value", QVariant(hourslection));
               delete cell;

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 6);
               cell->setProperty("Value", QVariant(hourspractic));
               delete cell;

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 7);
               cell->setProperty("Value", QVariant(hourshalf));
               delete cell;

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 8);
               cell->setProperty("Value", QVariant(hourshalf+hourspractic+hourslection));
               delete cell;

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 9);
               cell->setProperty("Value", QVariant(hourslectiontry));
               delete cell;

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 10);
               cell->setProperty("Value", QVariant(hourspractictry));
               delete cell;

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 11);
               cell->setProperty("Value", QVariant(hourscontrol));
               delete cell;

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 12);
               cell->setProperty("Value", QVariant(hourszachet));
               delete cell;

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 13);
               cell->setProperty("Value", QVariant(hoursexam));
               delete cell;

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 14);
               cell->setProperty("Value", QVariant(hourslectiontry+hourspractictry));
               delete cell;

               cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, 15);
               cell->setProperty("Value", QVariant(hourslectiontry+hourspractictry+hourshalf+hourspractic+hourslection+hourscontrol+hourszachet+hoursexam));
               delete cell;
               row++;
               }
           }
       }*/

       // workbook->dynamicCall("Save()");

}
