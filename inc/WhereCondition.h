#ifndef WHERE_CONDITION_H
#define WHERE_CONDITION_H

#include "Object.h"
#include <sstream>

class WhereCondition: public Object{

private:
    string m_left, m_right, m_operator;

public:
    WhereCondition(string, string, string op="");
    string getLeft()const;
    string getRight()const;
    string getOperator()const;
    
    virtual string toString() const;
    virtual int compareTo(Object*) const;
};

#endif
