#ifndef DATABASE_H
#define DATABASE_H

#include <QVector>

#include "connect.h"
#include "discipline.h"
#include "platoon.h"
#include "professor.h"
#include "thematicplan.h"
#include "trainingsession.h"

class DataBase: public Connect
{
public:
    DataBase();

    QVector<int> currentSemesters;
    QVector<int> currentVuses;
    QVector<Discipline*> currentDisciplines;
    QVector<Platoon*> currentPlatoons;

    ThematicPlan* currentThematicPlan;

    QVector<ClassType*> classTypes;
    QVector<Professor*> professors;
    QVector<ExtraDuty*> extraDuties;
    QVector<Discipline*> disciplines;
    QVector<Platoon*> platoons;
    QVector<TrainingSession*> trainingSessions;

    void GetVuses(int vkUvc);
    void GetPlatoons(int vkUvc, int vus);
    void GetSemesters(int vkUvc, Platoon *platoon);
    void GetDisciplines(int vkUvc, Platoon *platoon, int semester);
    void GetThematicPlan(int vkUvc, Platoon *platoon, int semester, Discipline* discipline);

    void GenerateReport();

    void reload();
};

#endif // DATABASE_H
