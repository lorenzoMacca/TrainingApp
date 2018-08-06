#include "UserData.h"

UserData::UserData(){
	
}

string UserData::toString() const{
	string res = "[UserData:";
	res += "]";
	return res;
}

int UserData::compareTo(Object*) const{
	return -2;
}