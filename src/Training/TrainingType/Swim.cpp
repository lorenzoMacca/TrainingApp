#include "Swim.h"

Swim::Swim(Date* date, TrainingDuration du, float km):Training(date, du){
    this->m_km=km;
    this->m_id=-1;
}

Swim::Swim(Date* date, TrainingDuration du, float km, int id):Training(date, du){
    this->m_km=km;
    this->m_id=id;
}

Swim::~Swim(){
    
}

string Swim::toString() const{
	stringstream str;
    str << "[Swim:"
        << "ID: " << this->m_id << " - "
        << "Km:" << this->m_km << " - "
        << this->Training::toString(this)
        << "]";
	return str.str();
}

int Swim::compareTo(Object*) const{
	//TODO implementation is missing
	return -2;
}

string Swim::getSqliteStrTocreateTable(){
    stringstream sql;
	sql << "CREATE TABLE SWIM("
		<< "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        << "ID_TRAINING INTEGER NOT NULL, "
		<< "KM REAL NOT NULL, "
        << "FOREIGN KEY(ID_TRAINING) REFERENCES TRAINING(ID)"
		<< ");";
	return sql.str();
}

string Swim::getSqliteStrToInsert()const{
    stringstream sql;
	sql << "INSERT INTO SWIM (ID_TRAINING, KM) "
		<< "VALUES ("
        << this->m_id_training << ", "
		<< this->m_km
		<< ");";
	return sql.str();
}

string Swim::getSqliteStrToGetAllRecords(){
    return "select SWIM.ID AS SWIM_ID, SWIM.*, TRAINING.ID AS TRAINING_ID, TRAINING.* from SWIM, TRAINING where SWIM.ID_TRAINING=TRAINING.ID";
}

int Swim::callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName) {
    // TRAINING_ID ID DATE DURATION COMMENT
    if(list_Not_casted == 0)
        return 0;
    List* list = static_cast<List*>(list_Not_casted);
    //run
    int swimId = -1;
    float km = 0;
    //training
    int trainingId = -1;
    Date *d = 0;
    string comment = "";
    float timeDuration = 0;
    for(int i = 0; i<argc; i++) {
        string columnNme(azColName[i]);
        if(columnNme == "SWIM_ID"){
            swimId=stoi(argv[i]);
        }else if(columnNme == "KM"){
            km=stof(argv[i]);
        }else if(columnNme == "DATE"){
            d = new Date(argv[i]);
        }else if(columnNme == "COMMENT"){
            comment=argv[i];
        }else if(columnNme == "DURATION"){
            timeDuration = stof(argv[i]);
        }else if(columnNme == "TRAINING_ID"){
            trainingId = stoi(argv[i]);
        }
    }
    TrainingDuration trainingDuration(timeDuration);
    Swim* swim = new Swim(d, trainingDuration, km, swimId);
    swim->setTrainingId(trainingId);
    Logger::getInstance()->log(Logger::INFO, "DbManager: SWIM instance created: " + swim->toString() );
    list->pushBack(swim);

    return 0;
}
