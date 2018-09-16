#ifndef ABS_H
#define ABS_H

#include <Training.h>
#include <Logger.h>
#include <Shoe.h>
#include <Exercise.h>

class Abs : public Training{
    private:
        int m_id;
        Exercise m_exercise;
        unsigned int m_reps;
        unsigned int m_time;
    
    public:
        Abs(Date*, TrainingDuration, unsigned int reps, unsigned int time, Exercise e, int id=-1);
    
        //from Training:
        virtual string toString() const;
        virtual int compareTo(Object*) const;
    
        //from DbObject
        static string getSqliteStrTocreateTable();
        virtual string getSqliteStrToInsert()const;
        static string getSqliteStrToGetAllRecords();

};

#endif
