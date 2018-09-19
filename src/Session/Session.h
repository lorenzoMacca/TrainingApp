#ifndef SESSION_H
#define SESSION_H

#include <Object.h>
#include <DbObject.h>
#include <List.h>
#include <Training.h>
#include <Break.h>

class Session: public Object, DbObject{

private:
    List* m_activities;

public:
    Session();
    
    bool addActivity(Object*);
    
    
    //from Object
    virtual string toString() const;
    virtual int compareTo(Object*) const;
    
    //from DbObject
    static string getSqliteStrTocreateTable();
    virtual string getSqliteStrToInsert()const;
    static string getSqliteStrToGetAllRecords();
    
};

#endif
