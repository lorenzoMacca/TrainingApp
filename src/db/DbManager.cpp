#include "DbManager.h"

DbManager::DbManager(){
    this->m_dbName = "training.db";
    this->m_db = NULL;
}

string DbManager::toString() const{
    string res = "[DbManager";
    res += "]";
    return res;
}

int DbManager::compareTo(Object* o) const{
    //TODO: won't implement
    return -2;
}

bool DbManager::connect(){
    int rc;
    rc = sqlite3_open(this->m_dbName.c_str(), &this->m_db);
    if(rc) {
        return false;
    } else {
        return true;
    }
    return false;
}

bool DbManager::disconnect(){
    sqlite3_close(this->m_db);
    return true;
}

DbManager* DbManager::m_instance=0;

DbManager* DbManager::getInstance(){
    if(m_instance==0){
        m_instance = new DbManager();
    }
    return m_instance;
}

