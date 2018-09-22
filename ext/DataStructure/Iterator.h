#ifndef Iterator_H
#define Iterator_H

#include "Node.h"
#include "Object.h"

class Iterator{

	public:
        virtual ~Iterator(){};
		virtual Object* getCurrentValue()const = 0;
		virtual bool hasNext()const = 0;
		virtual Iterator* operator++() = 0;
		virtual Iterator* operator++(int) = 0;
		virtual Iterator* operator--() = 0;
		virtual Iterator* operator--(int) = 0;
		virtual Iterator* operator=(const Iterator*) = 0;
		virtual Node* getNode()const = 0;
		virtual void setNode(Node*) = 0;
		virtual void goToNext() = 0;
        virtual void reset() = 0;
        virtual Object& operator*() = 0;
};

#endif
