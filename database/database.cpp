#include "database.h"

#include <QAxObject>

DataBase::DataBase()
{
    currentThematicPlan = nullptr;
    reload();
}

void DataBase::GetVuses(int vkUvc)
{
    currentVuses.clear();

    Query("SELECT DISTINCT platoons.vus FROM thematic_plan JOIN platoons ON thematic_plan.id_platoons = platoons.id_platoons\
                        WHERE vk_uvc=(?)",
            vkUvc);
    while (query.next())
    {
        currentVuses.push_back(query.value(0).toInt());
    }
}

void DataBase::GetPlatoons(int vkUvc, int vus)
{
    currentPlatoons.clear();

    Query("SELECT DISTINCT platoons.id_platoons, platoons.year, platoons.count_man, platoons.number_of_stream,\
                         platoons.count_half_platoons FROM thematic_plan JOIN platoons ON thematic_plan.id_platoons = platoons.id_platoons WHERE vk_uvc=(?) AND platoons.vus=(?)",
          vkUvc, vus);

    while (query.next())
    {
        currentPlatoons.push_back(new Platoon(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toInt(),query.value(4).toInt(),vus));
    }

}

void DataBase::GetSemesters(int vkUvc, Platoon* platoon)
{
    currentSemesters.clear();

    Query("SELECT DISTINCT semester FROM thematic_plan JOIN platoons ON thematic_plan.id_platoons = platoons.id_platoons\
                        WHERE vk_uvc=(?) AND platoons.id_platoons=(?)",
            vkUvc, platoon->getId());
    while (query.next())
    {
        currentSemesters.push_back(query.value(0).toInt());
    }

}

void DataBase::GetDisciplines(int vkUvc, Platoon *platoon, int semester)
{
    foreach (Discipline* i, currentDisciplines) {
        delete i;
    }
    currentDisciplines.clear();

    Query("SELECT DISTINCT disciplines.id_disciplines, disciplines.name FROM thematic_plan \
                   JOIN disciplines ON disciplines.id_disciplines = thematic_plan.id_disciplines \
                   JOIN platoons ON thematic_plan.id_platoons = platoons.id_platoons\
                   WHERE vk_uvc=(?) AND platoons.id_platoons=(?) AND semester=(?)",
            vkUvc, platoon->getId(), semester);

    while (query.next())
    {
        currentDisciplines.push_back(new Discipline(query.value(0).toInt(), query.value(1).toString()));
    }

}

void DataBase::GetThematicPlan(int vkUvc, Platoon *platoon, int semester, Discipline *discipline)
{
    if (currentThematicPlan!= nullptr)
        delete currentThematicPlan;

    Query("SELECT DISTINCT id_thematic_plan FROM thematic_plan \
                   JOIN platoons ON thematic_plan.id_platoons = platoons.id_platoons\
                   WHERE vk_uvc=(?) AND platoons.id_platoons=(?) AND semester=(?) AND id_disciplines=(?)",
            vkUvc, platoon->getId(), semester, discipline->getId());

    query.next();
    currentThematicPlan = new ThematicPlan(query.value(0).toInt(), vkUvc, discipline, semester, platoon);
}

void DataBase::GenerateReport()
{
       QAxObject* excel = new QAxObject( "Excel.Application", 0 );
       QAxObject* workbooks = excel->querySubObject( "Workbooks" );

       int headerHeight = 7;
       int currentRow = headerHeight;


       QString file = QDir::currentPath().replace("/","\\")+QString("\\1.xls");
       workbooks->dynamicCall("Open (const QString&)", file);



       QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
       QAxObject* sheets = workbook->querySubObject( "Worksheets" );

       int count = 1;

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

               int resultlection[3] = {0};
               int resultpractic[3] = {0};
               int resulthalf[3] = {0};
               int resultlectiontry[3] = {0};
               int resultpractictry[3] = {0};
               double resultconsult[3] = {0};

               double resultcontrol[3] = {0};
               double resultzachet[3] = {0};
               double resultexam[3] = {0};
               int resultduty = 0;
               int resulttrman = 0;
               int resultfinexam = 0;
               int resultselfstudy = 0;
               int resultattestation[3] = {0};

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
                   queryTemp.prepare("SELECT DISTINCT thematic_plan.semester, platoons.count_half_platoons, platoons.year, platoons.count_man FROM classes_professors \
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
                       cell->setProperty("Value", QString::number((2015-queryTemp.value(2).toInt())) +QString("(")+queryTemp.value(0).toString()+QString(")"));
                       cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 5);
                       cell->setProperty("Value", 1);
                       cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 6);
                       cell->setProperty("Value", 1);
                       cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 7);
                       cell->setProperty("Value", queryTemp.value(1).toInt());
                       cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 8);
                       cell->setProperty("Value", queryTemp.value(3).toInt());

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
                       double hoursconsult = 0;

                       int countcontrol = 0;
                       double hourscontrol = 0;
                       int countzachet = 0;
                       double hourszachet = 0;
                       int countexam = 0;
                       double hoursexam = 0;
                       int hoursattestation = 0;

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
                               hoursattestation += queryTemp2.value(1).toInt();
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
                            resultlection[0]+=hourslection;
                            resultlection[queryTemp.value(0).toInt()]+=hourslection;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 9);
                            cell->setProperty("Value", hourslection);
                        }
                        if(hourspractic)
                        {
                            resultpractic[0]+=hourspractic;
                            resultpractic[queryTemp.value(0).toInt()]+=hourspractic;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 11);
                            cell->setProperty("Value", hourspractic);
                        }
                        if(hourshalf)
                        {
                            resulthalf[0]+=hourshalf;
                            resulthalf[queryTemp.value(0).toInt()]+=hourshalf;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 13);
                            cell->setProperty("Value", hourshalf);
                        }
                        cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 16);
                        cell->setProperty("Value", hourshalf+hourslection+hourspractic);
                        if (hourslectiontry)
                        {
                            resultlectiontry[0]+=hourslectiontry;
                            resultlectiontry[queryTemp.value(0).toInt()]+=hourslectiontry;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 18);
                            cell->setProperty("Value", hourslectiontry);
                        }
                        if(hourspractictry)
                        {
                            resultpractictry[0]+=hourspractictry;
                            resultpractictry[queryTemp.value(0).toInt()]+=hourspractictry;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 19);
                            cell->setProperty("Value", hourspractictry);
                        }
                        if(hoursattestation)
                        {
                            resultattestation[0]+=hoursattestation;
                            resultattestation[queryTemp.value(0).toInt()]+=hoursattestation;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 27);
                            cell->setProperty("Value", hoursattestation);
                        }
                        if (countcontrol)
                        {
                            resultcontrol[0]+=hourscontrol;
                            resultcontrol[queryTemp.value(0).toInt()]+=hourscontrol;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 21);
                            cell->setProperty("Value", countcontrol);
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 22);
                            cell->setProperty("Value", hourscontrol);
                        }
                        if (countzachet)
                        {
                            resultzachet[0]+=hourszachet;
                            resultzachet[queryTemp.value(0).toInt()]+=hourszachet;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 23);
                            cell->setProperty("Value", countzachet);
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 24);
                            cell->setProperty("Value", hourszachet);
                        }
                        if (countexam)
                        {
                            resultexam[0]+=hoursexam;
                            resultexam[queryTemp.value(0).toInt()]+=hoursexam;
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 25);
                            cell->setProperty("Value", countexam);
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 26);
                            cell->setProperty("Value", hoursexam);
                        }
                        hoursconsult+= hourslection*0.15+(hourshalf+hourspractic)*0.1;
                        resultconsult[0]+=hoursconsult;
                        resultconsult[queryTemp.value(0).toInt()]+=hoursconsult;
                        cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 17);
                        cell->setProperty("Value", hoursconsult);
                        cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 31);
                        cell->setProperty("Value", hourszachet+hoursexam+hourscontrol+hoursconsult+hourslectiontry+hourspractictry+hoursattestation);
                        cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 32);
                        cell->setProperty("Value", hourshalf+hourslection+hourspractic+hourszachet+hoursexam+hourscontrol+hoursconsult+hourslectiontry+hourspractictry+hoursattestation);
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
               connect();
               query.prepare("SELECT training_sessions.training_management, training_sessions.final_examenation, training_sessions.self_study_management FROM professors\
                                JOIN training_sessions ON professors.id_professors = training_sessions.id_professors\
                                WHERE professors.id_professors = (?)");
                       query.addBindValue(professors[i]->getId());
                       query.exec();
               close();
               while(query.next())
               {
                   cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 3);
                   cell->setProperty("Value", QString("Учебные сборы"));
                   cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 20);
                   cell->setProperty("Value", query.value(0).toString());
                   resulttrman+=query.value(0).toInt();
                   cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 27);
                   cell->setProperty("Value", query.value(1).toString());
                   resultfinexam+=query.value(1).toInt();
                   cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 28);
                   cell->setProperty("Value", query.value(2).toString());
                   resultselfstudy+=query.value(2).toInt();
                   cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 31);
                   cell->setProperty("Value", query.value(0).toInt()+query.value(1).toInt()+query.value(2).toInt());
                   cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 32);
                   cell->setProperty("Value", query.value(0).toInt()+query.value(1).toInt()+query.value(2).toInt());
                   currentRow++;
               }
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 3);
               cell->setProperty("Value", QString("Итого 1 семестр"));
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 9);
               cell->setProperty("Value", resultlection[1]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 11);
               cell->setProperty("Value", resultpractic[1]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 13);
               cell->setProperty("Value", resulthalf[1]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 16);
               cell->setProperty("Value", resulthalf[1]+resultlection[1]+resultpractic[1]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 17);
               cell->setProperty("Value", resultconsult[1]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 18);
               cell->setProperty("Value", resultlectiontry[1]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 19);
               cell->setProperty("Value", resultpractictry[1]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 22);
               cell->setProperty("Value", resultcontrol[1]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 24);
               cell->setProperty("Value", resultzachet[1]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 26);
               cell->setProperty("Value", resultexam[1]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 27);
               cell->setProperty("Value", resultattestation[1]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 31);
               cell->setProperty("Value", resultcontrol[1]+resultlectiontry[1]+resultpractictry[1]+resultconsult[1]+resultzachet[1]+resultexam[1]+resultduty/2.0+resulttrman/2.0+resultfinexam/2.0+resultselfstudy/2.0+resultattestation[1]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 30);
               cell->setProperty("Value", resultduty/2.0);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 20);
               cell->setProperty("Value", resulttrman/2.0);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 27);
               cell->setProperty("Value", resultfinexam/2.0);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 28);
               cell->setProperty("Value", resultselfstudy/2.0);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 32);
               cell->setProperty("Value", resulthalf[1]+resultlection[1]+resultpractic[1]+resultcontrol[1]+resultlectiontry[1]+resultpractictry[1]+resultconsult[1]+resultzachet[1]+resultexam[1]+resultattestation[1]+resultduty/2.0+resulttrman/2.0+resultfinexam/2.0+resultselfstudy/2.0);
               currentRow++;
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 3);
               cell->setProperty("Value", QString("Итого 2 семестр"));
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 9);
               cell->setProperty("Value", resultlection[2]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 11);
               cell->setProperty("Value", resultpractic[2]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 13);
               cell->setProperty("Value", resulthalf[2]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 16);
               cell->setProperty("Value", resulthalf[2]+resultlection[2]+resultpractic[2]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 17);
               cell->setProperty("Value", resultconsult[2]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 18);
               cell->setProperty("Value", resultlectiontry[2]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 19);
               cell->setProperty("Value", resultpractictry[2]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 22);
               cell->setProperty("Value", resultcontrol[2]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 24);
               cell->setProperty("Value", resultzachet[2]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 26);
               cell->setProperty("Value", resultexam[2]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 27);
               cell->setProperty("Value", resultattestation[2]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 31);
               cell->setProperty("Value", resultcontrol[2]+resultlectiontry[2]+resultattestation[2]+resultpractictry[2]+resultconsult[2]+resultzachet[2]+resultexam[2]+resultduty/2.0+resulttrman/2.0+resultfinexam/2.0+resultselfstudy/2.0);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 30);
               cell->setProperty("Value", resultduty/2.0);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 20);
               cell->setProperty("Value", resulttrman/2.0);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 27);
               cell->setProperty("Value", resultfinexam/2.0);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 28);
               cell->setProperty("Value", resultselfstudy/2.0);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 32);
               cell->setProperty("Value", resulthalf[2]+resultlection[2]+resultattestation[2]+resultpractic[2]+resultcontrol[2]+resultlectiontry[2]+resultpractictry[2]+resultconsult[2]+resultzachet[2]+resultexam[2]+resultduty/2.0+resulttrman/2.0+resultfinexam/2.0+resultselfstudy/2.0);
               currentRow++;
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 3);
               cell->setProperty("Value", QString("Итого уч. год"));
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 9);
               cell->setProperty("Value", resultlection[0]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 11);
               cell->setProperty("Value", resultpractic[0]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 13);
               cell->setProperty("Value", resulthalf[0]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 16);
               cell->setProperty("Value", resulthalf[0]+resultlection[0]+resultpractic[0]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 17);
               cell->setProperty("Value", resultconsult[0]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 18);
               cell->setProperty("Value", resultlectiontry[0]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 19);
               cell->setProperty("Value", resultpractictry[0]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 22);
               cell->setProperty("Value", resultcontrol[0]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 24);
               cell->setProperty("Value", resultzachet[0]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 26);
               cell->setProperty("Value", resultexam[0]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 27);
               cell->setProperty("Value", resultattestation[0]);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 31);
               cell->setProperty("Value", resultcontrol[0]+resultlectiontry[0]+resultattestation[0]+resultpractictry[0]+resultconsult[0]+resultzachet[0]+resultexam[0]+resultduty+resulttrman+resultfinexam+resultselfstudy);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 30);
               cell->setProperty("Value", resultduty);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 20);
               cell->setProperty("Value", resulttrman);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 27);
               cell->setProperty("Value", resultfinexam);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 28);
               cell->setProperty("Value", resultselfstudy);
               cell = sheet->querySubObject("Cells(QVariant,QVariant)", currentRow, 32);
               cell->setProperty("Value", resulthalf[0]+resultlection[0]+resultattestation[0]+resultpractic[0]+resultcontrol[0]+resultlectiontry[0]+resultpractictry[0]+resultconsult[0]+resultzachet[0]+resultexam[0]+resultduty+resulttrman+resultfinexam+resultselfstudy);
               currentRow++;
           }

           QDateTime currTime = QDateTime::currentDateTime();
           workbook->dynamicCall("SaveAs (const QString&)", QDir::currentPath().replace("/","\\")+QString("\\")+currTime.toString("dd.MM.yyyy_hh.mm.ss")+QString(".xls"));

           excel->dynamicCall( "SetVisible(bool)", true );

       }
}

void DataBase::reload()
{
    Query("SELECT * FROM class_type");

    classTypes.clear();
    while (query.next())
    {
        classTypes.push_back(new ClassType(query.value(0).toInt(), query.value(1).toString()));
    }

    Query("SELECT * FROM professors");

    professors.clear();
    while (query.next())
    {
        professors.push_back(new Professor(query.value(0).toInt(), query.value(1).toString()));
    }

    Query("SELECT * FROM extra_duty");

    extraDuties.clear();
    while (query.next())
    {
        extraDuties.push_back(new ExtraDuty(query.value(0).toInt(), query.value(1).toString(), query.value(2).toInt(),
                                            query.value(3).toString(), query.value(4).toInt()));
    }

    Query("SELECT * FROM disciplines");

    disciplines.clear();
    while (query.next())
    {
        disciplines.push_back(new Discipline(query.value(0).toInt(), query.value(1).toString()));
    }

    Query("SELECT * FROM platoons");

    platoons.clear();
    while (query.next())
    {
        platoons.push_back(new Platoon(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt(),
                                       query.value(4).toInt(), query.value(5).toInt()));
    }

    Query("SELECT * FROM training_sessions");

    trainingSessions.clear();
    while (query.next())
    {
        trainingSessions.push_back(new TrainingSession(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt(),
                                       query.value(4).toInt()));
    }
}
