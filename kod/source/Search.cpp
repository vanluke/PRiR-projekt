#include "Search.h"
#include <mpi.h>
#include <map>
#include <fstream>
#include <string>
#include <string.h>
#include <iostream>
#include "SearchInfo.h"
#include "KarpRabin.h"

using namespace std;


Search::Search(){
	MPI_Comm_size(MPI_COMM_WORLD, &numOfProcesses);
}

//metoda ustawia szukaną frazę
void Search::SetPattern(string pattern){
	this->pattern = pattern;
	overlapSize = pattern.length()-1;
}

void Search::SetPackSize(unsigned int packSize){
	this->packSize = packSize;
}

void Search::SetFileList(map<string, string> files){
	this->files = files;
}

void Search::Run(){

	ResetProcessesInfo();

	for (map<string, string>::iterator it = files.begin(); it != files.end(); ++it)
	{
		//otwieramy plik
		ifstream file(it->second.c_str());

		char pack[packSize+1];
		char packTemp[packSize-overlapSize+1];

		//wczytujemy pierwszą paczkę
		file.get(pack, packSize+1);
		//kolejne paczki

		SendToProcess(pattern, pack, it->second);

		while(file.get(packTemp, packSize-overlapSize+1)){
			for(unsigned int i=0; i<overlapSize; i++){
				pack[i] = pack[packSize-overlapSize+i];
			}

			for(unsigned int i=overlapSize; i<packSize; i++){
				pack[i] = packTemp[i-overlapSize];
			}
			SendToProcess(pattern, pack, it->second);
		}
	}
	
	SendBreakInfo();
}

//Metoda resetuje informacje o procesach (np. o zajętości)
void Search::ResetProcessesInfo(){
	bool freeP[numOfProcesses];
	freeProcess = freeP;
	freeProcess[0] = false; //proces główny oznaczamy jako zajęty
	for(int i=0; i<numOfProcesses; i++){
		freeProcess[i] = true;
	}
	numOfFreeProcesses = numOfProcesses-1;
}


void Search::SendToProcess(string pattern, string text, string fileName){
	SearchInfo sInfo;
	
	strcpy(sInfo.pattern, pattern.c_str());
	strcpy(sInfo.text, text.c_str());
	strcpy(sInfo.fileName, fileName.c_str());

	int processNumber = GetFreeProcessNumber();
	freeProcess[processNumber] = false;
	numOfFreeProcesses--;

	cout << "wysylamy fragment: " << sInfo.text << ", " << sInfo.fileName;
	
	MPI_Send(&sInfo, 1, *MPI_SearchInfo, processNumber, 0, MPI_COMM_WORLD);

	cout << "Pozostało wolnych procesów: " << numOfFreeProcesses << endl;
	
	//jesli nie ma juz wiecej wolnych procesoo w tym miejscu czekamy na wolny, do ktorego mozemy wyslac
	if(numOfFreeProcesses==0){
		MPI_Recv(&processNumber, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		
		cout << "Proces główny dostał informację o zwolnieniu procesu" << processNumber << endl;
		
		freeProcess[processNumber] = true;
		numOfFreeProcesses++;
	}
}

//metoda przechodzi po tablicy i sprawdza który proces nic nie robi
int Search::GetFreeProcessNumber(){
	for(int i=1; i<numOfProcesses; i++){ //od 1 bo 0 to proces główny, który zawsze jest zajęty;
		if(freeProcess[i]){
			return i;
		}
	}
	return 0;
}

void Search::SendBreakInfo(){
	for(int i=1; i<numOfProcesses; i++){
		SearchInfo sInfo;
		sInfo.pattern[0] = 0;
		
		MPI_Send(&sInfo, 1, *MPI_SearchInfo, i, 0, MPI_COMM_WORLD);
	}
}

void Search::SetMpiStructInfo(MPI_Datatype* MPI_SearchInfo){
	this->MPI_SearchInfo = MPI_SearchInfo;
}

//Metoda dla procesów innych niż główny - czeka na dane i wykonuje na nich wyszukiwanie
void Search::Wait(){
	SearchInfo sInfo;

	int processNumber;
	MPI_Comm_rank(MPI_COMM_WORLD, &processNumber);
	while(true){
		MPI_Recv(&sInfo, 1, *MPI_SearchInfo, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		
		if(sInfo.pattern[0] == 0){
			cout << "Proces " << processNumber << "konczy działanie" << endl;
			break;
		}
		
		cout << "Proces " << processNumber << "przetwarza fragment" << sInfo.text << endl;

		KarpRabin karp;
		int q = 101;
		int alfabeath = 256;
		int value = karp.karp_rabin(sInfo.pattern, sInfo.text, q, alfabeath);
		
		cout << "wyniki znajdowania " << value << endl;
		
		MPI_Send(&processNumber, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
}