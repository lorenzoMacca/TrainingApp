#include "Abs.h"

Abs::Abs(Date* date, TrainingDuration du, unsigned int reps, unsigned int time, Exercise e, int id):Training(date, du){
    this->m_id = id;
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
    stringstream sql;
    sql << "CREATE TABLE ABS("
    << "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    << "REPS INTEGER NOT NULL, "
    << "TIME INTEGER NOT NULL, "
    << "ID_EXERCISE INTEGER NOT NULL, "
    << "FOREIGN KEY(ID_EXERCISE) REFERENCES EXERCISE(ID)"
    << ");";
    return sql.str();
}

string Abs::getSqliteStrToInsert()const{
    stringstream sql;
    sql << "INSERT INTO ABS (REPS, TIME, ID_EXERCISE) "
    << "VALUES ("
    << this->m_reps << ", "
    << this->m_time << ", "
    << this->m_exercise.getId()
    << ");";
    return sql.str();
}

string Abs::getSqliteStrToGetAllRecords(){
     return "select ABS.ID AS ABS_ID, ABS.*, EXERCISE.ID AS EXERCISE_ID, EXERCISE.* from ABS, EXERCISE, where ABS.ID_EXERCISE = EXERCISE.ID";
}
