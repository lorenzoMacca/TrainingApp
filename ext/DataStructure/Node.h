#ifndef NODE_H
#define NODE_H

#include "Object.h"

class Node : public Object{

	protected:
		Object* m_value;
		Node* m_previous_element;
		Node* m_next_element;

	public:
		Node();
		Node(Object*);
		virtual ~Node();
		Node(const Node& n);
		Object* getValue()const;
		void setValue(Object*);
		Node* getNext()const;
		Node* getPrevious()const;
		bool setNext(Node*);
		bool setPrevious(Node*);
    
        //from Object
        string toString() const;
        int compareTo(Object*) const;
};

#endif
