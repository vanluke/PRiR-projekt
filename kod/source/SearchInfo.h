#ifndef SEARCHINFO_H
#define SEARCHINFO_H

#include<string>

using namespace std;

typedef struct SearchInfo_s{
	char pattern[20];
	char text[100];
	char fileName[50];
} SearchInfo;

#endif