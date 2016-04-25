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

    Query("UPDATE classes_professors SET first_classes = (?), id_professors = (?) WHERE id_classes_professors=(?)",
          firstTime, idProfessor, id);

}

void classes_professors::insert(classes_professors *inserted)
{
    Query("INSERT classes_professors SET id_classes = (?), first_classes = (?), id_professors = (?)",
          inserted->getIdClass(), (int)inserted->getFirstTime(), inserted->getIdProfessor());
}

void classes_professors::remove()
{
    Query("DELETE FROM classes_professors WHERE id_classes_professors=(?)", id);

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
