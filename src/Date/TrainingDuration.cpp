#include "TrainingDuration.h"

TrainingDuration::TrainingDuration(float d){
    this->m_durationInMin = d;
}

TrainingDuration::TrainingDuration(){
    this->m_durationInMin = 0.0;
}

string TrainingDuration::toString() const{
    string res =  "[TrainingDuration: ";
    res += to_string(this->getDuration(MINUTES));
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
    }else if(type == SECONDS){
        //TODO: return the right number in seconds
    }
    return this->m_durationInMin;
}

void TrainingDuration::setDuration(float d){
    this->m_durationInMin = d;
}
