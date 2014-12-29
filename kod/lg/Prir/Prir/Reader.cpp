#include "stdafx.h"
#include "Reader.h"
#include <dirent.h>
#include <string>
#include <map>

using namespace std;

Reader::Reader()
{
}

Reader::~Reader()
{
}

bool Reader::check_file_exists(std::string filename) {
	std::ifstream infile(filename);
	return infile.good();
}

bool Reader::check_folder_existings(std::string folderName) {
	return true;
}

bool Reader::check_type(std::string filename) {
	string file_ext = filename.substr(filename.find_last_of(".") + 1);
	if (file_ext == "txt") {
		return true;
	}
	return false;
}

map<string, string> Reader::read_files(std::string folderPath) {
	map<string, string> retval;
	ifstream inn;
	string   str;
	DIR *pDIR;
	struct dirent *entry;
	char *v;
	cout << "In 1" << endl;
	try {
		if (pDIR = opendir("test/")){
			cout << "In 2i" << endl;
			while (entry = readdir(pDIR)){
				cout << "In 2" << endl;
				if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
					cout << "In 3" << endl;
					string name = entry->d_name;
					cout << name << endl;
					inn.open(name);
					inn >> str;
					cout << str << endl;
					retval[name] = str;
					// retval.insert(name, str);
				}
				closedir(pDIR);
			}
		}
	}
	catch (...) {
		cout << "Error in read files" << endl;
	}
	
	return retval;
}