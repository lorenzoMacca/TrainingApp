#include "Abs.h"

Abs::Abs(Date* date, TrainingDuration du):Training(date, du){
}

//from Training:
string Abs::toString() const{
    return "";
}

int Abs::compareTo(Object*) const{
    return -2;
}

//from DbObject
string Abs::getSqliteStrTocreateTable(){
    return "";
}

string Abs::getSqliteStrToInsert()const{
    return "";
}

string Abs::getSqliteStrToGetAllRecords(){
    return "";
}
