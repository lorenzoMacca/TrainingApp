#ifndef DBMAMAGER_H
#define DBMAMAGER_H

#include "Object.h"
#include <sqlite3.h>

class DbManager : public Object{

private:
    string  m_dbName;
    sqlite3* m_db;
    
    
public:
    DbManager();
    bool connect();
    bool disconnect();
    virtual string toString() const;
    virtual int compareTo(Object*) const;
};

#endif

