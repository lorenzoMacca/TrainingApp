#ifndef DBMAMAGER_H
#define DBMAMAGER_H

#include "Object.h"
#include <sqlite3.h>

class DbManager : public Object{

private:
    string  m_dbName;
    sqlite3* m_db;
    static DbManager* m_instance;
    DbManager();
    
public:
    static DbManager* getInstance();
    bool connect();
    bool disconnect();
    virtual string toString() const;
    virtual int compareTo(Object*) const;
    virtual bool createTable(string sqlQuery=0);
    
    //callback function
    static int callbackAfterTAbleCreation(void *NotUsed, int argc, char **argv, char **azColName);

};

#endif

