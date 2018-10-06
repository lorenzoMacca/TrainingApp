#ifndef DB_OBJECT_H
#define DB_OBJECT_H

#include <map>

class DbObject{
    
public:
    static string getSqliteStrTocreateTable();
    virtual string getSqliteStrToInsert()const=0;
    static string getSqliteStrToGetAllRecords();
};

#endif

