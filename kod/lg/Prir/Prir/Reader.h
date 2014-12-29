#ifndef READER_H
#define READER_H

#include <iostream>
#include <string>
#include <fstream>
#include <map>

class Reader
{
private: 
	std::fstream file_stream;
	bool check_folder_existings(std::string folderPath);
	bool check_type(std::string filename);
	bool check_file_exists(std::string filename);
public:
	Reader();
	~Reader();
	std::map<std::string, std::string> read_files(std::string folderPath);
};

#endif

