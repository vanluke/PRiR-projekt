#ifndef SEARCH_H
#define SEARCH_H

#include <map>
#include <iostream>
#include <mpi.h>

using namespace std;

class Search{

public:
	Search();

	//metody dla wątku głównego
	void SetFileList(map<string, string> files);
	void SetPattern(string pattern);
	void SetPackSize(unsigned int packSize);
	void SetMpiStructInfo(MPI_Datatype* MPI_SearchInfo);
	void Run();

	//metody dla wątków, które będą szukały (nie głównego)
	void Wait();

private:
	void ResetProcessesInfo();
	void SendToProcess(string pattern, string text, string fileName);
	int GetFreeProcessNumber();
	void SendBreakInfo();

	map<string, string> files;
	string pattern;	
	unsigned int packSize;
	unsigned int overlapSize;

	/* Wartości do obsługi zrównoleglenia */
	MPI_Datatype* MPI_SearchInfo;

	int numOfProcesses;
	bool* freeProcess; //tablica określająca czy proces jest wolny
	int numOfFreeProcesses; //liczba określająca ile jeszcze jest wolnych procesów

};

#endif