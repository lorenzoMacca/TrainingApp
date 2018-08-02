#include "User.h"

User::User(string name, string surname){
	this->m_name=name;
	this->m_surname=surname;
}

string User::toString() const{
	string res="[User: ";
	res+="Name: "+this->m_name+this->m_surname;
	res+=" ]";
	return res;
}

int User::compareTo(Object*) const{
	return 0;
}