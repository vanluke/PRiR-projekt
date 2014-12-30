#ifndef READER_H
#define READER_H

#include <iostream>
#include <string>
#include <fstream>
#include <map>

class Reader
{
public:
	Reader();
	~Reader();
	/*
		===========================================================

		usage:

			folderPath - podajesz folder np: c:\\test

		returns:

			mape z nazwa pliku jako klucz oraz zawartoscia pliku jako kontent.

		===========================================================
	*/
	std::map<std::string, std::string> read_files(std::string folderPath);

	/*
	===========================================================

	usage:

		local_map - mapa do wyswietlenia.

	returns: 
		void.

	===========================================================
	*/
	void print_map(std::map<std::string, std::string> local_map);
};

#endif

