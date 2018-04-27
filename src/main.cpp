#include "List.h"
#include "Training.h"
#include "Date.h"
#include "iostream"
#include "db/DbManager.h"
#include "logger/Logger.h"

#include<unistd.h>

using namespace std;

int main(){
    
    Logger::getInstance()->enable();
    Logger::getInstance()->log(INFO, "I'm the best logger ever");
    
    Date* d = new Date;
    
    cout << d->toString() << endl;
    
    //sleep(2);
    
    Date* d1 =new Date(Date::getCurrentTime());
    
    cout << d1->toString() << endl;
    
    //int res = d->compareTo(d1);
    
    int res = d1->compareTo(d);
    
    cout << res << endl;
    
    TrainingDuration* td = new TrainingDuration(60);
    
    Training t(d1, td);
    List l;
    l.pushBack(&t);
    
    cout << t.toString() << endl;
    
    DbManager* dbManager = DbManager::getInstance();
    cout << dbManager->toString() << endl;
    
    dbManager->connect();
    dbManager->disconnect();
    
    return 0;
}
