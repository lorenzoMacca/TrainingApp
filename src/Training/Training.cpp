#include "Training.h"

Training::Training(Date* d, TrainingDuration* t){
    this->m_date = d;
    this->m_trainingDuration = t;
}

string Training::toString() const{
	stringstream res;
	res <<  "[Training: ";
    res << this->m_date->toString() << " - ";
    res << this->m_trainingDuration->toString() << " - ";
    res << "Comment: " << this->m_comment;
    res << "]";
    return res.str();;
}

int Training::compareTo(Object* o) const{
    return 0;
}

Date* Training::getDate()const{
    return this->m_date;
}

void Training::setDate(Date* d){
    if(d!=0){
        delete this->m_date;
        this->m_date = d;
    }
}

TrainingDuration* Training::getTrainingDuration()const{
    return this->m_trainingDuration;
}

void Training::setTrainingDuration(TrainingDuration* t){
    if(t!=0){
        this->m_trainingDuration = t;
    }
}

void Training::setComment(string s){
	this->m_comment = s;
}

string Training::getComment()const{
	return this->m_comment;
}

string Training::getSqliteStrTocreateTable(){
	stringstream sql;
	sql << "CREATE TABLE TRAINING("
		<< "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		<< "DATE TEXT NOT NULL, "
		<< "DURATION INTEGER NOT NULL, "
		<< "COMMENT TEXT);";
	return sql.str();
}

string Training::getSqliteStrToInsert()const{
	stringstream sql;
	sql << "INSERT INTO TRAINING (DATE, DURATION, COMMENT) "
		<< "VALUES ('" << this->m_date->getTmSerialized() << "', "
		<< this->m_trainingDuration->getDuration() << ", "
		<< "'" << this->m_comment << "');";
	return sql.str();
}

string Training::getSqliteStrToGetAllRecords(){
	return "select * from TRAINING";
}

int Training::callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName) {
	if(list_Not_casted == 0) return 0;
	List* list = static_cast<List*>(list_Not_casted);
	int i;
	Date *d = 0;
	string comment = "";
	TrainingDuration* trainingDuration;
	for(i = 0; i<argc; i++) {
		string columnNme(azColName[i]);
		if(columnNme == "DATE"){
			d = new Date(argv[i]);
		}else if(columnNme == "COMMENT"){
			comment=argv[i];
		}else if(columnNme == "DURATION"){
			trainingDuration=new TrainingDuration(stoi(argv[i]));
		}
	}
	Training *t = new Training(d, trainingDuration);
	t->setComment(comment);
	Logger::getInstance()->log(Logger::INFO, "DbManager: Training instance created: " + t->toString() );
	list->pushBack(t);
	return 0;
}
