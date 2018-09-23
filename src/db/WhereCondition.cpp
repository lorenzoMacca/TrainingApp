#include "WhereCondition.h"

WhereCondition::WhereCondition(string l, string r , string op){
    this->m_left = l;
    this->m_right = r;
    this->m_operator = op;
}

string WhereCondition::getLeft()const{
    return this->m_left;
}

string WhereCondition::getRight()const{
    return this->m_right;
}

string WhereCondition::getOperator()const{
    return this->m_operator;
}

string WhereCondition::toString() const{
    stringstream res;
    res << "[WhereCondition "
    << this->m_left << " " << this->m_operator << " " << this->m_right
    << "]";
    return res.str();
}

int WhereCondition::compareTo(Object*) const{return -2;}
