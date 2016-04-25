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

    QVector<int> currentSemesters;
    QVector<Discipline*> currentDisciplines;
    QVector<Platoon*> currentPlatoons;

    ThematicPlan* currentThematicPlan;

    QVector<ClassType*> classTypes;
    QVector<Professor*> professors;
    QVector<ExtraDuty*> extraDuties;
    QVector<Discipline*> disciplines;
    QVector<Platoon*> platoons;

    void GetVuses(int vkUvc);
    void GetSemesters(int vkUvc, Platoon *platoon);
    void GetDisciplines(int vkUvc, Platoon *platoon, int semester);
    void GetPlatoons(int vkUvc, int vus, int semester, Discipline* discipline);
    void GetThematicPlan(int vkUvc, Platoon *platoon, int semester, Discipline* discipline);

    void GenerateReport();

    void reload();
};

#endif // DATABASE_H
