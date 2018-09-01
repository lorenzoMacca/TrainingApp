#include <List.h>
#include <Training.h>
#include <DbManager.h>
#include <Logger.h>
#include <TrainingDuration.h>
#include <User.h>
#include <Utils.h>
#include <vector>
#include <Iterator.h>
#include <unistd.h>
#include <Run.h>
#include <Shoe.h>
#include <Exercise.h>
#include <Abs.h>

using namespace std;

int main(){
    
	Shoe s(1, "asics", "prelude", 132.0);
	cout << s.toString() << endl;
	User u("Lorenzo", "Cozza");

    Logger::getInstance()->enable();
    Logger::getInstance()->log(Logger::INFO, "I'm the best logger ever");

    Logger::getInstance()->log(Logger::INFO, u.toString());


    Date* d = new Date;

    cout << d->toString() << endl;

    //sleep(2);

    Date* d1 =new Date(Date::getCurrentTime());

    Logger::getInstance()->log(Logger::INFO, "check tm serialized");
    cout << d1->toString() <<endl;
    string tmSerialized = d1->getTmSerialized();
    cout << tmSerialized << endl;
    std::vector<string> *ltm = Utils::split(tmSerialized, '-');
    for (std::vector<string>::iterator it=ltm->begin(); it != ltm->end(); ++it)
        std::cout << *it;
    cout << endl;
    Date d11(tmSerialized);
    cout << d11.toString() << endl;
    Logger::getInstance()->log(Logger::INFO, "END check tm serialized");

    cout << d1->toString() << endl;

    //int res = d->compareTo(d1);

    int res = d1->compareTo(d);

    cout << res << endl;

    TrainingDuration td(60);

    Training t(1, d1, td);
    t.setComment("pippo");
    List l;
    l.pushBack(&t);

    cout << "test run" << endl;
    Run r(d1, td, s, 30);
    
    Training *run = new Run(d1, td, s, 45);
    run->getSqliteStrToInsert();
    Logger::getInstance()->log(Logger::INFO, r.toString());
    
    //ABS
    BodyPart bodyPart = ABS;
    Exercise e(-1, bodyPart, "Plank");
    Abs abs1(d1, td, 3, 0, 60 , e);
    Logger::getInstance()->log(Logger::INFO, abs1.toString());

    cout << t.toString() << endl;

    DbManager* dbManager = DbManager::getInstance();
    cout << dbManager->toString() << endl;

    dbManager->connect();
    dbManager->init();

    //create table
    dbManager->exec(Training::getSqliteStrTocreateTable(), 0);
    dbManager->exec(Shoe::getSqliteStrTocreateTable(), 0);
    dbManager->exec(Run::getSqliteStrTocreateTable(), 0);
    dbManager->exec(Exercise::getSqliteStrTocreateTable(), 0);
    
     //insert
    dbManager->exec(t.getSqliteStrToInsert(), 0);
    unsigned idTraining = dbManager->getLastID();
    dbManager->exec(s.getSqliteStrToInsert(), 0);
    r.setId(idTraining);
    dbManager->exec(r.getSqliteStrToInsert(), 0);
    dbManager->exec(e.getSqliteStrToInsert(), 0);

    List* listTraining = new List;
    List* listShoes = new List;
    List* listExercise = new List;
    dbManager->exec(Training::getSqliteStrToGetAllRecords(), listTraining, Training::callbackAfterSelect);
    dbManager->exec(Shoe::getSqliteStrToGetAllRecords(), listShoes, Shoe::callbackAfterSelect);
    dbManager->exec(Exercise::getSqliteStrToGetAllRecords(), listExercise, Exercise::callbackAfterSelect);
    /*Iterator* i = list->getIterator();
    while(i->hasNext()){
    	string tmp = i->getCurrentValue()->toString();
    	cout << tmp << endl;
    	(*i)++;
    }*/
    
    

    dbManager->disconnect();


    delete listTraining;
    delete listShoes;
    return 0;
}
