#include "extraduty.h"

int ExtraDuty::getId() const
{
    return id;
}

void ExtraDuty::setId(int value)
{
    id = value;
}

QString ExtraDuty::getDutyName() const
{
    return dutyName;
}

void ExtraDuty::setDutyName(const QString &value)
{
    dutyName = value;
}

int ExtraDuty::getDutyHours() const
{
    return dutyHours;
}

void ExtraDuty::setDutyHours(int value)
{
    dutyHours = value;
}

QString ExtraDuty::getPositionName() const
{
    return positionName;
}

void ExtraDuty::setPositionName(const QString &value)
{
    positionName = value;
}

void ExtraDuty::update(ExtraDuty *updated)
{
    this->dutyName = updated->getDutyName();
    this->dutyHours = updated->getDutyHours();
    this->positionName = updated->getPositionName();
    this->idProfessor = updated->getIdProfessor();

    connect();

    query.prepare("UPDATE extra_duty SET duty_name = (?), hours = (?), position_name = (?), id_professors = (?)\
                   WHERE id_extra_duty = (?)");
    query.addBindValue(dutyName);
    query.addBindValue(dutyHours);
    query.addBindValue(positionName);
    query.addBindValue(idProfessor);
    query.addBindValue(id);
    query.exec();

    close();
}

void ExtraDuty::insert(ExtraDuty *inserted)
{
    connect();

    query.prepare("INSERT extra_duty SET duty_name = (?), hours = (?), position_name = (?), id_professors = (?)");
    query.addBindValue(inserted->getDutyName());
    query.addBindValue(inserted->getDutyHours());
    query.addBindValue(inserted->getPositionName());
    query.addBindValue(inserted->getIdProfessor());
    query.exec();

    close();
}

void ExtraDuty::remove()
{
    connect();

    query.prepare("DELETE FROM extra_duty WHERE id_extra_duty=(?)");
    query.addBindValue(id);
    query.exec();

    close();

    delete this;

}

int ExtraDuty::getIdProfessor() const
{
    return idProfessor;
}

void ExtraDuty::setIdProfessor(int value)
{
    idProfessor = value;
}

ExtraDuty::ExtraDuty()
{

}

ExtraDuty::ExtraDuty(int id, QString dutyName, int dutyHours, QString positionName, int idProfessor)
{
    this->id = id;
    this->dutyName = dutyName;
    this->dutyHours = dutyHours;
    this->positionName = positionName;
    this->idProfessor = idProfessor;
}
