#ifndef RUN_H
#define RUN_H

#include <Training.h>
#include <Logger.h>
#include <Shoe.h>

class Run : public Training{

	private:
        int m_id;
		unsigned m_km;
		Shoe m_shoe;


	public:
		Run(Date*, TrainingDuration, Shoe s, int km);
        Run(Date*, TrainingDuration, Shoe s, int km, int m_id);
        void setShoeId(int i);

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
