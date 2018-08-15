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
    Logger::getInstance()->log(Logger::INFO, "DbManager: connecting to " + this->m_dbName);
    int rc;
    rc = sqlite3_open(this->m_dbName.c_str(), &this->m_db);
    if(rc) {
        Logger::getInstance()->log(Logger::INFO, std::string("DbManager: Error: ") + sqlite3_errmsg(this->m_db));
        return false;
    } else {
        Logger::getInstance()->log(Logger::INFO, "DbManager: Opened database successfully");
        return true;
    }
    return false;
}

bool DbManager::disconnect(){
    Logger::getInstance()->log(Logger::INFO, "DbManager: Closing database");
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

bool DbManager::exec(string sqlQuery, void* d, int (*callback)(void*,int,char**,char**)){
	Logger::getInstance()->log(Logger::INFO, "DbManager: exec has beel called!");
		Logger::getInstance()->log(Logger::INFO, "DbManager: query: "+sqlQuery);
		char *zErrMsg = 0;
		int rc = sqlite3_exec(this->m_db, sqlQuery.c_str(), callback, d, &zErrMsg);
		if( rc != SQLITE_OK ){
			stringstream errMsg;
			errMsg << "DbManager: Error during query exec: " << rc << " - "  << zErrMsg;
			Logger::getInstance()->log(Logger::ERROR, errMsg.str());
			sqlite3_free(zErrMsg);
			return false;
		} else {
			Logger::getInstance()->log(Logger::INFO, "DbManager: query has been executed successfully!");
			return true;
		}
}

