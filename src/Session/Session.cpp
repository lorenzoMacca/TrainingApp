#include "Session.h"

Session::Session(){
    this->m_activities = new List;
    this->m_id=-1;
}

Session::Session(Date d){
    this->m_date = d;
    this->m_id=-1;
}

Session::~Session(){
    delete this->m_activities;
}

bool Session::addActivity(Object* o){
    if(dynamic_cast<Training*>(o)){
        this->m_activities->pushBack(o);
        return true;
    }else if(dynamic_cast<Break*>(o)){
        this->m_activities->pushBack(o);
        return true;
    }else{
        Logger::getInstance()->log(Logger::INFO, "Session: The Object cannot be added to the session: " + o->toString());
        return false;
    }
}

void Session::saveAll(){
    DbManager *dbManager = DbManager::getInstance();
    //Step1: save the session
    dbManager->exec(this->getSqliteStrToInsert(), 0);
    this->m_id = dbManager->getLastID();
    
    //Step2: save all activities in the list
    //Step3: save the relation between the activities and the current list
    Iterator* i = this->m_activities->getIterator();
    while(i->hasNext()){
        Training* t = dynamic_cast<Training*>(i->getCurrentValue());
        Break* b = dynamic_cast<Break*>(i->getCurrentValue());
        int id_activity = -1;
        if(t){
            dbManager->exec(t->Training::getSqliteStrToInsert(), 0);
            id_activity = dbManager->getLastID();
            t->setTrainingId(id_activity);
            dbManager->exec(t->getSqliteStrToInsert(), 0);
            dbManager->exec(this->getSqliteStrToInsertSessionTraining(this->m_id, id_activity), 0);
        }if(b) {
            dbManager->exec(b->getSqliteStrToInsert(), 0);
            id_activity = dbManager->getLastID();
            dbManager->exec(this->getSqliteStrToInsertSessionBreak(this->m_id, id_activity), 0);
        }
        
        ++(*i);
    }
    delete i;
}

string Session::toString() const{
    stringstream res;
    res <<  "[Session: "
        << this->m_date.toString() << " - "
        << this->m_activities->toString() << " - "
        << "]";
    return res.str();
}

int Session::compareTo(Object*) const{return -2;}

string Session::getSqliteStrTocreateTable(){
    stringstream sql;
    sql << "CREATE TABLE SESSION("
    << "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    << "DATE TEXT NOT NULL);";
    
    sql << "CREATE TABLE SESSION_TRAINING("
    << "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    << "ID_TRAINING INTEGER NOT NULL, "
    << "ID_SESSION INTEGER NOT NULL, "
    << "FOREIGN KEY(ID_TRAINING) REFERENCES TRAINING(ID), "
    << "FOREIGN KEY(ID_SESSION) REFERENCES SESSION(ID)"
    <<");";
    
    sql << "CREATE TABLE SESSION_BREAK("
    << "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    << "ID_BREAK INTEGER NOT NULL, "
    << "ID_SESSION INTEGER NOT NULL, "
    << "FOREIGN KEY(ID_BREAK) REFERENCES BREAK(ID), "
    << "FOREIGN KEY(ID_SESSION) REFERENCES SESSION(ID)"
    <<");";
    return sql.str();
}

string Session::getSqliteStrToInsert()const{
    stringstream sql;
    sql << "INSERT INTO SESSION (DATE) "
    << "VALUES ('" << this->m_date.getTmSerialized()
    << "');";
    return sql.str();
}

string Session::getSqliteStrToInsertSessionTraining(int id_session, int id_training)const{
    stringstream sql;
    sql << "INSERT INTO SESSION_TRAINING (ID_TRAINING, ID_SESSION) "
    << "VALUES ("
    << id_training << ", "
    << id_session
    << ");";
    return sql.str();
}

string Session::getSqliteStrToInsertSessionBreak(int id_session, int id_break)const{
    stringstream sql;
    sql << "INSERT INTO SESSION_BREAK (ID_BREAK, ID_SESSION) "
    << "VALUES ("
    << id_break << ", "
    << id_session
    << ");";
    return sql.str();
}

string Session::getSqliteStrToGetAllRecords(){
    return "select * form SESSION;";
    
}
