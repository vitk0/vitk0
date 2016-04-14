#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <QString>

class Professor
{
    int id;
    QString name;
public:
    Professor();
    Professor(int id, QString name);
    int getId() const;
    void setId(int value);
    QString getName() const;
    void setName(const QString &value);
};

#endif // PROFESSOR_H
