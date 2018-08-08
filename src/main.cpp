#include <List.h>
#include <Training.h>
//#include "Date.h"
//#include "iostream"
#include <DbManager.h>
#include <Logger.h>
#include <TrainingDuration.h>
#include <User.h>
#include <Utils.h>
#include <vector>
#include <Iterator.h>
#include <unistd.h>
#include <Run.h>

using namespace std;

int main(){
	
	
	
	User u("Lorenzo", "Cozza");
    
    Logger::getInstance()->enable();
    Logger::getInstance()->log(INFO, "I'm the best logger ever");
    
    Logger::getInstance()->log(INFO, u.toString());
    
    
    Date* d = new Date;
    
    cout << d->toString() << endl;
    
    //sleep(2);
    
    Date* d1 =new Date(Date::getCurrentTime());
    
    Logger::getInstance()->log(INFO, "check tm serialized");
    cout << d1->toString() <<endl;
    string tmSerialized = d1->getTmSerialized();
    cout << tmSerialized << endl;
    std::vector<string> *ltm = Utils::split(tmSerialized, '-');
    for (std::vector<string>::iterator it=ltm->begin(); it != ltm->end(); ++it)
        std::cout << *it;
    cout << endl;
    Date d11(tmSerialized);
    cout << d11.toString() << endl;
    Logger::getInstance()->log(INFO, "END check tm serialized");
    
    cout << d1->toString() << endl;
    
    //int res = d->compareTo(d1);
    
    int res = d1->compareTo(d);
    
    cout << res << endl;
    
    TrainingDuration* td = new TrainingDuration(60);
    
    Training t(d1, td);
    t.setComment("pippo");
    List l;
    l.pushBack(&t);
    
    cout << "test run" << endl;
    Run r(d1, td);
    Training *run = new Run(d1, td);
    run->getSqliteStrToInsert();
    
    cout << t.toString() << endl;
    
    DbManager* dbManager = DbManager::getInstance();
    cout << dbManager->toString() << endl;
    
    dbManager->connect();
    
    bool resQ = dbManager->exec(t.getSqliteStrTocreateTable());
   
    bool resQ1 = dbManager->exec(t.getSqliteStrToInsert());
    
    List* list = new List;
    bool resQ2 = dbManager->exec(Training::getSqliteStrToGetAllRecords(), list);
    /*Iterator* i = list->getIterator();
    while(i->hasNext()){
    	string tmp = i->getCurrentValue()->toString();
    	cout << tmp << endl;
    	(*i)++;
    }*/
     
    dbManager->disconnect();
    
    
    delete list;
    return 0;
}
