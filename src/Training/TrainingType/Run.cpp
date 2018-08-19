#include "Run.h"

Run::Run(Date* date, TrainingDuration* du, Shoe s):Training(date, du){
	this->m_shoe=s;
}

string Run::toString() const{
	//TODO implementation is missing
	return "";
}

int Run::compareTo(Object*) const{
	//TODO implementation is missing
	return -2;
}

string Run::getSqliteStrTocreateTable(){
	//TODO implementation is missing
	return "";
}

string Run::getSqliteStrToInsert()const{
	Logger::getInstance()->log(Logger::INFO, "RUN: getSqliteStrToInsert has been called");
	//TODO implementation is missing
	return "";
}

string Run::getSqliteStrToGetAllRecords(){
	//TODO implementation is missing
	return "";
}
