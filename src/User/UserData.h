#ifndef USERDATA_H
#define USERDATA_H

#include <Object.h>

class UserData : public Object{
	public:
		UserData();
		virtual string toString() const;
		virtual int compareTo(Object*) const;
};

#endif