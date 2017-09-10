#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorting.h"


int main(int argc, char * * argv)
{
	if(argc < 5)
	{
		printf("Too few arguments");
		return 0;
	}
	int Size;
	int Seq_Size;
	long * Array = NULL;
	double N_Comp = 0;
	double N_Move = 0;
	clock_t startClockIO, stopClockIO, startClockSort, stopClockSort;

	startClockIO = clock();
	Array = Load_From_File(argv[2], &Size);

	startClockSort = clock();

	if(strcmp(argv[1], "s"))
	{
		printf("Numbers of long integers read: %d\n", Size);
		Shell_Insertion_Sort(Array, Size, &N_Comp, &N_Move);
	}
	if(strcmp(argv[1], "i"))
	{
		printf("Number of long integers read: %d\n", Size);
		Shell_Selection_Sort(Array, Size, &N_Comp, &N_Move);
	}
	stopClockSort = clock();

	Seq_Size = Print_Seq(argv[3], Size);
	Save_To_File(argv[4], Array, Size);
	stopClockIO = clock();
	
	printf("Number of long integers stored: %d\n", Size);
	printf("Length of sequence: %d\n", Seq_Size);
	printf("Number of comparisons: %lf\n", N_Comp);
	printf("Number of moves: %lf\n", N_Move);
	printf("I/O time: %f\n", (float)((stopClockIO - startClockIO) - (stopClockSort - startClockSort))/CLOCKS_PER_SEC);
	printf("Sorting time: %f\n", (float)(stopClockSort - startClockSort)/CLOCKS_PER_SEC);

	return 1;
}
