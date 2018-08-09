#include "Shoe.h"

Shoe::Shoe(int id, string brand, string model, float price){
	this->m_brand=brand;
	this->m_model=model;
	this->m_price=price;
	this->m_id_db=id;
}

string Shoe::toString() const{
	stringstream sstr;
	sstr << "[Shoe: " 
		 << "ID: " << this->m_id_db << " - "
		 << "Brand: " << this->m_brand << " - "
		 << "Model: " << this->m_model << " - "
		 << "Price: " << this->m_price
		 << " ]";
	return sstr.str();
}

int Shoe::compareTo(Object*) const{return -2;}

string Shoe::getSqliteStrTocreateTable(){
	stringstream sql;
	sql << "CREATE TABLE SHOE("
		<< "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		<< "BRAND TEXT NOT NULL, "
		<< "MODEL TEXT NOT NULL, "
		<< "PRICE INTEGER NOT NULL);";
	return sql.str();
}

string Shoe::getSqliteStrToInsert()const{
	stringstream sql;
	sql << "INSERT INTO SHOE (BRAND, PRICE, MODEL) " 
		<< "VALUES ('" << m_brand << "', "
		<< this->m_id_db << ", "
		<< "'" << this->m_model << "');";
	return sql.str();
}

string Shoe::getSqliteStrToGetAllRecords(){
	return "select * from SHOE";
}

int Shoe::callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName) {
	if(list_Not_casted == 0) return 0;
	List* list = static_cast<List*>(list_Not_casted);
	int i;
	int id = -1;
	string brand = "";
	string model = "";
	float price = 0.0;
	for(i = 0; i<argc; i++) {
		string columnNme(azColName[i]);
		if(columnNme == "BRAND"){
			brand = argv[i];
		}else if(columnNme == "MODEL"){
			model=argv[i];
		}else if(columnNme == "ID"){
			id=stoi(argv[i]);
		}else if(columnNme == "PRICE"){
			price=stof(argv[i]);
		}
	}
	Shoe *s = new Shoe(id, brand, model, price);
	Logger::getInstance()->log(INFO, "DbManager: SHOE instance created: " + s->toString() );
	list->pushBack(s);
	return 0;
}
