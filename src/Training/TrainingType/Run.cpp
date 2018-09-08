#include "Run.h"

Run::Run(Date* date, TrainingDuration du, Shoe s, int km):Training(date, du){
	this->m_shoe=s;
    this->m_km=km;
}

void Run::setId(int id){
    this->m_id_training = id;
}

string Run::toString() const{
    //const Training*  = this;
	stringstream str;
    str << "[RUN:"
        << "Km:" << this->m_km << " - "
        << this->Training::toString(this)
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
        << "ID_TRAINING INTEGER NOT NULL, "
		<< "KM INTEGER NOT NULL, "
		<< "ID_SHOE INTEGER NOT NULL, "
		<< "FOREIGN KEY(ID_SHOE) REFERENCES SHOE(ID), "
        << "FOREIGN KEY(ID_TRAINING) REFERENCES TRAINING(ID)"
		<< ");";
	return sql.str();
}

string Run::getSqliteStrToInsert()const{
    stringstream sql;
	sql << "INSERT INTO RUN (ID_TRAINING, KM, ID_SHOE) "
		<< "VALUES ("
        << this->m_id_training << ", "
		<< this->m_km << ", "
		<< this->m_shoe.getId()
		<< ");";
	return sql.str();
}

string Run::getSqliteStrToGetAllRecords(){
    return "select * from RUN, TRAINING, SHOE where RUN.ID_TRAINING=TRAINING.ID and RUN.ID_SHOE=SHOE.ID";
}
