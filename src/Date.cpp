#include "Date.h"


string Date::toString() const{
    tm *ltm = localtime(&this->m_timeT);
    stringstream res;
    res << "["
        << 1900 + ltm->tm_year << this->m_dateSeparator
        << 1 + ltm->tm_mon << this->m_dateSeparator
        << ltm->tm_mday
        << " "
        << ltm->tm_hour << this->m_hourSeparator
        << ltm->tm_min  << this->m_hourSeparator
        << ltm->tm_sec
        << "]";
    return res.str();
}

int Date::compareTo(Object* o) const{
    double diff = difftime(this->m_timeT, ((Date*)o)->m_timeT);
    if(diff > 0){
        return -1;
    }else if(diff < 0){
        return 1;
    }
    return 0;
}

Date::Date(){
    this->m_dateSeparator = '-';
    this->m_hourSeparator = ':';
    // current date/time based on current system
    this->m_timeT = time(0);
    
    // convert now to string form
    //char* dt = ctime(&now);
    
    //this->m_ltm = localtime(&now);
}

Date::Date(time_t t){
    this->m_dateSeparator = '-';
    this->m_hourSeparator = ':';
    this->m_timeT = t;
}

char Date::getDateSeparator()const{
    return this->m_dateSeparator;
}

char Date::getHourSeparator()const{
    return this->m_hourSeparator;
}

void Date::setDateSeparator(char c){
    this->m_dateSeparator = c;
}

void Date::setHourSeparator(char c){
    this->m_hourSeparator = c;
}

time_t Date::getCurrentTime(){
    return time(0);
}
