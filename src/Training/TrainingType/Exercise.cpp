#include "Exercise.h"

Exercise::Exercise(int id, BodyPart bodyPart, string name){
    this->m_id = id;
    this->m_bodyPart = bodyPart;
    this->m_name = name;
}

string Exercise::toString() const{
    return "";
}

int Exercise::compareTo(Object*) const{return -2;}

//from DbObject
string Exercise::getSqliteStrTocreateTable(){
    return "";
}

string Exercise::getSqliteStrToInsert()const{
    return "";
}

string Exercise::getSqliteStrToGetAllRecords(){
    return "";
}
