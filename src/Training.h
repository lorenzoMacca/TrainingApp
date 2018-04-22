#ifndef TRAINING_H
#define TRAINING_H

#include "Object.h"
#include "Date.h"
#include "TrainingDuration.h"

class Training : public Object{
    
private:
    Date* m_date;
    string m_comment;
    TrainingDuration* m_trainingDuration;
    
public:
    Training(Date*, TrainingDuration*);
    virtual string toString() const;
    virtual int compareTo(Object*) const;
    Date* getDate()const;
    void setDate(Date*);
    TrainingDuration* getTrainingDuration()const;
    void setTrainingDuration(TrainingDuration*);
    
};

#endif
