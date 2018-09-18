#include "Break.h"

Break::Break(TrainingDuration td){
    this->m_td = td;
}

string Break::toString() const{return "";}
int Break::compareTo(Object*) const{return -2;}

string Break::getSqliteStrTocreateTable(){return "";}
string Break::getSqliteStrToInsert()const{return "";}
string Break::getSqliteStrToGetAllRecords(){return "";}
