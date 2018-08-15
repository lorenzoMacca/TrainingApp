#include "Logger.h"

Logger::Logger(){
    this->m_active=false;
}

Logger* Logger::m_instance = 0;

Logger* Logger::getInstance(){
    if(m_instance == 0){
        m_instance = new Logger();
    }
    return m_instance;
}

void Logger::enable(){
    this->m_active=true;
}

void Logger::disable(){
    this->m_active=false;
}

void Logger::log(int t, string mess){
    Date d(Date::getCurrentTime());
    string logType = "";
    switch(t){
        case Logger::INFO:
            logType = "INFO";
            break;
        case Logger::DEBUG:
            logType = "DEBUG";
            break;
        case Logger::ERROR:
            logType = "ERROR";
            break;
        default:
            logType = "NA";
    }
    cout << d.toString() << "[" << logType << "]" << " - { " << mess << "}" << endl;
}
