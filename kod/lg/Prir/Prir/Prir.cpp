// Prir.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include "Reader.h"



using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Reader reader;
	try {
		reader.read_files("c:\\test");
	}
	catch (...) {
		cout << "Error" << endl;
	}
	

	system("pause");
	return 0;
}

