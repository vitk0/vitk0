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

QVector<ExtraDuty *> Professor::getExtraDuties() const
{
    return extraDuties;
}

void Professor::update(Professor *updated)
{
    this->name = updated->getName();

    Query("UPDATE professors SET name = (?)\
                   WHERE id_professors = (?)", name, id);
}

void Professor::insert(Professor *inserted)
{
    Query("INSERT professors SET name = (?)", inserted->getName());
}

void Professor::remove()
{
    Query("DELETE FROM professors WHERE id_professors=(?)", id);

    delete this;
}

Professor::Professor()
{
    
}

Professor::Professor(int id, QString name)
{
    this->id = id;
    this->name = name;

    Query("SELECT DISTINCT id_extra_duty, duty_name, hours, position_name, id_professors\
                   FROM extra_duty WHERE id_professors=(?)", id);
    while (query.next())
    {
        extraDuties.push_back(new ExtraDuty(query.value(0).toInt(), query.value(1).toString(),
                                    query.value(2).toInt(), query.value(3).toString(), query.value(4).toInt()));
    }
}
