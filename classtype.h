#ifndef CLASSTYPE_H
#define CLASSTYPE_H

#include <QString>

class ClassType
{
    int id;
    QString name;
public:
    ClassType();
    ClassType(int id, QString name);
    int getId() const;
    void setId(int value);
    QString getName() const;
    void setName(const QString &value);
};

#endif // CLASSTYPE_H
