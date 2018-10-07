#ifndef GENERIC_EXERCISE_H
#define GENERIC_EXERCISE_H

#include <Training.h>
#include <Logger.h>
#include <Exercise.h>

class GenericExrercise : public Training{
    private:
        int m_id;
        Exercise m_exercise;
        unsigned int m_reps;
        unsigned int m_time;
        unsigned int m_weight;
    
    public:
        GenericExrercise(Date*, TrainingDuration, unsigned int reps, unsigned int time, unsigned int weight, Exercise e, int id=-1);
        ~GenericExrercise();
    
        static const string TAG;
    
        //from Training:
        virtual string toString() const;
        virtual int compareTo(Object*) const;
        Exercise& getExercise();
        virtual string getTag()const;
    
        //from DbObject
        static string getSqliteStrTocreateTable();
        virtual string getSqliteStrToInsert()const;
        static string getSqliteStrToGetAllRecords();
    
        //callback funcs
        static int callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName);

};

#endif
