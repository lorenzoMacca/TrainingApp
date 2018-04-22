#include "List.h"
#include "Training.h"
#include "Date.h"
#include "iostream"

#include<unistd.h>

using namespace std;

int main(){
    
   
    
    Date* d = new Date;
    
    cout << d->toString() << endl;
    
    //sleep(2);
    
    Date* d1 =new Date(Date::getCurrentTime());
    
    cout << d1->toString() << endl;
    
    //int res = d->compareTo(d1);
    
    int res = d1->compareTo(d);
    
    cout << res << endl;
    
    Training t(d1);
    List l;
    l.pushBack(&t);
    
    cout << t.toString() << endl;
    
    return 0;
}
