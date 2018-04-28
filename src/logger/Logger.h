#ifndef LOGGER_H
#define LOGGER_H

#define DEBUG 0
#define ERROR 1
#define INFO  2

#include <string>
#include <iostream>
using namespace std;
#include "../Date.h"

class Logger{
    
private:
    static Logger* m_instance;
    Logger();
    bool m_active;
    
public:
    static Logger* getInstance();
    void enable();
    void disable();
    void log(int, string );
    
};

#endif
