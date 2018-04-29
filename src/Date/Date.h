#ifndef DATE_H
#define DATE_H

#include <Object.h>
#include <ctime>
#include <sstream>

class Date : public Object{
    
private:
    time_t m_timeT;
    char m_dateSeparator;
    char m_hourSeparator;

public:
    virtual string toString() const;
    virtual int compareTo(Object*) const;
    
    Date();
    Date(string); //a date like this 2018-4-2 18:20:12
    Date(time_t);
    char getDateSeparator()const;
    char getHourSeparator()const;
    void setDateSeparator(char);
    void setHourSeparator(char);
    static time_t getCurrentTime();
    
    
    
};

#endif
