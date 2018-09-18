#ifndef SWIM_H
#define SWIM_H

#include <Training.h>
#include <Logger.h>

class Swim : public Training{

	private:
        int m_id;
		unsigned m_km;


	public:
		Swim(Date*, TrainingDuration, int km);
        Swim(Date*, TrainingDuration, int km, int m_id);

		//from Training:
		virtual string toString() const;
		virtual int compareTo(Object*) const;

		//from DbObject
		static string getSqliteStrTocreateTable();
		virtual string getSqliteStrToInsert()const;
		static string getSqliteStrToGetAllRecords();
    
        //callback funcs
        static int callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName);
};

#endif
