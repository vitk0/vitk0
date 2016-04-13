#include "discipline.h"

int Discipline::getId() const
{
    return id;
}

void Discipline::setId(int value)
{
    id = value;
}

QString Discipline::getName() const
{
    return name;
}

void Discipline::setName(const QString &value)
{
    name = value;
}

Discipline::Discipline(int id, QString name)
{
    this->id = id;
    this->name = name;
}
