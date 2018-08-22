#ifndef ABS_H
#define ABS_H

#include <Training.h>
#include <Logger.h>
#include <Shoe.h>

class Abs : public Training{
    private:
        unsigned int m_set;
        unsigned int m_reps;
    
    public:
        Abs(Date*, TrainingDuration);
    
        //from Training:
        virtual string toString() const;
        virtual int compareTo(Object*) const;
    
        //from DbObject
        static string getSqliteStrTocreateTable();
        virtual string getSqliteStrToInsert()const;
        static string getSqliteStrToGetAllRecords();

};

#endif
