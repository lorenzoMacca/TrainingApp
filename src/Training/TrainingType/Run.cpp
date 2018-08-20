#include "Run.h"

Run::Run(Date* date, TrainingDuration du, Shoe s):Training(date, du){
	this->m_shoe=s;
}

string Run::toString() const{
	stringstream str;
    str << "[RUN:"
        << "Km:" << this->m_km << " - "
        << this->m_shoe.toString()
        << "]";
	return str.str();
}

int Run::compareTo(Object*) const{
	//TODO implementation is missing
	return -2;
}

string Run::getSqliteStrTocreateTable(){
    stringstream sql;
	sql << "CREATE TABLE RUN("
		<< "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		<< "KM INTEGER NOT NULL, "
		<< "ID_SHOE INTEGER NOT NULL, "
		<< "FOREIGN KEY(ID_SHOE) REFERENCES SHOE(ID)"
		<< ");";
	return sql.str();
}

string Run::getSqliteStrToInsert()const{
    stringstream sql;
	sql << "INSERT INTO RUN (KM, ID_SHOE) "
		<< "VALUES ("
		<< this->m_km << ", "
		<< this->m_shoe.getId()
		<< ");";
	return sql.str();
}

string Run::getSqliteStrToGetAllRecords(){
	//TODO implementation is missing
	return "";
}
