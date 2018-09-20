#include "Break.h"

Break::Break(TrainingDuration td){
    this->m_td = td;
    this->m_id = -1;
}

Break::Break(int idDb, TrainingDuration td){
    this->m_td = td;
    this->m_id = idDb;
}

Break::~Break(){}

void Break::setId(int idDb){
    this->m_id = idDb;
}

string Break::toString() const{
    stringstream res;
    res << "[Break: "
    << "ID: " << this->m_id << " - "
    << this->m_td.toString()
    << "]";
    return res.str();
}

int Break::compareTo(Object*) const{return -2;}

string Break::getSqliteStrTocreateTable(){
    stringstream sql;
    sql << "CREATE TABLE BREAK("
    << "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    << "DURATION REAL NOT NULL "
    << ");";
    return sql.str();
}

string Break::getSqliteStrToInsert()const{
    stringstream sql;
    sql << "INSERT INTO BREAK (DURATION) "
    << "VALUES ("
    << this->m_td.getDuration()
    << ");";
    return sql.str();
}

string Break::getSqliteStrToGetAllRecords(){
    return "select * from BREAK";
}

int Break::callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName) {
    if(list_Not_casted == 0) return 0;
    List* list = static_cast<List*>(list_Not_casted);
    int i;
    int id = -1;
    float timeDuration = 0;
    for(i = 0; i<argc; i++) {
        string columnNme(azColName[i]);
        if(columnNme == "DURATION"){
            timeDuration = stof(argv[i]);
        }else if(columnNme == "ID"){
            id = stoi(argv[i]);
        }
    }
    TrainingDuration trainingDuration(timeDuration);
    Break* breakT = new Break(id, trainingDuration);
    Logger::getInstance()->log(Logger::INFO, "DbManager: Break instance created: " + breakT->toString() );
    list->pushBack(breakT);
    return 0;
}
