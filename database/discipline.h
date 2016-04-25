#ifndef DISCIPLINE_H
#define DISCIPLINE_H

#include "connect.h"

#include <QString>

class Discipline: public Connect
{
    int id;
    QString name;
public:
    Discipline();
    Discipline(int id, QString name);
    int getId() const;
    void setId(int value);
    QString getName() const;
    void setName(const QString &value);

    void update(Discipline* updated);
    void insert(Discipline* inserted);
    void remove();
};

#endif // DISCIPLINE_H
