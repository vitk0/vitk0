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

int Professor::getIdExtraDuty() const
{
    return idExtraDuty;
}

void Professor::setIdExtraDuty(int value)
{
    idExtraDuty = value;
}

QString Professor::getDutyName() const
{
    return dutyName;
}

void Professor::setDutyName(const QString &value)
{
    dutyName = value;
}

int Professor::getDutyHours() const
{
    return dutyHours;
}

void Professor::setDutyHours(int value)
{
    dutyHours = value;
}

QString Professor::getPositionName() const
{
    return positionName;
}

void Professor::setPositionName(const QString &value)
{
    positionName = value;
}

Professor::Professor()
{
    
}

Professor::Professor(int id, QString name, int idExtraDuty, QString dutyName, int dutyHours, QString positionName)
{
    this->id = id;
    this->name = name;
    this->idExtraDuty = idExtraDuty;
    this->dutyName = dutyName;
    this->dutyHours = dutyHours;
    this->positionName = positionName;

}
