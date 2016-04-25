#ifndef EXTRADUTY_H
#define EXTRADUTY_H

#include "connect.h"

#include <QString>

class ExtraDuty: public Connect
{
    int id;
    QString dutyName;
    int dutyHours;
    QString positionName;
    int idProfessor;
public:
    ExtraDuty();
    ExtraDuty(int id, QString dutyName, int dutyHours, QString positionName, int idProfessor);
    int getId() const;
    void setId(int value);
    QString getDutyName() const;
    void setDutyName(const QString &value);
    int getDutyHours() const;
    void setDutyHours(int value);
    QString getPositionName() const;
    void setPositionName(const QString &value);

    void update(ExtraDuty* updated);
    void insert(ExtraDuty* inserted);
    void remove();
    int getIdProfessor() const;
    void setIdProfessor(int value);
};

#endif // EXTRADUTY_H
