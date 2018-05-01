#include "DbManager.h"
#include "Logger.h"

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
    Logger::getInstance()->log(INFO, "DbManager: connecting to " + this->m_dbName);
    int rc;
    rc = sqlite3_open(this->m_dbName.c_str(), &this->m_db);
    if(rc) {
        Logger::getInstance()->log(INFO, std::string("DbManager: Error: ") + sqlite3_errmsg(this->m_db));
        return false;
    } else {
        Logger::getInstance()->log(INFO, "DbManager: Opened database successfully");
        return true;
    }
    return false;
}

bool DbManager::disconnect(){
    Logger::getInstance()->log(INFO, "DbManager: Closing database");
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

