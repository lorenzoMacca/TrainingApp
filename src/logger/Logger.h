#ifndef LOGGER_H
#define LOGGER_H

class Logger{
    
private:
    static Logger* m_instance;
    Logger();
    
public:
    static Logger* getInstance();
    
};

#endif
