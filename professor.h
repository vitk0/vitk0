#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <QString>

class Professor
{
    int id;
    QString name;
    int idExtraDuty;
    QString dutyName;
    int dutyHours;
    QString positionName;
public:
    Professor();
    Professor(int id, QString name, int idExtraDuty, QString dutyName, int dutyHours, QString positionName);
    int getId() const;
    void setId(int value);
    QString getName() const;
    void setName(const QString &value);
    int getIdExtraDuty() const;
    void setIdExtraDuty(int value);
    QString getDutyName() const;
    void setDutyName(const QString &value);
    int getDutyHours() const;
    void setDutyHours(int value);
    QString getPositionName() const;
    void setPositionName(const QString &value);
};

#endif // PROFESSOR_H
