#pragma once

#include<string>
#include<fstream>

namespace bear { namespace core { 

static std::string get_file_content(std::string a_Path) 
{
	std::ifstream file(a_Path);
	return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

}} 