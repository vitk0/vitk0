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

    connect();

    query.prepare("UPDATE professors SET name = (?)\
                   WHERE id_professors = (?)");
    query.addBindValue(name);
    query.addBindValue(id);
    query.exec();

    close();
}

void Professor::insert(Professor *inserted)
{

    connect();

    query.prepare("INSERT professors SET name = (?)");
    query.addBindValue(inserted->getName());
    query.exec();

    close();
}

void Professor::remove()
{

    connect();

    query.prepare("DELETE FROM professors WHERE id_professors=(?)");
    query.addBindValue(id);
    query.exec();

    close();

    delete this;

}

Professor::Professor()
{
    
}

Professor::Professor(int id, QString name)
{
    this->id = id;
    this->name = name;
    connect();
    query.prepare("SELECT DISTINCT id_extra_duty, duty_name, hours, position_name, id_professors\
                   FROM extra_duty WHERE id_professors=(?)");
    query.addBindValue(id);
    query.exec();
    while (query.next())
    {
        extraDuties.push_back(new ExtraDuty(query.value(0).toInt(), query.value(1).toString(),
                                    query.value(2).toInt(), query.value(3).toString(), query.value(4).toInt()));
    }
    close();
}
