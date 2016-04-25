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

    Query("UPDATE extra_duty SET duty_name = (?), hours = (?), position_name = (?), id_professors = (?)\
                   WHERE id_extra_duty = (?)", dutyName, dutyHours, positionName,
            idProfessor, id);
}

void ExtraDuty::insert(ExtraDuty *inserted)
{
    Query("INSERT extra_duty SET duty_name = (?), hours = (?), position_name = (?), id_professors = (?)",
          inserted->getDutyName(), inserted->getDutyHours(), inserted->getPositionName(), inserted->getIdProfessor());
}

void ExtraDuty::remove()
{
    Query("DELETE FROM extra_duty WHERE id_extra_duty=(?)", id);

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
