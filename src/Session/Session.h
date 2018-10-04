#ifndef SESSION_H
#define SESSION_H

#include <Object.h>
#include <DbObject.h>
#include <List.h>
#include <Training.h>
#include <Break.h>
#include <DbManager.h>
#include <string>
#include <WhereCondition.h>
#include <Utils.h>

class Session: public Object, DbObject{

private:
    List* m_activities;
    Date m_date;
    int m_id;

public:
    Session();
    Session(Date d);
    Session(int dbId, Date d);
    ~Session();
    
    bool addActivity(Object*);
    void saveAll();
    bool loadActivities();
    string getSqliteStrToInsertSessionTraining(int id_session, int id_training, int position)const;
    string getSqliteStrToInsertSessionBreak(int id_session, int id_break, int position)const;
    
    //from Object
    virtual string toString() const;
    virtual int compareTo(Object*) const;
    
    //from DbObject
    static string getSqliteStrTocreateTable();
    virtual string getSqliteStrToInsert()const;
    static string getSqliteStrToGetAllRecords();
    
    //callback funcs
    static int callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName);
    static int callbackAfterSelectSessionTraining(void *list_Not_casted, int argc, char **argv, char **azColName);
    static int callbackAfterSelectSessionBreak(void *list_Not_casted, int argc, char **argv, char **azColName);
    
};

class SessionTraining: public Object{
public:
    int _id;
    int _trainingId;
    int _idSession;
    int _position;
    
    virtual string toString() const;
    virtual int compareTo(Object*) const{return -2;}
};

class SessionBreak: public Object{
public:
    int _id;
    int _breakId;
    int _idSession;
    int _position;
    
    virtual string toString() const;
    virtual int compareTo(Object*) const{return -2;}
};

#endif
