#ifndef TRAINING_DURATION_H
#define TRAINING_DURATION_H

#include "Object.h"


class TrainingDuration : public Object{

private:
    unsigned int m_durationInMin;

public:
    static const int HOURS = 0;
    static const int MINUTES = 1;

    TrainingDuration(unsigned int );
    TrainingDuration();
    virtual string toString() const;
    virtual int compareTo(Object*) const;
    int getDuration(int type=MINUTES)const;
    void setDuration(unsigned int);

};

#endif
