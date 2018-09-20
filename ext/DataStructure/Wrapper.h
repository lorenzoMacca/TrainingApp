#ifndef WRAPPER_H
#define WRAPPER_H

#include <string>
#include <sstream>
#include "Object.h"

template <class T>
class Wrapper : public Object{
    
    protected:
        T data;
    
    public:
        Wrapper();
        Wrapper(T const&);
        virtual ~Wrapper(){};
        virtual string toString()const;
        virtual int compareTo(Object*) const;
        Wrapper& operator=(T const&);
};



template <class T>
Wrapper<T>::Wrapper():
data()
{}
template <class T>
Wrapper<T>::Wrapper(T const& d):
data(d)
{}

template <class T>
string Wrapper<T>::toString()const{
    /*stringstream used to convert type like int/char to string*/
    stringstream ss;
    ss << data;
    return ss.str();
}

template <class T>
int Wrapper<T>::compareTo(Object* o) const{
    if(o == 0) return -2;
    if(this == o) return 0;
    if(this->data == ((Wrapper<T>*)o)->data ) return 0;
    if(this->data > ((Wrapper<T>*)o)->data ) return -1;
    if(this->data < ((Wrapper<T>*)o)->data ) return 1;
    return -2;
    
}

template <class T>
Wrapper<T>& Wrapper<T>::operator=(T const& d){
    this->data = d;
    return *this;
}

typedef Wrapper<int> Integer;
typedef Wrapper<char> Char;
typedef Wrapper<bool> Boolean;
typedef Wrapper<double> Double;
typedef Wrapper<float> Float;
typedef Wrapper<std::string> String;


#endif
