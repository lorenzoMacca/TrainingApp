#ifndef DB_OBJECT_H
#define DB_OBJECT_H

class DbObject{
    
public:
    static string getSqliteStrTocreateTable();
    string getSqliteStrToInsert()const;
    static string getSqliteStrToGetAllRecords();
};

#endif

