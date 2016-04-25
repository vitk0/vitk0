#include "platoon.h"

int Platoon::getId() const
{
    return id;
}

void Platoon::setId(int value)
{
    id = value;
}

int Platoon::getYear() const
{
    return year;
}

void Platoon::setYear(int value)
{
    year = value;
}

int Platoon::getManCount() const
{
    return manCount;
}

void Platoon::setManCount(int value)
{
    manCount = value;
}

int Platoon::getStreamNumber() const
{
    return streamNumber;
}

void Platoon::setStreamNumber(int value)
{
    streamNumber = value;
}

int Platoon::getHalfPlatoonsCount() const
{
    return halfPlatoonsCount;
}

void Platoon::setHalfPlatoonsCount(int value)
{
    halfPlatoonsCount = value;
}

int Platoon::getVus() const
{
    return vus;
}

void Platoon::setVus(int value)
{
    vus = value;
}

void Platoon::update(Platoon *updated)
{
    this->year = updated->getYear();
    this->manCount = updated->getManCount();
    this->streamNumber = updated->getStreamNumber();
    this->halfPlatoonsCount = updated->getHalfPlatoonsCount();
    this->vus = updated->getVus();

    Query("UPDATE platoons SET year = (?), count_man = (?), number_of_stream = (?), count_half_platoons = (?),\
                   vus = (?) WHERE id_platoons = (?)",
            year, manCount, streamNumber, halfPlatoonsCount, vus, id);

}

void Platoon::insert(Platoon *inserted)
{
    Query("INSERT platoons SET year = (?), count_man = (?), number_of_stream = (?), count_half_platoons = (?),\
                   vus = (?)",
            year, manCount, streamNumber, halfPlatoonsCount, vus);

    int selected = query.lastInsertId().toInt();

    connect();

    query.prepare("SELECT id_disciplines FROM disciplines");
    query.exec();

    close();

    QSqlQuery queryTemp;
    while (query.next())
    {
        connect();

        queryTemp.prepare("INSERT thematic_plan SET vk_uvc = 1, id_disciplines = (?), id_platoons = (?), semester = 1");
        queryTemp.addBindValue(query.value(0).toInt());
        queryTemp.addBindValue(selected);
        queryTemp.exec();

        close();

        connect();

        queryTemp.prepare("INSERT thematic_plan SET vk_uvc = 2, id_disciplines = (?), id_platoons = (?), semester = 1");
        queryTemp.addBindValue(query.value(0).toInt());
        queryTemp.addBindValue(selected);
        queryTemp.exec();

        close();

        connect();

        queryTemp.prepare("INSERT thematic_plan SET vk_uvc = 1, id_disciplines = (?), id_platoons = (?), semester = 2");
        queryTemp.addBindValue(query.value(0).toInt());
        queryTemp.addBindValue(selected);
        queryTemp.exec();

        close();

        connect();

        queryTemp.prepare("INSERT thematic_plan SET vk_uvc = 2, id_disciplines = (?), id_platoons = (?), semester = 2");
        queryTemp.addBindValue(query.value(0).toInt());
        queryTemp.addBindValue(selected);
        queryTemp.exec();

        close();
    }

}

void Platoon::remove()
{
    Query("DELETE FROM platoons WHERE id_platoons=(?)", id);

    delete this;

}

Platoon::Platoon()
{

}

Platoon::Platoon(int id, int year, int manCount, int streamNumber, int halfPlatoonsCount, int vus)
{
    this->id = id;
    this->year = year;
    this->manCount = manCount;
    this->streamNumber = streamNumber;
    this->halfPlatoonsCount = halfPlatoonsCount;
    this->vus = vus;
}
