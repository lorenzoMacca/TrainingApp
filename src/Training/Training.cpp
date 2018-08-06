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

string Training::getSqliteStrTocreateTable()const{
	string sql = "CREATE TABLE COMPANY("  \
			"ID INT PRIMARY KEY     NOT NULL," \
			"NAME           TEXT    NOT NULL," \
			"AGE            INT     NOT NULL," \
			"ADDRESS        CHAR(50)," \
			"SALARY         REAL );";
	return sql;
}