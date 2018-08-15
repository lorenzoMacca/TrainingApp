#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
using namespace std;
#include <Date.h>

class Logger{

private:
    static Logger* m_instance;
    Logger();
    bool m_active;

public:
    static const int INFO  = 0;
    static const int DEBUG = 1;
    static const int ERROR = 2;
    static Logger* getInstance();
    void enable();
    void disable();
    void log(int, string );

};

#endif
