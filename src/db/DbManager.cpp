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

bool DbManager::exec(string sqlQuery, void* d){
	Logger::getInstance()->log(INFO, "DbManager: exec has beel called!");
		Logger::getInstance()->log(INFO, "DbManager: query: "+sqlQuery);
		char *zErrMsg = 0;
		int rc = sqlite3_exec(this->m_db, sqlQuery.c_str(), callbackAfterSelect, d, &zErrMsg);
		if( rc != SQLITE_OK ){
			stringstream errMsg;
			errMsg << "DbManager: Error during query exec: " << rc << " - "  << zErrMsg;
			Logger::getInstance()->log(ERROR, errMsg.str());
			sqlite3_free(zErrMsg);
			return false;
		} else {
			Logger::getInstance()->log(INFO, "DbManager: query has been executed successfully!");
			return true;
		}
}

int DbManager::callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName) {
	if(list_Not_casted == 0) return 0;
	List* list = static_cast<List*>(list_Not_casted);
	int i;
	Date *d = 0;
	string comment = "";
	TrainingDuration* trainingDuration;
	for(i = 0; i<argc; i++) {
		string columnNme(azColName[i]);
		if(columnNme == "DATE"){
			d = new Date(argv[i]);
		}else if(columnNme == "COMMENT"){
			comment=argv[i];
		}else if(columnNme == "DURATION"){
			trainingDuration=new TrainingDuration(stoi(argv[i]));
		}
	}
	Training *t = new Training(d, trainingDuration);
	t->setComment(comment);
	Logger::getInstance()->log(INFO, "DbManager: Training instance created: " + t->toString() );
	list->pushBack(t);
	return 0;
}

