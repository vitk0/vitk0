#include "classes_professors.h"

int classes_professors::getId() const
{
    return id;
}

void classes_professors::setId(int value)
{
    id = value;
}

int classes_professors::getIdClass() const
{
    return idClass;
}

void classes_professors::setIdClass(int value)
{
    idClass = value;
}

bool classes_professors::getFirstTime() const
{
    return firstTime;
}

void classes_professors::setFirstTime(bool value)
{
    firstTime = value;
}

int classes_professors::getIdProfessor() const
{
    return idProfessor;
}

void classes_professors::setIdProfessor(int value)
{
    idProfessor = value;
}

QString classes_professors::getName() const
{
    return name;
}

void classes_professors::setName(const QString &value)
{
    name = value;
}

void classes_professors::update(classes_professors *updated)
{
    this->idClass = updated->getIdClass();
    this->firstTime = updated->getFirstTime();
    this->idProfessor = updated->getIdProfessor();
    this->name = updated->getName();

    connect();

    query.prepare("UPDATE classes_professors SET first_classes = (?), id_professors = (?) WHERE id_classes_professors=(?)");
    query.addBindValue(firstTime);
    query.addBindValue(idProfessor);
    query.addBindValue(id);
    query.exec();

    close();

}

void classes_professors::insert(classes_professors *inserted)
{
    connect();

    query.prepare("INSERT classes_professors SET id_classes = (?), first_classes = (?), id_professors = (?)");
    query.addBindValue(inserted->getIdClass());
    query.addBindValue((int)inserted->getFirstTime());
    query.addBindValue(inserted->getIdProfessor());
    query.exec();

    close();

}

void classes_professors::remove()
{
    connect();

    query.prepare("DELETE FROM classes_professors WHERE id_classes_professors=(?)");
    query.addBindValue(id);
    query.exec();

    close();

    delete this;
}

classes_professors::classes_professors(int id, int idClass, bool firstTime, int idProfessor, QString name)
{
    this->id = id;
    this->idClass = idClass;
    this->firstTime = firstTime;
    this->idProfessor = idProfessor;
    this->name = name;
}
