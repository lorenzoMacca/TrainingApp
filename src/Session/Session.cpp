#include "Session.h"

Session::Session(){
    this->m_activities = new List;
    this->m_id=-1;
}

Session::Session(Date d){
    this->m_activities = new List;
    this->m_date = d;
    this->m_id=-1;
}

Session::Session(int dbId, Date d){
    this->m_activities = new List;
    this->m_date = d;
    this->m_id=dbId;
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

bool Session::loadActivities(){
    if(this->m_id < 1){
        Logger::getInstance()->log(Logger::INFO, "Session: Current activity has an id not valid: " + std::to_string(this->m_id));
        return false;
    }
    DbManager* dbManager = DbManager::getInstance();
    List* sessionActivitiesList = new List;
    
    //get sessionTraining
    List cond1;
    cond1.pushBack(new WhereCondition("SESSION.ID", std::to_string(this->m_id), "="));
    cond1.pushBack(new WhereCondition("SESSION.ID", "SESSION_TRAINING.ID_SESSION", "="));
    string queryGetsessionTrainings = "select SESSION_TRAINING.ID AS SESSION_TRAINING_ID, SESSION_TRAINING.* from SESSION, SESSION_TRAINING";
    dbManager->exec(Utils::getSqliteStrToGetRecords(queryGetsessionTrainings, cond1, "WHERE"), sessionActivitiesList, Session::callbackAfterSelectSessionTraining);
    
    //get sessionBreak
    List cond2;
    cond2.pushBack(new WhereCondition("SESSION.ID", std::to_string(this->m_id), "="));
    cond2.pushBack(new WhereCondition("SESSION.ID", "SESSION_BREAK.ID_SESSION", "="));
    string queryGetsessionbreaks = "select SESSION_BREAK.ID AS SESSION_BREAK_ID, SESSION_BREAK.* from SESSION, SESSION_BREAK";
    dbManager->exec(Utils::getSqliteStrToGetRecords(queryGetsessionbreaks, cond2, "WHERE"), sessionActivitiesList, Session::callbackAfterSelectSessionBreak);
    
    Algorithms* algorithms = new Algorithms();
    algorithms->insertionSort(sessionActivitiesList, Algorithms::ASC);
    
    cout << "PIPPO" << sessionActivitiesList->toString() << endl;
    
    //get breaks
    Iterator* sessionIterator = sessionActivitiesList->getIterator();
    while(sessionIterator->hasNext()){
        
        SessionBreak* sB = dynamic_cast<SessionBreak*>(sessionIterator->getCurrentValue());
        SessionTraining* sT = dynamic_cast<SessionTraining*>(sessionIterator->getCurrentValue());
        if(sB){ // BREAK
            List cond3;
            cond3.pushBack(new WhereCondition("ID", std::to_string(sB->_breakId), "="));
            dbManager->exec(Utils::getSqliteStrToGetRecords(Break::getSqliteStrToGetAllRecords(), cond3, "WHERE"), this->m_activities, Break::callbackAfterSelect);
        }else if(sT){ // TRAINING+
            List cond3;
            cond3.pushBack(new WhereCondition("ID_TRAINING", std::to_string(sT->_trainingId), "="));
            string tag = sT->_tag;
            if(tag == Run::TAG){
                dbManager->exec(Utils::getSqliteStrToGetRecords(Run::getSqliteStrToGetAllRecords(), cond3, "AND"), this->m_activities, Run::callbackAfterSelect);
            }else if(tag == Abs::TAG){
                dbManager->exec(Utils::getSqliteStrToGetRecords(Abs::getSqliteStrToGetAllRecords(), cond3, "AND"), this->m_activities, Abs::callbackAfterSelect);
            }else if(tag == Swim::TAG){
                dbManager->exec(Utils::getSqliteStrToGetRecords(Swim::getSqliteStrToGetAllRecords(), cond3, "AND"), this->m_activities, Swim::callbackAfterSelect);
            }
        }else{
            Logger::getInstance()->log(Logger::INFO, "Session-loadActivities: what?: " + sessionIterator->getCurrentValue()->toString() );
        }
        ++(*sessionIterator);
    }
    delete sessionIterator;
    
    return true;
}

void Session::saveAll(){
    DbManager *dbManager = DbManager::getInstance();
    //Step1: save the session
    dbManager->exec(this->getSqliteStrToInsert(), 0);
    this->m_id = dbManager->getLastID();
    
    //Step2: save all activities in the list
    //Step3: save the relation between the activities and the current list
    Iterator* i = this->m_activities->getIterator();
    int currentPosition = 0;
    while(i->hasNext()){
        Training* t = dynamic_cast<Training*>(i->getCurrentValue());
        Break* b = dynamic_cast<Break*>(i->getCurrentValue());
        int id_activity = -1;
        if(t){
            dbManager->exec(t->Training::getSqliteStrToInsert(), 0);
            id_activity = dbManager->getLastID();
            t->setTrainingId(id_activity);
            dbManager->exec(t->getSqliteStrToInsert(), 0);
            dbManager->exec(this->getSqliteStrToInsertSessionTraining(this->m_id, id_activity, currentPosition, t->getTag()), 0);
        }if(b) {
            dbManager->exec(b->getSqliteStrToInsert(), 0);
            id_activity = dbManager->getLastID();
            dbManager->exec(this->getSqliteStrToInsertSessionBreak(this->m_id, id_activity, currentPosition), 0);
        }
        
        ++(*i);
        ++currentPosition;
    }
    delete i;
}

string Session::toString() const{
    stringstream res;
    res <<  "[Session: "
        << "ID: " << this->m_id << " - "
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
    << "POSITION INTEGER NOT NULL, "
    << "TAG TEXT NOT NULL, "
    << "FOREIGN KEY(ID_TRAINING) REFERENCES TRAINING(ID), "
    << "FOREIGN KEY(ID_SESSION) REFERENCES SESSION(ID)"
    <<");";
    
    sql << "CREATE TABLE SESSION_BREAK("
    << "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    << "ID_BREAK INTEGER NOT NULL, "
    << "ID_SESSION INTEGER NOT NULL, "
    << "POSITION INTEGER NOT NULL, "
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

string Session::getSqliteStrToInsertSessionTraining(int id_session, int id_training, int position, string tag)const{
    stringstream sql;
    sql << "INSERT INTO SESSION_TRAINING (ID_TRAINING, ID_SESSION, POSITION, TAG) "
    << "VALUES ("
    << id_training << ", "
    << id_session << ", "
    << position << ", "
    << "'" << tag << "'"
    << ");";
    return sql.str();
}

string Session::getSqliteStrToInsertSessionBreak(int id_session, int id_break, int position)const{
    stringstream sql;
    sql << "INSERT INTO SESSION_BREAK (ID_BREAK, ID_SESSION, POSITION) "
    << "VALUES ("
    << id_break << ", "
    << id_session << ", "
    << position
    << ");";
    return sql.str();
}

string Session::getSqliteStrToGetAllRecords(){
    return "select * from SESSION;";
}

int Session::callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName) {
    // TRAINING_ID ID DATE DURATION COMMENT
    if(list_Not_casted == 0)
        return 0;
    List* list = static_cast<List*>(list_Not_casted);
    
    //training
    int sessionId = -1;
    Date d;
    
    for(int i = 0; i<argc; i++) {
        string columnNme(azColName[i]);
        if(columnNme == "ID"){
            sessionId=stoi(argv[i]);
        }else if(columnNme == "DATE"){
            d.init(argv[i]);
        }
    }
    Session* session = new Session(sessionId, d);
    Logger::getInstance()->log(Logger::INFO, "DbManager: Session instance created: " + session->toString() );
    list->pushBack(session);
    
    return 0;
}

string SessionTraining::toString() const{
    stringstream res;
    res <<  "[SessionTraining: "
    << "ID: " << this->_id << " - "
    << "ID_TRAINING: " << this->_trainingId << " - "
    << "ID_SESSION: " << this->_idSession << " - "
    << "POSITION: " << this->_position << " - "
    << "TAG: " << this->_tag
    << "]";
    return res.str();
}

int Session::callbackAfterSelectSessionTraining(void *list_Not_casted, int argc, char **argv, char **azColName) {
    if(list_Not_casted == 0)
        return 0;
    List* list = static_cast<List*>(list_Not_casted);
    
    //sessionTrainig
    SessionTraining* sessionTraining = new SessionTraining;
    
    for(int i = 0; i<argc; i++) {
        string columnNme(azColName[i]);
        if(columnNme == "SESSION_TRAINING_ID"){
            sessionTraining->_id=stoi(argv[i]);
        }else if(columnNme == "ID_TRAINING"){
           sessionTraining->_trainingId=stoi(argv[i]);
        }else if(columnNme == "ID_SESSION"){
            sessionTraining->_idSession=stoi(argv[i]);
        }else if(columnNme == "POSITION"){
            sessionTraining->_position=stoi(argv[i]);
        }else if(columnNme == "TAG"){
            sessionTraining->_tag=argv[i];
        }
    }
    Logger::getInstance()->log(Logger::INFO, "DbManager: sessionTraining instance created: " + sessionTraining->toString() );
    list->pushBack(sessionTraining);
    
    return 0;
}

string SessionBreak::toString() const{
    stringstream res;
    res <<  "[SessionBreak: "
    << "ID: " << this->_id << " - "
    << "ID_TRAINING: " << this->_breakId << " - "
    << "ID_SESSION: " << this->_idSession << " - "
    << "POSITION: " << this->_position
    << "]";
    return res.str();
}

int Session::callbackAfterSelectSessionBreak(void *list_Not_casted, int argc, char **argv, char **azColName) {
    if(list_Not_casted == 0)
        return 0;
    List* list = static_cast<List*>(list_Not_casted);
    
    //SessionBreak
    SessionBreak* sessionBreak = new SessionBreak;
    
    for(int i = 0; i<argc; i++) {
        string columnNme(azColName[i]);
        if(columnNme == "SESSION_BREAK_ID"){
            sessionBreak->_id=stoi(argv[i]);
        }else if(columnNme == "ID_BREAK"){
            sessionBreak->_breakId=stoi(argv[i]);
        }else if(columnNme == "ID_SESSION"){
            sessionBreak->_idSession=stoi(argv[i]);
        }else if(columnNme == "POSITION"){
            sessionBreak->_position=stoi(argv[i]);
        }
    }
    Logger::getInstance()->log(Logger::INFO, "DbManager: sessionBreak instance created: " + sessionBreak->toString() );
    list->pushBack(sessionBreak);
    
    return 0;
}
