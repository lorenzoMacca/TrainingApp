#ifndef RUN_H
#define RUN_H

#include <Training.h>
#include <Logger.h>
#include <Shoe.h>

class Run : public Training{

	private:
		unsigned m_km;
		Shoe m_shoe;


	public:
		Run(Date*, TrainingDuration, Shoe s);

		//from Training:
		virtual string toString() const;
		virtual int compareTo(Object*) const;

		//from DbObject
		static string getSqliteStrTocreateTable();
		virtual string getSqliteStrToInsert()const;
		static string getSqliteStrToGetAllRecords();
};

#endif
