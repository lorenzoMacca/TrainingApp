#include "Exercise.h"

Exercise::Exercise(int id, BodyPart bodyPart, string name){
    this->m_id = id;
    this->m_bodyPart = bodyPart;
    this->m_name = name;
}

string Exercise::toString() const{
    stringstream sstr;
    sstr << "[Exercise: "
    << "ID: " << (int)this->m_id << " - "
    << "BodyPart: " << (BodyPart)this->m_bodyPart << " - "
    << "Name: " << this->m_name
    << " ]";
    return sstr.str();
}

int Exercise::compareTo(Object*) const{return -2;}

//from DbObject
string Exercise::getSqliteStrTocreateTable(){
    stringstream sql;
    sql << "CREATE TABLE EXERCISE("
    << "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    << "BODYPART INTEGER NOT NULL, "
    << "NAME TEXT NOT NULL);";
    return sql.str();
}

string Exercise::getSqliteStrToInsert()const{
    stringstream sql;
    sql << "INSERT INTO EXERCISE (BODYPART, NAME) "
    << "VALUES (" << this->m_bodyPart << ", "
    << "'" << this->m_name << "');";
    return sql.str();
}

string Exercise::getSqliteStrToGetAllRecords(){
    return "select * from EXERCISE";
}
