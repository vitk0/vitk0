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
    query.prepare("SELECT last_insert_id()");
    query.exec();
    query.next();

    int selected = query.value(0).toInt();

    close();

    connect();

    query.prepare("SELECT id_platoons FROM platoons");
    query.exec();

    close();

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
