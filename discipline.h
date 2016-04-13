#ifndef DISCIPLINE_H
#define DISCIPLINE_H

#include <QString>

class Discipline
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
};

#endif // DISCIPLINE_H
