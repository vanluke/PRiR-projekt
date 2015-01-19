// Prir.cpp : Defines the entry point for the console application.
//

#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <math.h>
#include <dirent.h>
#include <cstddef>
#include "Reader.h"
#include "Search.h"
#include "SearchInfo.h"

using namespace std;

int main(int argc, char* argv[])
{
	string pattern = "plik";
	unsigned int packSize = 10;
	if (pattern.length() > packSize)
	{ 
		packSize = pattern.length()*2; 
	}
	
	MPI_Init(&argc, &argv);
	int processId;

	MPI_Comm_rank(MPI_COMM_WORLD, &processId);

	/* deklaracja typu dla struktury */
	int blocklengths[3] = {20,100,50};
	MPI_Datatype strukturaTypy[3] = { MPI_CHAR, MPI_CHAR, MPI_CHAR };
	MPI_Datatype MPI_SearchInfo;
	MPI_Aint offsets[3];

	offsets[0] = offsetof(SearchInfo, pattern);
	offsets[1] = offsetof(SearchInfo, text);
	offsets[2] = offsetof(SearchInfo, fileName);

	MPI_Type_create_struct(3, blocklengths, offsets, strukturaTypy, &MPI_SearchInfo);
	MPI_Type_commit(&MPI_SearchInfo);

	double t1 = 0.0, t2 = 0.0;

	if(processId==0){
		Reader reader;
		map<string, string> retval;

		try {
			retval = reader.read_files("./pliki");
		}
		catch (...) {
			cout << "Error" << endl;
		}

		Search search;
		search.SetMpiStructInfo(&MPI_SearchInfo);
		search.SetPattern(pattern);
		search.SetPackSize(packSize);
		search.SetFileList(retval);
		t1 = MPI_Wtime();
		search.Run();
		t2 = MPI_Wtime();
		cout << "Czas: " << fabs(t2 - t1) * 1000 << "[ms]" << endl;
	}
	else{
		//pozostałe procesy - nie główny
		Search search;
		search.SetMpiStructInfo(&MPI_SearchInfo);
		search.Wait();
	}

	MPI_Finalize();
	
//	reader.print_map(retval);


/*	cout << retval["1.txt"] << endl;

	string txt = "GEEKS two FOR GEEKS";

	string pat = "two";

	KarpRabin karp;
	int q = 101;
	int alfabeath = 256;
	int value = karp.karp_rabin(pat, txt, q, alfabeath);

	cout << "Found at : " << value << endl;
*/
	return 0;
}


