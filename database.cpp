#include "database.h"

DataBase::DataBase()
{
    currentThematicPlan = nullptr;

    connect();

    query.prepare("SELECT * FROM class_type");
    query.exec();

    while (query.next())
    {
        classTypes.push_back(new ClassType(query.value(0).toInt(), query.value(1).toString()));
    }

    close();

    connect();

    query.prepare("SELECT * FROM professors");
    query.exec();

    while (query.next())
    {
        professors.push_back(new Professor(query.value(0).toInt(), query.value(1).toString()));
    }

    close();
}

void DataBase::GetVuses(int vkUvc)
{
    currentVuses.clear();

    connect();

    query.prepare("SELECT DISTINCT vus FROM thematic_plan WHERE vk_uvc=(?)");
    query.addBindValue(vkUvc);
    query.exec();

    while (query.next())
    {
        currentVuses.push_back(query.value(0).toInt());
    }

    close();
}

void DataBase::GetSemesters(int vkUvc, int vus)
{
    currentSemesters.clear();

    connect();

    query.prepare("SELECT DISTINCT semester FROM thematic_plan WHERE vk_uvc=(?) AND vus=(?)");
    query.addBindValue(vkUvc);
    query.addBindValue(vus);
    query.exec();

    while (query.next())
    {
        currentSemesters.push_back(query.value(0).toInt());
    }

    close();

}

void DataBase::GetDisciplines(int vkUvc, int vus, int semester)
{
    foreach (Discipline* i, currentDisciplines) {
        delete i;
    }
    currentDisciplines.clear();

    connect();

    query.prepare("SELECT DISTINCT disciplines.id_disciplines, disciplines.name FROM thematic_plan \
                   JOIN disciplines ON disciplines.id_disciplines = thematic_plan.id_disciplines \
                   WHERE vk_uvc=(?) AND vus=(?) AND semester=(?)");
    query.addBindValue(vkUvc);
    query.addBindValue(vus);
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

void DataBase::GetThematicPlan(int vkUvc, int vus, int semester, Discipline *discipline)
{
    if (currentThematicPlan!= nullptr)
        delete currentThematicPlan;

    connect();

    query.prepare("SELECT DISTINCT id_thematic_plan FROM thematic_plan \
                   WHERE vk_uvc=(?) AND vus=(?) AND semester=(?) AND id_disciplines=(?)");
    query.addBindValue(vkUvc);
    query.addBindValue(vus);
    query.addBindValue(semester);
    query.addBindValue(discipline->getId());
    query.exec();

    query.next();
    currentThematicPlan = new ThematicPlan(query.value(0).toInt(), vkUvc, vus, semester, discipline);
    close();
}
