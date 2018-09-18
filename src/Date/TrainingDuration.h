#ifndef TRAINING_DURATION_H
#define TRAINING_DURATION_H

#include "Object.h"


class TrainingDuration : public Object{

private:
    float m_durationInMin;

public:
    static const int HOURS = 0;
    static const int MINUTES = 1;
    static const int SECONDS = 2;

    TrainingDuration(float );
    TrainingDuration();
    virtual string toString() const;
    virtual int compareTo(Object*) const;
    float getDuration(int type=MINUTES)const;
    void setDuration(float);

};

#endif
