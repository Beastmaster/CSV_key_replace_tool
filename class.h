#ifndef __CLASS_H__
#define __CLASS_H__

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fstream>



class ParseParseParse
{
	//index: property value; value: number
	typedef std::map< std::string , int > lookup_type;
public:
	ParseParseParse();
	~ParseParseParse();

	//search string, if not contains, add the key
	int search_Key(std::string);
	//print key and value map to .txt
	void print_Map(std::string);
private:
	lookup_type data_container;
};



#endif






