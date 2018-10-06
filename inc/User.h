#ifndef USER_H
#define USER_H

#include <Object.h>
#include <UserData.h>

class User : public Object {

private:
	string m_name;
	string m_surname;
	UserData m_userData;
	
public:
	User(string, string);
	virtual string toString() const;
	virtual int compareTo(Object*) const;
	
};

#endif