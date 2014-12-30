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

map<string, string> Reader::read_files(std::string folderPath) {
	map<string, string> retval;

	ifstream fin;
	
	string filepath;
	
	string content;
	
	DIR *dp;
	
	struct dirent *dirp;
	
	struct stat filestat;

	dp = opendir(folderPath.c_str());

	while ((dirp = readdir(dp)))
	{
		filepath = folderPath + "/" + dirp->d_name;

		if (stat(filepath.c_str(), &filestat)) {
			continue;
		}
		if (S_ISDIR(filestat.st_mode)) {
			continue;
		}

		fin.open(filepath.c_str());

		if (fin >> content) {
			cout << filepath << ": " << content << endl;
			retval[dirp->d_name] = content;
		}
			
		fin.close();
	}

	closedir(dp);
	
	return retval;
}

void Reader::print_map(map<string, string> local_map) {
	for (map<string, string>::iterator outer_iter = local_map.begin(); outer_iter != local_map.end(); ++outer_iter) {
		cout << "File name: " << outer_iter->first << " content " << outer_iter->second << std::endl;
	}
}
