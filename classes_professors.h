#ifndef CLASSES_PROFESSORS_H
#define CLASSES_PROFESSORS_H

#include <QString>

class classes_professors
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
};

#endif // CLASSES_PROFESSORS_H
