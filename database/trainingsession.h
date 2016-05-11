#ifndef TRAININGSESSION_H
#define TRAININGSESSION_H

#include "connect.h"



class TrainingSession: public Connect
{
    int id;
    int idProfessor;
    int trainingManagement;
    int finalExamenation;
    int selfStudyManagement;
public:
    TrainingSession();
    TrainingSession(int id, int idProfessor, int trainingManagement, int finalExamenation, int selfStudyManagement);
    int getId() const;
    void setId(int value);
    int getIdProfessor() const;
    void setIdProfessor(int value);
    int getTrainingManagement() const;
    void setTrainingManagement(int value);
    int getFinalExamenation() const;
    void setFinalExamenation(int value);
    int getSelfStudyManagement() const;
    void setSelfStudyManagement(int value);

    void update(TrainingSession* updated);
    void insert(TrainingSession* inserted);
    void remove();
};

#endif // TRAININGSESSION_H
