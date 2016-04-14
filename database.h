#ifndef DATABASE_H
#define DATABASE_H

#include <QVector>

#include "connect.h"
#include "discipline.h"
#include "platoon.h"
#include "professor.h"
#include "thematicplan.h"

class DataBase: public Connect
{
public:
    DataBase();

    QVector<int> currentVuses;
    QVector<int> currentSemesters;
    QVector<Discipline*> currentDisciplines;
    QVector<Platoon*> currentPlatoons;

    ThematicPlan* currentThematicPlan;

    QVector<ClassType*> classTypes;
    QVector<Professor*> professors;

    void GetVuses(int vkUvc);
    void GetSemesters(int vkUvc, int vus);
    void GetDisciplines(int vkUvc, int vus, int semester);
    void GetPlatoons(int vkUvc, int vus, int semester, Discipline* discipline);
    void GetThematicPlan(int vkUvc, int vus, int semester, Discipline* discipline);
};

#endif // DATABASE_H
