#ifndef BREAK_H
#define BREAK_H

#include <Object.h>
#include <DbObject.h>
#include <TrainingDuration.h>
#include <Logger.h>
#include <List.h>

class Break : public Object, DbObject{
private:
    TrainingDuration m_td;
    int m_id;
    
public:
    Break(TrainingDuration m_td);
    Break(int idDb, TrainingDuration m_td);
    void setId(int idDb);
    
    //from Object
    virtual string toString() const;
    virtual int compareTo(Object*) const;
    
    //from DbObject
    static string getSqliteStrTocreateTable();
    virtual string getSqliteStrToInsert()const;
    static string getSqliteStrToGetAllRecords();
    
    //from sqlite3 callback func
    //callback function
    static int callbackAfterSelect(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif
