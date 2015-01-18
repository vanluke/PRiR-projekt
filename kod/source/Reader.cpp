
#include "Reader.h"
#include <dirent.h>
#include <string>
#include <map>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


using namespace std;

Reader::Reader()
{
}

Reader::~Reader()
{
}

map<string, string> Reader::read_files(std::string folderPath) {
	map<string, string> retval;

	string filepath;
	
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

		retval[dirp->d_name] = filepath.c_str();		
	}

	closedir(dp);
	
	return retval;
}

/*string Reader::get_content(string filePath){
	ifstream fin;

	fin.open(filePath);

	fin.close();
}*/

void Reader::print_map(map<string, string> local_map) {
	for (map<string, string>::iterator outer_iter = local_map.begin(); outer_iter != local_map.end(); ++outer_iter) {
		cout << "File name: " << outer_iter->first << " content " << outer_iter->second << std::endl;
	}
}
