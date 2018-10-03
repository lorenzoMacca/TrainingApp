#ifndef UTILS_H 
#define UTILS_H

#include <vector>
#include <iostream>
using namespace std;
#include <string>
#include <List.h>
#include <WhereCondition.h>

class Utils{
	public:
		static vector<string>* split(string str, char delim);
        static string getSqliteStrToGetRecords(string strAllRecord, const List&, string add );
};

#endif
