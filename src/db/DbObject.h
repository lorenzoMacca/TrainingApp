#ifndef DB_OBJECT_H
#define DB_OBJECT_H

class DbObject{
    
public:
    virtual DbObject* getFromDB()=0;
    virtual bool writeToDB()=0;
};

#endif

