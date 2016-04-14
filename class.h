#ifndef CLASS_H
#define CLASS_H

#include "classes_professors.h"
#include "classtype.h"
#include "connect.h"

#include <QVector>

class Class:public Connect
{
    int id;
    int number;
    ClassType* classType;
    int hours;
    QVector<classes_professors*> professors;
public:
    Class();
    Class(int id, int number, ClassType* classType, int hours);
    int getId() const;
    void setId(int value);
    int getNumber() const;
    void setNumber(int value);
    int getHours() const;
    void setHours(int value);
    ~Class();

    ClassType *getClassType() const;
    void setClassType(ClassType *value);
    QVector<classes_professors *> getProfessors() const;

    void update(Class* updated);
    void insert(Class* inserted);
    void remove();

    void addProfessor(classes_professors* professor);

};

#endif // CLASS_H
