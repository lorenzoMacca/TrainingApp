#include "Session.h"

Session::Session(){
    this->m_activities = new List;
}

Session::Session(Date d){
    this->m_date = d;
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
    //Step1: save the session
    
    //Step2: save all activities in the list
    IteratorList* i = static_cast<IteratorList*>(this->m_activities->getIterator());
    DbManager *dbManager = DbManager::getInstance();
    while(i->hasNext()){
        Training* t = dynamic_cast<Training*>(i->getCurrentValue());
        Break* b = dynamic_cast<Break*>(i->getCurrentValue());
        if(t){
            dbManager->exec(t->Training::getSqliteStrToInsert(), 0);
            t->setTrainingId(dbManager->getLastID());
            dbManager->exec(t->getSqliteStrToInsert(), 0);
        }if(b) {
            dbManager->exec(b->getSqliteStrToInsert(), 0);
        }
        ++(*i);
    }
    delete i;
    
    //Step3: save the relation between the activities and the current list
}

string Session::toString() const{
    stringstream res;
    res <<  "[Session: ";
    res << this->m_date.toString() << " - ";
    res << this->m_activities->toString() << " - ";
    res << "]";
    return res.str();
}

int Session::compareTo(Object*) const{return -2;}

string Session::getSqliteStrTocreateTable(){return "";}
string Session::getSqliteStrToInsert()const{return "";}
string Session::getSqliteStrToGetAllRecords(){return "";}
