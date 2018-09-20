#include "Abs.h"

Abs::Abs(Date* date, TrainingDuration du, unsigned int reps, unsigned int time, unsigned int weight, Exercise e, int id):Training(date, du){
    this->m_id = id;
    this->m_reps = reps;
    this->m_time = time;
    this->m_weight = weight;
    this->m_exercise = e;
}

Abs::~Abs(){
    //Logger::getInstance()->log(Logger::INFO, "Abs: destructor called");
}

Exercise& Abs::getExercise(){
    return this->m_exercise;
}

//from Training:
string Abs::toString() const{
    stringstream sstr;
    sstr << "[ABS: "
    << "ID: " << this->m_id << " - "
    << this->m_exercise.toString() << " - "
    << "Reps: " << this->m_reps << " - "
    << "Time: " << this->m_time << " - "
    << "Weight: " << this->m_weight << " - "
    << this->Training::toString(this)
    << " ]";
    return sstr.str();
}

int Abs::compareTo(Object*) const{
    return -2;
}

//from DbObject
string Abs::getSqliteStrTocreateTable(){
    stringstream sql;
    sql << "CREATE TABLE ABS("
    << "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
    << "REPS INTEGER NOT NULL, "
    << "TIME INTEGER NOT NULL, "
    << "WEIGHT INTEGER NOT NULL, "
    << "ID_EXERCISE INTEGER NOT NULL, "
    << "ID_TRAINING INTEGER NOT NULL, "
    << "FOREIGN KEY(ID_EXERCISE) REFERENCES EXERCISE(ID)"
    << "FOREIGN KEY(ID_TRAINING) REFERENCES TRAINING(ID)"
    << ");";
    return sql.str();
}

string Abs::getSqliteStrToInsert()const{
    stringstream sql;
    sql << "INSERT INTO ABS (REPS, TIME, WEIGHT, ID_EXERCISE, ID_TRAINING) "
    << "VALUES ("
    << this->m_reps << ", "
    << this->m_time << ", "
    << this->m_weight << ", "
    << this->m_exercise.getId() << ", "
    << this->m_id_training
    << ");";
    return sql.str();
}

string Abs::getSqliteStrToGetAllRecords(){
     return "select ABS.ID AS ABS_ID, ABS.*, EXERCISE.ID AS EXERCISE_ID, EXERCISE.*, TRAINING.ID AS TRAINING_ID, TRAINING.* from ABS, EXERCISE, TRAINING where ABS.ID_EXERCISE = EXERCISE.ID AND ABS.ID_TRAINING=TRAINING.ID";
}

int Abs::callbackAfterSelect(void *list_Not_casted, int argc, char **argv, char **azColName) {
    // TRAINING_ID ID DATE DURATION COMMENT
    if(list_Not_casted == 0)
        return 0;
    List* list = static_cast<List*>(list_Not_casted);
    //Exercise
    int exerciseId = -1;
    string name = "";
    BodyPart bodyPart = NA;
    int absId = -1;
    unsigned int reps = 0;
    unsigned int time = 0;
    unsigned int weight = 0;
    //training
    float timeDuration = 0;
    int trainingId = -1;
    Date *d = 0;
    string comment = "";
    for(int i = 0; i<argc; i++) {
        string columnNme(azColName[i]);
        if(columnNme == "BODYPART"){
            Exercise::itoBodyPart(&bodyPart, stoi(argv[i]));
        }else if(columnNme == "NAME"){
            name=argv[i];
        }else if(columnNme == "EXERCISE_ID"){
            exerciseId=stoi(argv[i]);
        }else if(columnNme == "ABS_ID"){
            absId=stoi(argv[i]);
        }else if(columnNme == "REPS"){
            reps=stoi(argv[i]);
        }else if(columnNme == "TIME"){
            time=stoi(argv[i]);
        }else if(columnNme == "DATE"){
            d = new Date(argv[i]);
        }else if(columnNme == "COMMENT"){
            comment=argv[i];
        }else if(columnNme == "DURATION"){
            timeDuration = stof(argv[i]);
        }else if(columnNme == "TRAINING_ID"){
            trainingId = stoi(argv[i]);
        }else if(columnNme == "WEIGHT"){
            weight = stoi(argv[i]);
        }
    }
    Exercise e(exerciseId, bodyPart, name);
    TrainingDuration trainingDuration(timeDuration);
    Abs *abs = new Abs(d, trainingDuration, reps, time, weight, e, absId);
    abs->setTrainingId(trainingId);
    Logger::getInstance()->log(Logger::INFO, "DbManager: ABS instance created: " + abs->toString() );
    list->pushBack(abs);
    return 0;
}
