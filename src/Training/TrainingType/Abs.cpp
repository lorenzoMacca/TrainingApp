#include "Abs.h"

Abs::Abs(Date* date, TrainingDuration du, unsigned int set, unsigned int reps, unsigned int time, Exercise e, int id):Training(date, du){
    this->m_id = id;
    this->m_set = set;
    this->m_reps = reps;
    this->m_time = time;
    this->m_exercise = e;
}

//from Training:
string Abs::toString() const{
    stringstream sstr;
    sstr << "[ABS: "
    << "ID: " << this->m_id << " - "
    << this->m_exercise.toString() << " - "
    << "set: " << this->m_set << " - "
    << "reps: " << this->m_reps << " - "
    << "time: " << this->m_time
    << " ]";
    return sstr.str();
}

int Abs::compareTo(Object*) const{
    return -2;
}

//from DbObject
string Abs::getSqliteStrTocreateTable(){
    return "";
}

string Abs::getSqliteStrToInsert()const{
    return "";
}

string Abs::getSqliteStrToGetAllRecords(){
    return "";
}
