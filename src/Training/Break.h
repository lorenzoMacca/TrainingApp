#ifndef BREAK_H
#define BREAK_H

#include <Object.h>
#include <DbObject.h>
#include <TrainingDuration.h>

class Break : public Object, DbObject{
private:
    TrainingDuration m_td;
    
public:
    Break(TrainingDuration m_td);
    
    //from Object
    virtual string toString() const;
    virtual int compareTo(Object*) const;
    
    //from DbObject
    static string getSqliteStrTocreateTable();
    virtual string getSqliteStrToInsert()const;
    static string getSqliteStrToGetAllRecords();
};

#endif
