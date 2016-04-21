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
