#include "classes_professors.h"

int classes_professors::getId() const
{
    return id;
}

void classes_professors::setId(int value)
{
    id = value;
}

int classes_professors::getIdClass() const
{
    return idClass;
}

void classes_professors::setIdClass(int value)
{
    idClass = value;
}

bool classes_professors::getFirstTime() const
{
    return firstTime;
}

void classes_professors::setFirstTime(bool value)
{
    firstTime = value;
}

int classes_professors::getIdProfessor() const
{
    return idProfessor;
}

void classes_professors::setIdProfessor(int value)
{
    idProfessor = value;
}

QString classes_professors::getName() const
{
    return name;
}

void classes_professors::setName(const QString &value)
{
    name = value;
}

classes_professors::classes_professors(int id, int idClass, bool firstTime, int idProfessor, QString name)
{
    this->id = id;
    this->idClass = idClass;
    this->firstTime = firstTime;
    this->idProfessor = idProfessor;
    this->name = name;
}
