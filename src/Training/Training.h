#ifndef TRAINING_H
#define TRAINING_H

#include <Object.h>
#include <DbObject.h>
#include <Date.h>
#include <TrainingDuration.h>
#include <List.h>
#include <Logger.h>


class Training : public Object, DbObject{

protected:
    int m_id_training;
    Date* m_date;
    string m_comment;
    TrainingDuration m_trainingDuration;

public:
    Training(int id=-1, Date* d = 0, TrainingDuration t=0);
    Training(Date* , TrainingDuration);
    Date* getDate()const;
    void setDate(Date*);
    TrainingDuration getTrainingDuration()const;
    void setTrainingDuration(TrainingDuration);
    void setComment(string s);
    string getComment()const;
    string toString(const Training*) const;

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
