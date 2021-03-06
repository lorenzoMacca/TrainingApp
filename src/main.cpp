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
#include <GenericExercise.h>
#include <Swim.h>
#include <Break.h>
#include <Session.h>
#include <WhereCondition.h>

using namespace std;

int main(){
    
    {
        cout << "Checking the distructor" << endl;
        TrainingDuration td(1);
        //Training* t = new Training(new Date(Date::getCurrentTime()), td);
        Shoe s(0, "asics", "prelude", 132.0);
        Training* t1 = new Run(new Date(Date::getCurrentTime()), td, s, 42.0);
        Run* t2 = new Run(new Date(Date::getCurrentTime()), td, s, 42.0);
        //delete t;
        delete t1;
        delete t2;
        /*the following code can couse bad access in the mamory during tha distruction call
        Date* d = new Date(Date::getCurrentTime());
        Training* t2 = new Training(d, td);
        Training* t3 = new Run(d, td, s, 42.0);
        delete t2;
        delete t3;
         */
        cout << "[END] - Checking the distructor" << endl;
        
    }
    
    
    Logger::getInstance()->enable();
    Logger::getInstance()->log(Logger::INFO, "I'm the best logger ever");

    User u("Lorenzo", "Cozza");
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

    TrainingDuration td(60.2);

    
    DbManager* dbManager = DbManager::getInstance();
    dbManager->connect();
    dbManager->init();
    
    int i=0;
    
    while(i++<1){

    //create table
    dbManager->exec(Session::getSqliteStrTocreateTable(), 0);
    dbManager->exec(Training::getSqliteStrTocreateTable(), 0);
    dbManager->exec(Shoe::getSqliteStrTocreateTable(), 0);
    dbManager->exec(Run::getSqliteStrTocreateTable(), 0);
    dbManager->exec(Exercise::getSqliteStrTocreateTable(), 0);
    dbManager->exec(GenericExercise::getSqliteStrTocreateTable(), 0);
    dbManager->exec(Swim::getSqliteStrTocreateTable(), 0);
    dbManager->exec(Break::getSqliteStrTocreateTable(), 0);
    
    //start session
    Session session;
    
    
    //insert Shoe
    Shoe s(0, "asics", "prelude", 132.0);
    dbManager->exec(s.getSqliteStrToInsert(), 0);
    int idShoe = dbManager->getLastID();
    
    //insert Run
    Training *run = new Run(new Date(Date::getCurrentTime()), td, s, 21.2);
    //dbManager->exec(run->Training::getSqliteStrToInsert(), 0);
    //run->setTrainingId(dbManager->getLastID());
    ((Run*)run)->setShoeId(idShoe);
    //dbManager->exec(run->getSqliteStrToInsert(), 0);
    
    //Insert break
    TrainingDuration tdBreak1(3.5);
    Break* break1 = new Break(tdBreak1);
    //dbManager->exec(break1->getSqliteStrToInsert(), 0);
    //Do you need to save the last id?
    
    //insert Exercise
    BodyPart bodyPart = ABS;
    BodyPart bodyPart2 = SQUAT;
    Exercise plank(-1, bodyPart, "Plank");
    Exercise squat(-1, bodyPart2, "Squat");
    dbManager->exec(plank.getSqliteStrToInsert(), 0);
    unsigned idExercise = dbManager->getLastID();
    dbManager->exec(squat.getSqliteStrToInsert(), 0);
    unsigned idExercisesquat = dbManager->getLastID();
    
    //insert Abs
    Training *abs1 = new GenericExercise(new Date(Date::getCurrentTime()), td, 0, 60, 0 , plank);
    ((GenericExercise*)abs1)->getExercise().setId(idExercise);
    //dbManager->exec(abs1->Training::getSqliteStrToInsert(), 0);
    //abs1->setTrainingId(dbManager->getLastID());
    //dbManager->exec(abs1->getSqliteStrToInsert(), 0);
    
    //insert SWIM
    TrainingDuration tdSwim(31.4);
    Training *swim1 = new Swim(new Date(Date::getCurrentTime()), tdSwim, 0.750);
    //dbManager->exec(swim1->Training::getSqliteStrToInsert(), 0);
    //swim1->setTrainingId(dbManager->getLastID());
    //dbManager->exec(swim1->getSqliteStrToInsert(), 0);
        
    Training *squat1 = new GenericExercise(new Date(Date::getCurrentTime()), td, 0, 60, 0 , squat);
    ((GenericExercise*)squat1)->getExercise().setId(idExercisesquat);
    
    session.addActivity(run);
    session.addActivity(break1);
    session.addActivity(abs1);
    session.addActivity(swim1);
    session.addActivity(squat1);
    
    session.saveAll();
    
    //cout << session.toString() << endl;
    

    List* listTraining = new List;
    List* listShoes = new List;
    List* listExercise = new List;
    List* listRun = new List;
    List* listAbs = new List;
    List* listSwim = new List;
    List* listBreaks = new List;
    List* listSession = new List;
    dbManager->exec(Training::getSqliteStrToGetAllRecords(), listTraining, Training::callbackAfterSelect);
    dbManager->exec(Shoe::getSqliteStrToGetAllRecords(), listShoes, Shoe::callbackAfterSelect);
    dbManager->exec(Exercise::getSqliteStrToGetAllRecords(), listExercise, Exercise::callbackAfterSelect);
    dbManager->exec(Run::getSqliteStrToGetAllRecords(), listRun, Run::callbackAfterSelect);
    dbManager->exec(GenericExercise::getSqliteStrToGetAllRecords(), listAbs, GenericExercise::callbackAfterSelect);
    dbManager->exec(Swim::getSqliteStrToGetAllRecords(), listSwim, Swim::callbackAfterSelect);
    dbManager->exec(Break::getSqliteStrToGetAllRecords(), listBreaks, Break::callbackAfterSelect);
    dbManager->exec(Session::getSqliteStrToGetAllRecords(), listSession, Session::callbackAfterSelect);
    
    /*Iterator* i = list->getIterator();
    while(i->hasNext()){
    	string tmp = i->getCurrentalue()->toString();
    	cout << tmp << endl;
    	(*i)++;
    }*/
    
    List conditions;
    conditions.pushBack(new WhereCondition("A", "B", "="));
    conditions.pushBack(new WhereCondition("B", "C", "="));
    conditions.pushBack(new WhereCondition("C", "D", "="));
    //cout << Training::getSqliteStrToGetRecords(Swim::getSqliteStrToGetAllRecords(), conditions, "and") << endl;
    
    //load all the activities related to
    Session* sessionFromDb = static_cast<Session*>(listSession->getValueLastElement());
    sessionFromDb->loadActivities();
    cout << "Session From Db:" << sessionFromDb->toString() << endl;
    
   

    delete listTraining;
    delete listShoes;
    delete listExercise;
    delete listRun;
    delete listAbs;
    delete listSwim;
    delete listBreaks;
    delete listSession;
        
    }
    
    //dbManager->disconnect();
    DbManager::resetInstance();
    return 0;
}
