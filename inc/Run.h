#ifndef RUN_H
#define RUN_H

#include <Training.h>
#include <Logger.h>
#include <Shoe.h>

class Run : public Training{

	private:
        int m_id;
		float m_km;
		Shoe m_shoe;

	public:
		Run(Date*, TrainingDuration, Shoe s, float km);
        Run(Date*, TrainingDuration, Shoe s, float km, int m_id);
        ~Run();
    
        static const string TAG;
    
        void setShoeId(int i);

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
