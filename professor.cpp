#include "professor.h"

int Professor::getId() const
{
    return id;
}

void Professor::setId(int value)
{
    id = value;
}

QString Professor::getName() const
{
    return name;
}

void Professor::setName(const QString &value)
{
    name = value;
}

Professor::Professor()
{

}

Professor::Professor(int id, QString name)
{
    this->id = id;
    this->name = name;
}
