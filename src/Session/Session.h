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
#include <Algorithms.h>

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

class PositionObject: public Object{
    
public:
    int _position;
    virtual string toString() const{return "";}
    virtual int compareTo(Object* o) const{
        PositionObject* pd = static_cast<PositionObject*>(o);
        if(this->_position == pd->_position){
            return 0;
        }if (this->_position > pd->_position) {
            return -1;
        } else {
            return 1;
        }
    };
};

class SessionTraining: public PositionObject{
public:
    int _id;
    int _trainingId;
    int _idSession;
    
    virtual string toString() const;
};

class SessionBreak: public PositionObject{
public:
    int _id;
    int _breakId;
    int _idSession;
    
    virtual string toString() const;
};

#endif
