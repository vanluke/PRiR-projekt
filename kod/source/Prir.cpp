// Prir.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <dirent.h>
#include "Reader.h"
#include "KarpRabin.h"

using namespace std;

int main(int argc, char* argv[])
{
	Reader reader;
	
	map<string, string> retval;

	KarpRabin karp;

	try {
		retval = reader.read_files(".");
	}
	catch (...) {
		cout << "Error" << endl;
	}

	// reader.print_map(retval);

	string txt = "GEEKS FOR GEEKS";

	string pat = "two";

	int q = 101;

	int alfabeath = 256;

	int value = karp.karp_rabin(pat, retval["one.txt"], q, alfabeath);

	cout << "Found at : " << value << endl;

	return 0;
}


