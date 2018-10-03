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

string Utils::getSqliteStrToGetRecords(string strAllRecord, const List& l, string add){
    stringstream str;
    str << strAllRecord << " " << add << " ";
    Iterator* i = l.getIterator();
    while(i->hasNext()){
        WhereCondition* wc = static_cast<WhereCondition*>(i->getCurrentValue());
        str << " " << wc->getLeft() << " " << wc->getOperator() << " " << wc->getRight();
        ++(*i);
        if(i->hasNext()){
            str << " and ";
        }
    }
    
    delete i;
    return str.str();
}
