#ifndef SWIM_H
#define SWIM_H

#include <Training.h>
#include <Logger.h>

class Swim : public Training{

	private:
        int m_id;
		float m_km;

	public:
		Swim(Date*, TrainingDuration, float km);
        Swim(Date*, TrainingDuration, float km, int m_id);
        ~Swim();
    
        static const string TAG;

		//from Training:
		virtual string toString() const;
		virtual int compareTo(Object*) const;
        virtual string getTag()const;

		//from DbObject
		static string getSqliteStrTocreateTable();
		virtual string getSqliteStrToInsert()const;
		static string getSqliteStrToGetAllRecords();
    
        //callback funcs
        static int callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName);
};

#endif
