#include "Logger.h"

Logger::Logger(){}

Logger* Logger::m_instance = 0;

Logger* Logger::getInstance(){
    if(m_instance == 0){
        m_instance = new Logger();
    }
    return m_instance;
}
