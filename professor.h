#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "connect.h"
#include "extraduty.h"

#include <QString>
#include <QVector>

class Professor: public Connect
{
    int id;
    QString name;
    QVector<ExtraDuty*> extraDuties;
public:
    Professor();
    Professor(int id, QString name);
    int getId() const;
    void setId(int value);
    QString getName() const;
    void setName(const QString &value);
    QVector<ExtraDuty *> getExtraDuties() const;

    void update(Professor* updated);
    void insert(Professor* inserted);
    void remove();
};

#endif // PROFESSOR_H
