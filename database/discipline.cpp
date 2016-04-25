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

    Query("UPDATE disciplines SET name = (?)\
                   WHERE id_disciplines = (?)", name, id);
}

void Discipline::insert(Discipline *inserted)
{
    Query("INSERT disciplines SET name = (?)", inserted->getName());

    int selected = query.lastInsertId().toInt();

    Query("SELECT id_platoons FROM platoons");

    QSqlQuery queryTemp;
    while (query.next())
    {
        connect();

        queryTemp.prepare("INSERT thematic_plan SET vk_uvc = 1, id_disciplines = (?), id_platoons = (?), semester = 1");
        queryTemp.addBindValue(selected);
        queryTemp.addBindValue(query.value(0).toInt());
        queryTemp.exec();

        close();

        connect();

        queryTemp.prepare("INSERT thematic_plan SET vk_uvc = 2, id_disciplines = (?), id_platoons = (?), semester = 1");
        queryTemp.addBindValue(selected);
        queryTemp.addBindValue(query.value(0).toInt());
        queryTemp.exec();

        close();

        connect();

        queryTemp.prepare("INSERT thematic_plan SET vk_uvc = 1, id_disciplines = (?), id_platoons = (?), semester = 2");
        queryTemp.addBindValue(selected);
        queryTemp.addBindValue(query.value(0).toInt());
        queryTemp.exec();

        close();

        connect();

        queryTemp.prepare("INSERT thematic_plan SET vk_uvc = 2, id_disciplines = (?), id_platoons = (?), semester = 2");
        queryTemp.addBindValue(selected);
        queryTemp.addBindValue(query.value(0).toInt());
        queryTemp.exec();

        close();
    }
}

void Discipline::remove()
{
    Query("DELETE FROM disciplines WHERE id_disciplines=(?)", id);

    delete this;
}

Discipline::Discipline(int id, QString name)
{
    this->id = id;
    this->name = name;
}
