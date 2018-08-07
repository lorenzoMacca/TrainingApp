#include "Training.h"

Training::Training(Date* d, TrainingDuration* t){
    this->m_date = d;
    this->m_trainingDuration = t;
}

string Training::toString() const{
    string res =  "[Training: ";
    res += this->m_date->toString() + " - ";
    res += this->m_trainingDuration->toString();
    res += "]";
    return res;
}

int Training::compareTo(Object* o) const{
    return 0;
}

Date* Training::getDate()const{
    return this->m_date;
}

void Training::setDate(Date* d){
    if(d!=0){
        delete this->m_date;
        this->m_date = d;
    }
}

TrainingDuration* Training::getTrainingDuration()const{
    return this->m_trainingDuration;
}

void Training::setTrainingDuration(TrainingDuration* t){
    if(t!=0){
        this->m_trainingDuration = t;
    }
}

string Training::getSqliteStrTocreateTable(){
	stringstream sql;
	sql << "CREATE TABLE TRAINING("
		<< "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		<< "DATE TEXT NOT NULL);";
	return sql.str();
}

string Training::getSqliteStrToInsert()const{
	stringstream sql;
	sql << "INSERT INTO TRAINING (DATE) " 
		<< "VALUES ('" << this->m_date->getTmSerialized() << "');";
	return sql.str();	
}

string Training::getSqliteStrToGetAllRecords(){
	return "select * from TRAINING";
}