#ifndef DBMAMAGER_H
#define DBMAMAGER_H

#include "Object.h"
#include <sqlite3.h>
#include <Logger.h>
#include <List.h>
#include <TrainingDuration.h>
#include <Date.h>
#include <Training.h>

class DbManager : public Object{

private:
    string  m_dbName;
    sqlite3* m_db;
    static DbManager* m_instance;
    
    DbManager();
    ~DbManager();
    
    bool checkForeignKeysEnabled();
    void enableForeignkeys();

public:
    static DbManager* getInstance();
    static void resetInstance();
    bool connect();
    bool disconnect();
    bool init();
    virtual string toString() const;
    virtual int compareTo(Object*) const;
    virtual unsigned getLastID();

    //parameter: query, data to be passed to the callback func, callback func
    virtual bool exec(string sqlQuery=0, void* d=0, int (*callback)(void*,int,char**,char**)=0);

    //from sqlite3 callback func
    //callback function
	static int callbackAfterPragmaCall(void *NotUsed, int argc, char **argv, char **azColName);

};

#endif

