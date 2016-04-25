#ifndef PLATOON_H
#define PLATOON_H

#include "connect.h"



class Platoon: public Connect
{
    int id;
    int year;
    int manCount;
    int streamNumber;
    int halfPlatoonsCount;
    int vus;
public:
    Platoon();
    Platoon(int id,int year, int manCount, int streamNumber, int halfPlatoonsCount, int vus);
    int getId() const;
    void setId(int value);
    int getYear() const;
    void setYear(int value);
    int getManCount() const;
    void setManCount(int value);
    int getStreamNumber() const;
    void setStreamNumber(int value);
    int getHalfPlatoonsCount() const;
    void setHalfPlatoonsCount(int value);
    int getVus() const;
    void setVus(int value);

    void update(Platoon* updated);
    void insert(Platoon* inserted);
    void remove();
};

#endif // PLATOON_H
