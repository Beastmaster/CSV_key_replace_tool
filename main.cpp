#include "class.h"
#include <iostream>
#include <fstream>
#include <string>

//output: number of row (properties)
//input:  file name
//function: read the first line of the file and find format
int find_num_Row(std::string file_name);


//ouput: a vector of components
//input: 1. source string; 2. split string
//function: split a string by input string
std::vector<std::string> split_String(std::string input_str,std::string split_str);

//output: float point position
//input:  file name
//function: read the first line of the file and find format
std::vector<int> find_float_pos(std::string file_name);

int main(int argc,char** argv)
{

	std::string file_name = "D:\\WorkPlace\\CSV_Parse\\census-income.data.CSV";
	std::string out_file_name;// = "D:\\WorkPlace\\CSV_Parse\\census-income_test_out.CSV";
	std::string out_map_file_name;// = "D:\\WorkPlace\\CSV_Parse\\census-income_map_out.CSV";

	out_file_name = file_name;
	out_file_name = out_file_name.insert(file_name.find(".CSV"),"-out");
	out_map_file_name = file_name;
	out_map_file_name = out_map_file_name.insert(file_name.find(".CSV"),"-map");

	int num_row = 0;
	//find number of row (properties) here
	num_row = find_num_Row(file_name);
	
	std::vector<int> float_pos_vector;
	float_pos_vector = find_float_pos(file_name);


	if (num_row == 0)
	{
		std::cout<<"error:number of row is 0...."<<std::endl;
		return 0;
	}

	//init a vector to hold all map, initial number of row is assigned
	std::vector< ParseParseParse* > csv_parse_handle;
	for (int cnt = 0;cnt < num_row;cnt++)
	{
		ParseParseParse* temp_parse = new ParseParseParse;
		csv_parse_handle.push_back(temp_parse);
		std::cout<<cnt<<"th pair-map created"<<std::endl;
	}

	//create a output file and add content into it
	std::ofstream out_file(out_file_name);  
	if (!out_file.is_open())
	{
		std::cout<<"opening file: "<<out_file_name<<std::endl;
		out_file.open(out_file_name,std::ofstream::out);
	}

	//get in line and split them by ","
	std::ifstream ifs;
	ifs.open (file_name, std::ifstream::in);
	if (!ifs)
	{
		std::cout<<"file does not exist"<<std::endl;
		return 0;
	}
	else
	{//file exist, read line in the file
		std::string temp_line;
		int cnt_row=0;
		while (std::getline(ifs,temp_line,'\n'))
		{
			//skip the line that loss information (contains ", ?")
			if (temp_line.find(", ?") != std::string::npos)
			{
				continue;
			}

			//split line by ", "
			auto temp_line_vector = split_String(temp_line,", ");

			//check size of vector match with number of row
			if (temp_line_vector.size() != num_row)
			{
				std::cout<<"this line is not reasonable..."<<std::endl;
				continue;
			}

			//iterate through the temp_line_vector to put component to map
			for (int i=0;i<num_row;i++)
			{
				//print float number
				for (int cnt=0;cnt<float_pos_vector.size();cnt++)
				{
					//get the pos that hold the float number
					if (float_pos_vector[cnt] == i)
					{
						if (float_pos_vector[cnt]<num_row-1)
						{
							out_file<<temp_line_vector[i]<<", ";
						}
						else
						{
							out_file<<temp_line_vector[i]<<".\n";
						}
					}
					continue;
				}

				//print in ordinary way
				int row_temp = csv_parse_handle[i]->search_Key(temp_line_vector[i]);
				if (i<num_row-1)
				{
					out_file<<row_temp<<", ";
				}
				else
				{
					out_file<<row_temp<<".\n";
				}
			}
			std::cout<<cnt_row++<<"th line done"<<std::endl;
		}
	}
	//close intpu file
	if (ifs.is_open())
	{
		ifs.close();
	}
	//close output file
	if (out_file.is_open())
	{
		out_file.close();
	}

	//iterate through the vector to release memory
	for (auto it = csv_parse_handle.begin();
		 it!=csv_parse_handle.end();it++)
	{
		(*it)->print_Map(out_map_file_name);
		delete (*it);
	}
	return 0 ;
}

int find_num_Row(std::string file_name)
{
	std::string first_line;
	std::ifstream fs;
	fs.open (file_name, std::ifstream::in);
	if (!fs)
	{
		std::cout<<"file does not exist"<<std::endl;
		return 0;
	}
	else
	{//file exist, read the first line in the file
		std::getline(fs,first_line,'\n');
	}

	if (fs.is_open())
	{
		fs.close();
	}

	//iterate through string to find number of ','
	int cnt=0;
	for(std::string::iterator it = first_line.begin();
		it!=first_line.end();it++)
	{
		if ((*it)==',')
		{
			cnt++;
		}
	}

	return ++cnt;
}

std::vector<int> find_float_pos(std::string file_name)
{
	std::vector< int > return_vector;

	std::string first_line;
	std::ifstream fs;
	fs.open (file_name, std::ifstream::in);
	if (!fs)
	{
		std::cout<<"file does not exist"<<std::endl;
		return return_vector;
	}
	else
	{//file exist, read the first line in the file
		std::getline(fs,first_line,'\n');
	}

	if (fs.is_open())
	{
		fs.close();
	}

	auto str_vector = split_String(first_line,", ");


	//iterate through string to find number of ','
	int pos = 0;
	for(auto it = str_vector.begin();
		it!=str_vector.end();
		it++)
	{
		int flag = 0;
		if ((*it).find(".") != std::string::npos)
		//if . can be found in the string, find character
		{
			for (int i = 0 ;i<(*it).size();i++)
			{
				//can only find number here
				if ((*it)[i]<='9' && (*it)[i]>='0')
				{
					//flag = 0;
					continue;
				}
				else
				{
					flag = 1;
					break;
				}
			}
		}
		if (flag == 1)
		{
			return_vector.push_back(pos);
		}
		pos++;
	}

	return return_vector;
}



std::vector<std::string> split_String(std::string input_str,std::string split_str)
{
	std::vector<std::string> return_vector;

	while(input_str.find(split_str)!=std::string::npos)
	{
		//find first sub_str split by split_str
		std::size_t pos_first = input_str.find(split_str);
		return_vector.push_back(input_str.substr(0,pos_first));

		//find sub_str in the middle of string
		input_str = input_str.substr(pos_first+split_str.size());//skip ", ": (split str size)
	}

	//if there is no split_str
	if (input_str.find(split_str) == std::string::npos)
	{
		//eliminate the "." at the end of line
		std::size_t dot_pos = input_str.find(".");
		if (dot_pos!=std::string::npos)
		{
			input_str = input_str.substr(0,dot_pos);
		}

		return_vector.push_back(input_str);
	}
	return return_vector;
}









