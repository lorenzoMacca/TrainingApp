#include "Date.h"


string Date::toString() const{
    tm *ltm = localtime(&this->m_timeT);
    stringstream res;
    res << "[Date: "
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

Date::Date(string str){
	this->m_dateSeparator = '-';
	this->m_hourSeparator = ':';
	tm * timeptr = new tm;
	if( this->deserializeToTm(str,timeptr) ){
		this->m_timeT = mktime(timeptr);
	}else{
		this->m_timeT = time(0);
	}
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

string Date::getTmSerialized()const{
	tm *ltm = localtime(&this->m_timeT);
	stringstream str;
	str << ltm->tm_sec << "-"
	    << ltm->tm_min << "-"
		<< ltm->tm_hour << "-"
		<< ltm->tm_mday << "-"
		<< ltm->tm_mon << "-"
		<< ltm->tm_year << "-"
		<< ltm->tm_wday << "-"
		<< ltm->tm_yday << "-"
		<< ltm->tm_isdst;
	return str.str();
}

bool Date::deserializeToTm(string str, struct tm * timeptr)const{
	std::vector<string> *vtm = Utils::split(str, '-');
	if(vtm->size() != 9) return false;
	timeptr->tm_sec   = stoi(vtm->at(0));
	timeptr->tm_min   = stoi(vtm->at(1));
	timeptr->tm_hour  = stoi(vtm->at(2));
	timeptr->tm_mday  = stoi(vtm->at(3));
	timeptr->tm_mon   = stoi(vtm->at(4));
	timeptr->tm_year  = stoi(vtm->at(5));
	timeptr->tm_wday  = stoi(vtm->at(6));
	timeptr->tm_yday  = stoi(vtm->at(7));
	timeptr->tm_isdst = stoi(vtm->at(8));
	delete vtm;
	return true;
}




