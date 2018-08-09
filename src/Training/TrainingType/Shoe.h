#ifndef SHOE_H
#define SHOE_H

#include <Object.h>
#include <DbObject.h>
#include <sstream>

class Shoe : public Object, DbObject{
	private:
		string m_brand;
		string m_model;
		float m_price;
		int m_id_db;
	
	public:
		Shoe(int id=-1, string brand="", string model="", float price=0);
		
		//from Object
		virtual string toString() const;
		virtual int compareTo(Object*) const;
	
		//from DbObject
		static string getSqliteStrTocreateTable();
		virtual string getSqliteStrToInsert()const;
		static string getSqliteStrToGetAllRecords();
};

#endif