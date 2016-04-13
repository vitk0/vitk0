#include "thematicplan.h"

int ThematicPlan::getId() const
{
    return id;
}

void ThematicPlan::setId(int value)
{
    id = value;
}

int ThematicPlan::getVkUvc() const
{
    return vkUvc;
}

void ThematicPlan::setVkUvc(int value)
{
    vkUvc = value;
}

int ThematicPlan::getVus() const
{
    return vus;
}

void ThematicPlan::setVus(int value)
{
    vus = value;
}

Discipline *ThematicPlan::getDiscipline() const
{
    return discipline;
}

void ThematicPlan::setDiscipline(Discipline *value)
{
    discipline = new Discipline(value->getId(),value->getName());
}

int ThematicPlan::getSemester() const
{
    return semester;
}

void ThematicPlan::setSemester(int value)
{
    semester = value;
}

ThematicPlan::~ThematicPlan()
{
    delete discipline;
}

ThematicPlan::ThematicPlan(int id, int vkUvc, int vus, int semester,
                           Discipline *discipline)
{
    this->id = id;
    this->vkUvc = vkUvc;
    this->vus = vus;
    this->semester = semester;
    this->discipline = new Discipline(discipline->getId(), discipline->getName());

    connect();

    query.prepare("SELECT DISTINCT id_classes, number, class_type.id_class_type,\
                   class_type.name, hours FROM classes JOIN class_type\
                   ON class_type.id_class_type = classes.id_type \
                   WHERE id_thematic_plan=(?)");
    query.addBindValue(id);
    query.exec();
    while (query.next())
    {
        classes.push_back(new Class(query.value(0).toInt(), query.value(1).toInt(),
                                    new ClassType(query.value(2).toInt(), query.value(3).toString()),
                                    query.value(4).toInt()));
    }
    close();
}

QVector<Class *> ThematicPlan::getClasses() const
{
    return classes;
}

int ThematicPlan::classesCount()
{
    return classes.size();
}
