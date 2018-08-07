#include "Utils.h"

std::vector<string>* Utils::split(string str, char delim){
	std::vector<string> *vector=new std::vector<string>;
	string tmp="";
	for(unsigned i=0; i<str.length(); ++i){
		if(str.at(i) == delim){
			if(tmp.size() > 0){
				vector->push_back(tmp);
				tmp="";
			}
		}else{
			tmp += str.at(i);
		}
	}
	vector->push_back(tmp);
	return vector;
}

/*
 * -
 * 
 * a--
 * 
 * */