#ifndef DB_OBJECT_H
#define DB_OBJECT_H

class DbObject{
    
public:
    virtual string getSqliteStrTocreateTable()const=0;
};

#endif

