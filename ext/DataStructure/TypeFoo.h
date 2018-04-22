#ifndef TYPE_FOO_H
#define TYPE_FOO_H

#include "Object.h"


class TypeFoo: public Object{

	public:
		string name;
		int value;

		TypeFoo(string name, int value){
			this->name=name;
			this->value=value;
		}

		virtual string toString()const{
			string s = "Hi! I am a dummy " + this->name + " class";
			return s;
		};
		
		virtual int compareTo(Object* o)const{
			//cout << "Comparing: " << this->value << " with " << ((TypeFoo*)o)->value <<endl;
			if(o == 0) return -2;
			if(this == o) return 0;
			if(this->value == ((TypeFoo*)o)->value) return 0;
			if(this->value > ((TypeFoo*)o)->value) return -1;
			if(this->value < ((TypeFoo*)o)->value) return 1;
            return -2;
		}
};

#endif
