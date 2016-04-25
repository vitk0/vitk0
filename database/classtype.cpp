#include "classtype.h"

int ClassType::getId() const
{
    return id;
}

void ClassType::setId(int value)
{
    id = value;
}

QString ClassType::getName() const
{
    return name;
}

void ClassType::setName(const QString &value)
{
    name = value;
}

ClassType::ClassType(int id, QString name)
{
    this->id = id;
    this->name = name;
}
