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

void Discipline::update(Discipline *updated)
{
    this->name = updated->getName();

    connect();

    query.prepare("UPDATE disciplines SET name = (?)\
                   WHERE id_disciplines = (?)");
    query.addBindValue(name);
    query.addBindValue(id);
    query.exec();

    close();
}

void Discipline::insert(Discipline *inserted)
{
    connect();

    query.prepare("INSERT disciplines SET name = (?)");
    query.addBindValue(inserted->getName());
    query.exec();

    close();

}

void Discipline::remove()
{
    connect();

    query.prepare("DELETE FROM disciplines WHERE id_disciplines=(?)");
    query.addBindValue(id);
    query.exec();

    close();

    delete this;

}

Discipline::Discipline(int id, QString name)
{
    this->id = id;
    this->name = name;
}
