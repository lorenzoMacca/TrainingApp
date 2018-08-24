#ifndef TRAINING_H
#define TRAINING_H

#include <Object.h>
#include <DbObject.h>
#include <Date.h>
#include <TrainingDuration.h>
#include <List.h>
#include <Logger.h>


class Training : public Object, DbObject{

private:
    Date* m_date;
    string m_comment;
    TrainingDuration m_trainingDuration;

public:
    Training(Date*, TrainingDuration);
    virtual string toString() const;
    virtual int compareTo(Object*) const;
    Date* getDate()const;
    void setDate(Date*);
    TrainingDuration getTrainingDuration()const;
    void setTrainingDuration(TrainingDuration);
    void setComment(string s);
    string getComment()const;

    //from DbObject
    static string getSqliteStrTocreateTable();
    virtual string getSqliteStrToInsert()const;
    static string getSqliteStrToGetAllRecords();

    //from sqlite3 callback func
    //callback function
    static int callbackAfterSelect(void *NotUsed, int argc, char **argv, char **azColName);



};

#endif
