#ifndef SEARCHINFO_H
#define SEARCHINFO_H

#include "config.h"
#include <string>

using namespace std;

typedef struct SearchInfo_s{
	char pattern[DLUGOSC_FRAZY];
	char text[ROZMIAR_BLOKU];
	char fileName[50];
} SearchInfo;

#endif