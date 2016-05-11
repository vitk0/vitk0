#include "trainingsession.h"

int TrainingSession::getId() const
{
    return id;
}

void TrainingSession::setId(int value)
{
    id = value;
}

int TrainingSession::getIdProfessor() const
{
    return idProfessor;
}

void TrainingSession::setIdProfessor(int value)
{
    idProfessor = value;
}

int TrainingSession::getTrainingManagement() const
{
    return trainingManagement;
}

void TrainingSession::setTrainingManagement(int value)
{
    trainingManagement = value;
}

int TrainingSession::getFinalExamenation() const
{
    return finalExamenation;
}

void TrainingSession::setFinalExamenation(int value)
{
    finalExamenation = value;
}

int TrainingSession::getSelfStudyManagement() const
{
    return selfStudyManagement;
}

void TrainingSession::setSelfStudyManagement(int value)
{
    selfStudyManagement = value;
}

void TrainingSession::update(TrainingSession *updated)
{
    this->idProfessor = updated->getIdProfessor();
    this->trainingManagement = updated->getTrainingManagement();
    this->finalExamenation = updated->getFinalExamenation();
    this->selfStudyManagement = updated->getSelfStudyManagement();

    Query("UPDATE training_sessions SET id_professors = (?), training_management = (?), final_examenation = (?), self_study_management = (?)\
           WHERE id_training_sessions = (?)",
           idProfessor, trainingManagement, finalExamenation, selfStudyManagement, id);

}

void TrainingSession::insert(TrainingSession *inserted)
{
    Query("INSERT training_sessions SET id_professors = (?), training_management = (?), final_examenation = (?), self_study_management = (?)",
            inserted->getIdProfessor(), inserted->getTrainingManagement(), inserted->getFinalExamenation(), inserted->getSelfStudyManagement());
}

void TrainingSession::remove()
{
    Query("DELETE FROM training_sessions WHERE id_training_sessions=(?)", id);

    delete this;
}

TrainingSession::TrainingSession(int id, int idProfessor, int trainingManagement, int finalExamenation, int selfStudyManagement)
{
    this->id = id;
    this->idProfessor = idProfessor;
    this->trainingManagement = trainingManagement;
    this->finalExamenation = finalExamenation;
    this->selfStudyManagement = selfStudyManagement;
}
