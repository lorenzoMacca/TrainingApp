#ifndef EXERCISE_H
#define EXERCISE_H

#include <Object.h>
#include <DbObject.h>
#include <sstream>
#include <List.h>
#include <Logger.h>

enum BodyPart {NA=0, ABS=1, SQUAT=2};

class Exercise : public Object, DbObject{
    
    private:
        unsigned int m_id;
        BodyPart m_bodyPart;
        string m_name;
        //link for the tutorial
    
    public:
    
        Exercise(int id=-1, BodyPart bodyPart=NA, string name="");
        unsigned int getId()const;
        void setId(unsigned int);
    
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
    
        //to conver int -> BodyPart
        static bool itoBodyPart(BodyPart* b, int i);
        //return name of bodypart
        static string getBodyPartName(BodyPart b);

};

#endif
