#ifndef THEMATICPLAN_H
#define THEMATICPLAN_H

#include <QVector>

#include "discipline.h"
#include "class.h"
#include "connect.h"
#include "platoon.h"

class ThematicPlan: public Connect
{
    int id;
    int vkUvc;
    Discipline* discipline;
    int semester;
    Platoon* platoon;
    QVector<Class*> classes;
public:
    ThematicPlan();
    ThematicPlan(int id, int vkUvc, Discipline* discipline, int semester, Platoon* platoon);
    int getId() const;
    void setId(int value);
    int getVkUvc() const;
    void setVkUvc(int value);
    Discipline *getDiscipline() const;
    void setDiscipline(Discipline *value);
    int getSemester() const;
    void setSemester(int value);

    ~ThematicPlan();
    QVector<Class *> getClasses() const;
    int classesCount();
};

#endif // THEMATICPLAN_H
