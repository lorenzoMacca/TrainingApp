#ifndef DATE_H
#define DATE_H

#include <Object.h>
#include <ctime>
#include <sstream>
#include <Utils.h>
#include <vector>

class Date : public Object{
    
private:
    time_t m_timeT;
    char m_dateSeparator;
    char m_hourSeparator;

public:
    virtual string toString() const;
    virtual int compareTo(Object*) const;
    
    Date();
    Date(string); //from tm serialized
    Date(time_t);
    ~Date();
    char getDateSeparator()const;
    char getHourSeparator()const;
    void setDateSeparator(char);
    void setHourSeparator(char);
    static time_t getCurrentTime();
    string getTmSerialized()const;
    bool deserializeToTm(string str, struct tm * timeptr)const;
    
    
    
};

#endif
