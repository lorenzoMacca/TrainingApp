#ifndef EXERCISE_H
#define EXERCISE_H

#include <Object.h>
#include <DbObject.h>
#include <sstream>

enum BodyPart {NA, ABS};

class Exercise : public Object, DbObject{
    
    private:
        unsigned int m_id;
        BodyPart m_bodyPart;
        string m_name;
        //link for the tutorial
    
    public:
    
        Exercise(int id=-1, BodyPart bodyPart=NA, string name="");
    
        //from Object
        virtual string toString() const;
        virtual int compareTo(Object*) const;
    
        //from DbObject
        static string getSqliteStrTocreateTable();
        virtual string getSqliteStrToInsert()const;
        static string getSqliteStrToGetAllRecords();

};

#endif
