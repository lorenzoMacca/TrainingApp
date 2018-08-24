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
    << "BodyPart: " << Exercise::getBodyPartName(this->m_bodyPart) << " - "
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

int Exercise::callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName) {
    if(list_Not_casted == 0) return 0;
    List* list = static_cast<List*>(list_Not_casted);
    int i;
    int id = -1;
    string name = "";
    BodyPart bodyPart = NA;
    for(i = 0; i<argc; i++) {
        string columnNme(azColName[i]);
        if(columnNme == "BODYPART"){
            Exercise::itoBodyPart(&bodyPart, stoi(argv[i]));
        }else if(columnNme == "NAME"){
            name=argv[i];
        }else if(columnNme == "ID"){
            id=stoi(argv[i]);
        }
    }
    Exercise *e = new Exercise(id, bodyPart, name);
    Logger::getInstance()->log(Logger::INFO, "DbManager: Eercise instance created: " + e->toString() );
    list->pushBack(e);
    return 0;
}

bool Exercise::itoBodyPart(BodyPart* b, int i){
    switch (i) {
        case NA:
            *b=NA;
            return true;
        case ABS:
            *b=ABS;
            return true;
    }
    stringstream ss;
    ss << i;
    Logger::getInstance()->log(Logger::INFO, "BodyPart: value " + ss.str() + " cannot be converted "   );
    return false;
}

string Exercise::getBodyPartName(BodyPart b){
    string s = "AN";
    switch (b) {
        case NA:
            s =  "NA";
            break;
        case ABS:
            s =  "ABS";
            break;
        default:
            stringstream ss;
            ss << b;
            Logger::getInstance()->log(Logger::INFO, "BodyPart: value " + ss.str() + " cannot be converted"  );
    }
    return s;
}
