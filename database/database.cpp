#include "database.h"

#include <QAxObject>

DataBase::DataBase()
{
    currentThematicPlan = nullptr;
    reload();
}

void DataBase::GetVuses(int vkUvc)
{
    currentPlatoons.clear();

    connect();

    query.prepare("SELECT DISTINCT platoons.id_platoons, platoons.year, platoons.count_man, platoons.number_of_stream,\
                   platoons.count_half_platoons, platoons.vus FROM thematic_plan JOIN platoons ON thematic_plan.id_platoons = platoons.id_platoons WHERE vk_uvc=(?)");
    query.addBindValue(vkUvc);
    query.exec();

    while (query.next())
    {
        currentPlatoons.push_back(new Platoon(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toInt()));
    }

    close();
}

void DataBase::GetSemesters(int vkUvc, Platoon* platoon)
{
    currentSemesters.clear();

    connect();

    query.prepare("SELECT DISTINCT semester FROM thematic_plan JOIN platoons ON thematic_plan.id_platoons = platoons.id_platoons\
                  WHERE vk_uvc=(?) AND platoons.vus=(?)");
    query.addBindValue(vkUvc);
    query.addBindValue(platoon->getVus());
    query.exec();

    while (query.next())
    {
        currentSemesters.push_back(query.value(0).toInt());
    }

    close();

}

void DataBase::GetDisciplines(int vkUvc, Platoon *platoon, int semester)
{
    foreach (Discipline* i, currentDisciplines) {
        delete i;
    }
    currentDisciplines.clear();

    connect();

    query.prepare("SELECT DISTINCT disciplines.id_disciplines, disciplines.name FROM thematic_plan \
                   JOIN disciplines ON disciplines.id_disciplines = thematic_plan.id_disciplines \
                   JOIN platoons ON thematic_plan.id_platoons = platoons.id_platoons\
                   WHERE vk_uvc=(?) AND platoons.vus=(?) AND semester=(?)");
    query.addBindValue(vkUvc);
    query.addBindValue(platoon->getVus());
    query.addBindValue(semester);
    query.exec();

    while (query.next())
    {
        currentDisciplines.push_back(new Discipline(query.value(0).toInt(), query.value(1).toString()));
    }

    close();

}

void DataBase::GetPlatoons(int vkUvc, int vus, int semester, Discipline *discipline)
{

}

void DataBase::GetThematicPlan(int vkUvc, Platoon *platoon, int semester, Discipline *discipline)
{
    if (currentThematicPlan!= nullptr)
        delete currentThematicPlan;

    connect();

    query.prepare("SELECT DISTINCT id_thematic_plan FROM thematic_plan \
                   JOIN platoons ON thematic_plan.id_platoons = platoons.id_platoons\
                   WHERE vk_uvc=(?) AND platoons.vus=(?) AND semester=(?) AND id_disciplines=(?)");
    query.addBindValue(vkUvc);
    query.addBindValue(platoon->getVus());
    query.addBindValue(semester);
    query.addBindValue(discipline->getId());
    query.exec();

    query.next();
    currentThematicPlan = new ThematicPlan(query.value(0).toInt(), vkUvc, discipline, semester, platoon);
    close();
}

void DataBase::GenerateReport()
{
       QAxObject* excel = new QAxObject( "Excel.Application", 0 );
       QAxObject* workbooks = excel->querySubObject( "Workbooks" );

       int headerHeight = 7;
       int currentRow = headerHeight;

     //  excel->setProperty("Visible", true);

      // workbooks->dynamicCall("Add");

       workbooks->dynamicCall("Open (const QString&)",QDir::currentPath().replace("/","\\")+QString("\\1.xls"));

       QAxObject * workbook = excel->querySubObject("ActiveWorkBook");
       QAxObject* sheets = workbook->querySubObject( "Worksheets" );

       int count = 1;// count = sheets->property("Count").toInt();

       for (int i=1; i<=count; i++) //cycle through sheets
        {

           //sheet pointer

           QAxObject* sheet = sheets->querySubObject( "Item( int )", i );

           QAxObject* cell = sheet->querySubObject("Cells(QVariant,QVariant)", 1, 1);

           for (int i = 0; i<professors.size();i++)
           {
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 1);
               cell->setProperty("Value", QString::number(i+1));
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 2);
               QString temp;
               foreach (ExtraDuty* i, professors[i]->getExtraDuties())
               {
                   temp+= i->getDutyName()+QString(" ");
               }

               cell->setProperty("Value", temp+QString("\n\n")+professors[i]->getName());

               int resultlection = 0;
               int resultpractic = 0;
               int resulthalf = 0;
               int resultlectiontry = 0;
               int resultpractictry = 0;
               int resultconsult = 0;

               double resultcontrol = 0;
               double resultzachet = 0;
               double resultexam = 0;
               int resultduty = 0;

               connect();

               query.prepare("SELECT DISTINCT thematic_plan.vk_uvc, platoons.vus, disciplines.name\
                              FROM classes_professors JOIN classes ON classes_professors.id_classes=classes.id_classes\
                              JOIN thematic_plan ON classes.id_thematic_plan = thematic_plan.id_thematic_plan\
                              JOIN platoons ON platoons.id_platoons = thematic_plan.id_platoons\
                              JOIN professors ON classes_professors.id_professors = professors.id_professors\
                              JOIN disciplines ON thematic_plan.id_disciplines=disciplines.id_disciplines \
                              WHERE professors.id_professors = (?) ORDER BY platoons.vus");
                       query.addBindValue(professors[i]->getId());
               query.exec();
               close();
               while (query.next())
               {
                   cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 3);
                   cell->setProperty("Value", query.value(2).toString()+QString("(")+query.value(1).toString()+QString(")"));

                   QSqlQuery queryTemp;
                   connect();
                   queryTemp.prepare("SELECT DISTINCT thematic_plan.semester, platoons.count_half_platoons FROM classes_professors \
                                     JOIN classes ON classes_professors.id_classes=classes.id_classes\
                                     JOIN thematic_plan ON classes.id_thematic_plan = thematic_plan.id_thematic_plan\
                           JOIN platoons ON thematic_plan.id_platoons = platoons.id_platoons \
                                     JOIN professors ON classes_professors.id_professors = professors.id_professors\
                                     JOIN disciplines ON thematic_plan.id_disciplines=disciplines.id_disciplines \
                                     WHERE professors.id_professors = (?) AND thematic_plan.vk_uvc = (?)\
                                     AND platoons.vus = (?) AND disciplines.name = (?)");
                   queryTemp.addBindValue(professors[i]->getId());
                   queryTemp.addBindValue(query.value(0).toInt());
                   queryTemp.addBindValue(query.value(1).toInt());
                   queryTemp.addBindValue(query.value(2).toString());
                   queryTemp.exec();
                   close();



                   while (queryTemp.next())
                   {
                       cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 4);
                       cell->setProperty("Value", queryTemp.value(0).toInt());
                       cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 5);
                       cell->setProperty("Value", 1);
                       cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 6);
                       cell->setProperty("Value", 1);
                       cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 7);
                       cell->setProperty("Value", queryTemp.value(1).toInt());

                       QSqlQuery queryTemp2;
                       connect();
                       queryTemp2.prepare("SELECT DISTINCT classes.id_type, classes.hours, classes_professors.first_classes,\
                                         platoons.count_man, classes.id_classes FROM classes_professors \
                                           JOIN classes ON classes_professors.id_classes=classes.id_classes\
                                         JOIN thematic_plan ON classes.id_thematic_plan = thematic_plan.id_thematic_plan\
                                         JOIN platoons ON thematic_plan.id_platoons = platoons.id_platoons \
                                         JOIN professors ON classes_professors.id_professors = professors.id_professors\
                                         JOIN disciplines ON thematic_plan.id_disciplines=disciplines.id_disciplines \
                                         WHERE professors.id_professors = (?) AND thematic_plan.vk_uvc = (?)\
                                         AND platoons.vus = (?) AND disciplines.name = (?)");
                       queryTemp2.addBindValue(professors[i]->getId());
                       queryTemp2.addBindValue(query.value(0).toInt());
                       queryTemp2.addBindValue(query.value(1).toInt());
                       queryTemp2.addBindValue(query.value(2).toString());
                       queryTemp2.exec();
                       close();


                       int hourslection = 0;
                       int hourspractic = 0;
                       int hourshalf = 0;
                       int hourslectiontry = 0;
                       int hourspractictry = 0;
                       int hoursconsult = 0;

                       int countcontrol = 0;
                       double hourscontrol = 0;
                       int countzachet = 0;
                       double hourszachet = 0;
                       int countexam = 0;
                       double hoursexam = 0;



                       while (queryTemp2.next())
                       {
                           QSqlQuery queryTemp3;
                           connect();
                           queryTemp3.prepare("SELECT DISTINCT classes_professors.id_professors, COUNT(*) FROM classes\
                                                JOIN classes_professors ON classes.id_classes=classes_professors.id_classes\
                                                WHERE classes.id_classes =(?)");
                           queryTemp3.addBindValue(queryTemp2.value(4).toInt());
                           queryTemp3.exec();
                           queryTemp3.next();
                           close();

                           switch (queryTemp2.value(0).toInt())
                           {
                           case 2:
                               hourslection += queryTemp2.value(1).toInt();
                               if (queryTemp2.value(2).toBool())
                               {
                                   hourslectiontry += queryTemp2.value(1).toInt()*2;
                               }
                               else
                               {
                                   hourslectiontry += queryTemp2.value(1).toInt();
                               }
                               break;
                           case 1:
                               hourspractic += queryTemp2.value(1).toInt();
                               if (queryTemp2.value(2).toBool())
                               {
                                   hourspractictry += queryTemp2.value(1).toInt()*2;
                               }
                               else
                               {
                                   hourspractictry += queryTemp2.value(1).toInt();
                               }
                               break;
                           case 4:
                               hourshalf += queryTemp2.value(1).toInt();
                               if (queryTemp2.value(2).toBool())
                               {
                                   hourspractictry += queryTemp2.value(1).toInt()*2;
                               }
                               else
                               {
                                   hourspractictry += queryTemp2.value(1).toInt();
                               }
                               break;
                           case 6:
                               hoursconsult += queryTemp2.value(1).toInt();
                               break;
                           case 7:
                               countcontrol++;
                               hourscontrol += queryTemp2.value(3).toInt()*0.8;
                               break;
                           case 5:
                               countzachet++;

                               hourszachet += queryTemp2.value(1).toInt()/queryTemp3.value(1).toDouble();
                               break;
                           case 3:
                               countexam++;
                               hoursexam += queryTemp2.value(1).toInt()/queryTemp3.value(1).toDouble();
                               break;
                           }
                       }
                        if (hourslection)
                        {
                            resultlection+=hourslection;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 9);
                            cell->setProperty("Value", hourslection);
                        }
                        if(hourspractic)
                        {
                            resultpractic+=hourspractic;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 11);
                            cell->setProperty("Value", hourspractic);
                        }
                        if(hourshalf)
                        {
                            resulthalf+=hourshalf;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 13);
                            cell->setProperty("Value", hourshalf);
                        }
                        cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 16);
                        cell->setProperty("Value", hourshalf+hourslection+hourspractic);
                        if (hoursconsult)
                        {
                            resultconsult+=hoursconsult;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 17);
                            cell->setProperty("Value", hoursconsult);
                        }
                        if (hourslectiontry)
                        {
                            resultlectiontry+=hourslectiontry;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 18);
                            cell->setProperty("Value", hourslectiontry);
                        }
                        if(hourspractictry)
                        {
                            resultpractictry+=hourspractictry;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 19);
                            cell->setProperty("Value", hourspractictry);
                        }
                        if (countcontrol)
                        {
                            resultcontrol+=hourscontrol;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 21);
                            cell->setProperty("Value", countcontrol);
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 22);
                            cell->setProperty("Value", hourscontrol);
                        }
                        if (countzachet)
                        {
                            resultzachet+=hourszachet;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 23);
                            cell->setProperty("Value", countzachet);
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 24);
                            cell->setProperty("Value", hourszachet);
                        }
                        if (countexam)
                        {
                            resultexam+=hoursexam;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 25);
                            cell->setProperty("Value", countexam);
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 26);
                            cell->setProperty("Value", hoursexam);
                        }
                        cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 31);
                        cell->setProperty("Value", hourszachet+hoursexam+hourscontrol+hoursconsult+hourslectiontry+hourspractictry);
                        cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 32);
                        cell->setProperty("Value", hourshalf+hourslection+hourspractic+hourszachet+hoursexam+hourscontrol+hoursconsult+hourslectiontry+hourspractictry);
                       currentRow++;
                   }

               }
               connect();
               query.prepare("SELECT extra_duty.position_name, extra_duty.hours FROM professors\
                                JOIN extra_duty ON professors.id_professors = extra_duty.id_professors\
                                WHERE professors.id_professors = (?)");
                       query.addBindValue(professors[i]->getId());
                       query.exec();
               close();
               while(query.next())
               {
                   cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 3);
                   cell->setProperty("Value", query.value(0).toString());
                   resultduty+=query.value(1).toInt();
                   cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 30);
                   cell->setProperty("Value", query.value(1).toString());
                   cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 31);
                   cell->setProperty("Value", query.value(1).toString());
                   cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 32);
                   cell->setProperty("Value", query.value(1).toString());
                   currentRow++;
               }
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 3);
               cell->setProperty("Value", QString("Итого уч. год"));
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 9);
               cell->setProperty("Value", resultlection);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 11);
               cell->setProperty("Value", resultpractic);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 13);
               cell->setProperty("Value", resulthalf);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 16);
               cell->setProperty("Value", resulthalf+resultlection+resultpractic);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 17);
               cell->setProperty("Value", resultconsult);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 18);
               cell->setProperty("Value", resultlectiontry);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 19);
               cell->setProperty("Value", resultpractictry);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 22);
               cell->setProperty("Value", resultcontrol);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 24);
               cell->setProperty("Value", resultzachet);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 26);
               cell->setProperty("Value", resultexam);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 31);
               cell->setProperty("Value", resultcontrol+resultlectiontry+resultpractictry+resultconsult+resultzachet+resultexam+resultduty);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 30);
               cell->setProperty("Value", resultduty);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 32);
               cell->setProperty("Value", resulthalf+resultlection+resultpractic+resultcontrol+resultlectiontry+resultpractictry+resultconsult+resultzachet+resultexam+resultduty);
               currentRow++;
           }

           QDateTime currTime = QDateTime::currentDateTime();
           workbook->dynamicCall("SaveAs (const QString&)", QDir::currentPath().replace("/","\\")+currTime.toString("dd.MM.yyyy_hh.mm.ss")+QString(".xls"));
           workbook->dynamicCall("Close()");
           excel->dynamicCall("Quit()");

       }
}

void DataBase::reload()
{
    connect();

    query.prepare("SELECT * FROM class_type");
    query.exec();

    classTypes.clear();
    while (query.next())
    {
        classTypes.push_back(new ClassType(query.value(0).toInt(), query.value(1).toString()));
    }

    close();

    connect();

    query.prepare("SELECT * FROM professors");
    query.exec();

    professors.clear();
    while (query.next())
    {
        professors.push_back(new Professor(query.value(0).toInt(), query.value(1).toString()));
    }

    close();

    connect();

    query.prepare("SELECT * FROM extra_duty");
    query.exec();

    extraDuties.clear();
    while (query.next())
    {
        extraDuties.push_back(new ExtraDuty(query.value(0).toInt(), query.value(1).toString(), query.value(2).toInt(),
                                            query.value(3).toString(), query.value(4).toInt()));
    }

    close();

    connect();

    query.prepare("SELECT * FROM disciplines");
    query.exec();

    disciplines.clear();
    while (query.next())
    {
        disciplines.push_back(new Discipline(query.value(0).toInt(), query.value(1).toString()));
    }

    close();

    connect();

    query.prepare("SELECT * FROM platoons");
    query.exec();

    platoons.clear();
    while (query.next())
    {
        platoons.push_back(new Platoon(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt(),
                                       query.value(4).toInt(), query.value(5).toInt()));
    }

    close();
}
