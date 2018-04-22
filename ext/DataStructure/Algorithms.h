#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "List.h"

class Algorithms{
	
	public:
		static const int ASC=0;
		static const int DESC=1;
        
        static const int NULL_POINT=0;
        static const int INVALID_MODE=1;
		
		void insertionSort(List*, int mode = Algorithms::ASC);
        bool isSorted(List*, int mode = Algorithms::ASC);
        void mergeSort(List*, int mode = Algorithms::ASC);

};

#endif
