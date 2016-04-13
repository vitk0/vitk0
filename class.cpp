#include "class.h"

ClassType *Class::getClassType() const
{
    return classType;
}

void Class::setClassType(ClassType *value)
{
    classType = new ClassType(value->getId(), value->getName());
}

int Class::getId() const
{
    return id;
}

void Class::setId(int value)
{
    id = value;
}

int Class::getNumber() const
{
    return number;
}

void Class::setNumber(int value)
{
    number = value;
}

int Class::getHours() const
{
    return hours;
}

void Class::setHours(int value)
{
    hours = value;
}

Class::~Class()
{
    delete classType;
}

QVector<classes_professors *> Class::getProfessors() const
{
    return professors;
}

Class::Class(int id, int number, ClassType* classType, int hours)
{
    this->id = id;
    this->number = number;
    this->classType = classType;
    this->hours = hours;

    connect();
    query.prepare("SELECT DISTINCT id_classes_professors, first_classes, professors.id_professors,\
                   professors.name FROM classes_professors JOIN professors\
                   ON classes_professors.id_professors = professors.id_professors \
                   WHERE id_classes=(?)");
    query.addBindValue(id);
    query.exec();
    while (query.next())
    {
        professors.push_back(new classes_professors(query.value(0).toInt(), id, query.value(1).toBool(),
                                    query.value(2).toInt(), query.value(3).toString()));
    }
    close();
}
