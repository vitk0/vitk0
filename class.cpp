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

void Class::update(Class *updated)
{
    this->id = updated->getId();
    this->number = updated->getNumber();
    this->classType = updated->getClassType();
    this->hours = updated->getHours();

    connect();

    query.prepare("UPDATE classes SET number = (?), id_type = (?), hours = (?) WHERE id_classes=(?)");
    query.addBindValue(number);
    query.addBindValue(classType->getId());
    query.addBindValue(hours);
    query.addBindValue(id);
    query.exec();

    close();

    foreach(classes_professors* i, professors)
    {
        i->remove();
    }

    foreach(classes_professors* i, updated->getProfessors())
    {
        professors.push_back(new classes_professors(i->getId(),i->getIdClass(),i->getFirstTime(),i->getIdProfessor(), i->getName()));
        i->insert(i);
    }
}

void Class::remove()
{
    foreach(classes_professors* i, professors)
    {
        i->remove();
    }

    connect();

    query.prepare("DELETE FROM classes WHERE id_classes=(?)");
    query.addBindValue(id);
    query.exec();

    close();

    delete this;
}

void Class::addProfessor(classes_professors *professor)
{
    professors.push_back(new classes_professors(professor->getId(),professor->getIdClass(),professor->getFirstTime(),professor->getIdProfessor(), professor->getName()));
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
