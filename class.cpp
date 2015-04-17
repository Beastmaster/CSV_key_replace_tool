#include "class.h"

ParseParseParse::ParseParseParse()
{

}

ParseParseParse::~ParseParseParse()
{

}


int ParseParseParse::search_Key(std::string in)
{
	//if string contains a-z or A-Z or other notations 
	int flag = 0;
	for (int i = 0 ;i<in.size();i++)
	{
		if (in[i]<='9' && in[i]>='0')
		{
			//flag = 0;
			continue;
		}
		else
		{
			//if there is character other than number
			flag = 1;
			break;
		}
	}

	//if flag==0, then the string contains numbers only and can convert to int
	if (flag == 0)
	{
		int x = std::atoi(in.c_str());
		data_container[in] = x;
		return x;
	}

	//if not contain "in", add it to data container
	if (data_container.find(in) == data_container.end())
	{
		//assign data container size to value number
		data_container[in] = data_container.size();
	}
	return data_container[in];
}

void ParseParseParse::print_Map(std::string file_name)
{
	std::ofstream out_file;
	out_file.open (file_name, std::ofstream::out | std::ofstream::app);

	if (!out_file.is_open())
	{
		std::cout<<"opening file: "<<file_name<<std::endl;
		out_file.open(file_name,std::ofstream::out || std::ofstream::app);
	}

	//print index
	int num_row = 0;
	for(auto it=data_container.begin();it != data_container.end()
		;it++)
	{
		if (num_row<data_container.size()-1)
		{
			out_file<<(*it).first<<", ";
		}
		else
		{
			out_file<<(*it).first<<".\n";
		}
		num_row++;
	}

	//print key value
	num_row = 0;
	for(auto it=data_container.begin();it != data_container.end()
		;it++)
	{

		if (num_row<data_container.size()-1)
		{
			out_file<<(*it).second<<", ";
		}
		else
		{
			out_file<<(*it).second<<".\n";
		}
		num_row++;
	}

	if (out_file.is_open())
	{
		out_file.close();
	}
}

