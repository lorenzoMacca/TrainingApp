#include "Session.h"

Session::Session(){
    this->m_activities = new List;
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

string Session::toString() const{return "";}
int Session::compareTo(Object*) const{return -2;}

string Session::getSqliteStrTocreateTable(){return "";}
string Session::getSqliteStrToInsert()const{return "";}
string Session::getSqliteStrToGetAllRecords(){return "";}
