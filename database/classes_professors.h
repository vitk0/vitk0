#ifndef CLASSES_PROFESSORS_H
#define CLASSES_PROFESSORS_H

#include "connect.h"

#include <QString>

class classes_professors: public Connect
{
    int id;
    int idClass;
    bool firstTime;
    int idProfessor;
    QString name;
public:
    classes_professors();
    classes_professors(int id, int idClass, bool firstTime, int idProfessor, QString name);
    int getId() const;
    void setId(int value);
    int getIdClass() const;
    void setIdClass(int value);
    bool getFirstTime() const;
    void setFirstTime(bool value);
    int getIdProfessor() const;
    void setIdProfessor(int value);
    QString getName() const;
    void setName(const QString &value);
    void update(classes_professors* updated);
    void insert(classes_professors* inserted);
    void remove();
};

#endif // CLASSES_PROFESSORS_H
