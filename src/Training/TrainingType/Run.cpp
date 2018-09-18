#include "Run.h"

Run::Run(Date* date, TrainingDuration du, Shoe s, int km):Training(date, du){
	this->m_shoe=s;
    this->m_km=km;
    this->m_id=-1;
}

Run::Run(Date* date, TrainingDuration du, Shoe s, int km, int id):Training(date, du){
    this->m_shoe=s;
    this->m_km=km;
    this->m_id=id;
}

void Run::setShoeId(int i){
    this->m_shoe.setId(i);
}

string Run::toString() const{
    //const Training*  = this;
	stringstream str;
    str << "[RUN:"
        << "ID: " << this->m_id << " - "
        << "Km:" << this->m_km << " - "
        << this->Training::toString(this)
        << this->m_shoe.toString()
        << "]";
	return str.str();
}

int Run::compareTo(Object*) const{
	//TODO implementation is missing
	return -2;
}

string Run::getSqliteStrTocreateTable(){
    stringstream sql;
	sql << "CREATE TABLE RUN("
		<< "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        << "ID_TRAINING INTEGER NOT NULL, "
		<< "KM INTEGER NOT NULL, "
		<< "ID_SHOE INTEGER NOT NULL, "
		<< "FOREIGN KEY(ID_SHOE) REFERENCES SHOE(ID), "
        << "FOREIGN KEY(ID_TRAINING) REFERENCES TRAINING(ID)"
		<< ");";
	return sql.str();
}

string Run::getSqliteStrToInsert()const{
    stringstream sql;
	sql << "INSERT INTO RUN (ID_TRAINING, KM, ID_SHOE) "
		<< "VALUES ("
        << this->m_id_training << ", "
		<< this->m_km << ", "
		<< this->m_shoe.getId()
		<< ");";
	return sql.str();
}

string Run::getSqliteStrToGetAllRecords(){
    return "select RUN.ID AS RUN_ID, RUN.*, SHOE.ID AS SHOE_ID, SHOE.*, TRAINING.ID AS TRAINING_ID, TRAINING.* from RUN, TRAINING, SHOE where RUN.ID_TRAINING=TRAINING.ID and RUN.ID_SHOE=SHOE.ID";
}

int Run::callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName) {
    // TRAINING_ID ID DATE DURATION COMMENT
    if(list_Not_casted == 0)
        return 0;
    List* list = static_cast<List*>(list_Not_casted);
    //run
    int runId = -1;
    int km = 0;
    //shoe
    int shoeId = -1;
    string brand = "";
    string model = "";
    float price = 0.0;
    //training
    int trainingId = -1;
    Date *d = 0;
    string comment = "";
    unsigned int timeDuration = 0;
    for(int i = 0; i<argc; i++) {
        string columnNme(azColName[i]);
        if(columnNme == "RUN_ID"){
            runId=stoi(argv[i]);
        }else if(columnNme == "KM"){
            km=stoi(argv[i]);
        }else if(columnNme == "SHOE_ID"){
            shoeId=stoi(argv[i]);
        }else if(columnNme == "BRAND"){
            brand = argv[i];
        }else if(columnNme == "MODEL"){
            model=argv[i];
        }else if(columnNme == "PRICE"){
            price=stof(argv[i]);
        }else if(columnNme == "DATE"){
            d = new Date(argv[i]);
        }else if(columnNme == "COMMENT"){
            comment=argv[i];
        }else if(columnNme == "DURATION"){
            timeDuration = stoi(argv[i]);
        }else if(columnNme == "TRAINING_ID"){
            trainingId = stoi(argv[i]);
        }
    }
    TrainingDuration trainingDuration(timeDuration);
    Shoe s = Shoe(shoeId, brand, model, price);
    Run* r = new Run(d, trainingDuration, s, km, runId);
    r->setTrainingId(trainingId);
    Logger::getInstance()->log(Logger::INFO, "DbManager: RUN instance created: " + r->toString() );
    list->pushBack(r);

    return 0;
}
