#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorting.h"

int main(int argc, char * * argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "too few arguments");
		return 0;
	}

	Node * head = NULL;
	
	clock_t startClockIO, stopClockIO, startClockSort, stopClockSort;

	startClockIO = clock();
	head = Load_From_File(argv[1]);

	startClockSort = clock();
	head = Shell_Sort(head);
	stopClockSort = clock();
	Save_To_File(argv[2], head);
	stopClockIO = clock();

	printf("I/O time: %f\n", (float) ((stopClockIO - startClockIO) - (stopClockSort - startClockSort))/CLOCKS_PER_SEC);
	printf("Sorting time: %f\n", (float) (stopClockSort - startClockSort)/CLOCKS_PER_SEC);

	return 1;
}
