#include "Session.h"

Session::Session(){
    this->m_activities = new List;
}

string Session::toString() const{return "";}
int Session::compareTo(Object*) const{return -2;}

string Session::getSqliteStrTocreateTable(){return "";}
string Session::getSqliteStrToInsert()const{return "";}
string Session::getSqliteStrToGetAllRecords(){return "";}
