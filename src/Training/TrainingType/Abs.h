#ifndef ABS_H
#define ABS_H

#include <Training.h>
#include <Logger.h>
#include <Shoe.h>
#include <Exercise.h>

class Abs : public Training{
    private:
        int m_id;
        unsigned int m_set;
        unsigned int m_reps;
        Exercise m_exercise;
    
    public:
        Abs(Date*, TrainingDuration, unsigned int set, unsigned int reps, Exercise e, int id=-1);
    
        //from Training:
        virtual string toString() const;
        virtual int compareTo(Object*) const;
    
        //from DbObject
        static string getSqliteStrTocreateTable();
        virtual string getSqliteStrToInsert()const;
        static string getSqliteStrToGetAllRecords();

};

#endif
