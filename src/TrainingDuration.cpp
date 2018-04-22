#include "TrainingDuration.h"

TrainingDuration::TrainingDuration(unsigned int d){
    this->m_durationInMin = d;
}

string TrainingDuration::toString() const{
    string res =  "[TrainingDuration ";
    res += "]";
    return res;
}

int TrainingDuration::compareTo(Object* o) const{
    if(this->m_durationInMin > ((TrainingDuration*)o)->getDuration(MINUTES)){
        return -1;
    }else if(this->m_durationInMin < ((TrainingDuration*)o)->getDuration(MINUTES)){
        return 1;
    }
    return 0;
}

float TrainingDuration::getDuration(int type)const{
    if(type == HOURS){
            return this->m_durationInMin/60.0;
    }
    return this->m_durationInMin;
}

void TrainingDuration::setDuration(unsigned int d){
    this->m_durationInMin = d;
}
