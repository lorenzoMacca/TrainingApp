#ifndef UTILS_H 
#define UTILS_H

#include <vector>
#include <iostream>
using namespace std;
#include <string>

class Utils{
	public:
		static vector<string>* split(string str, char delim);
};

#endif