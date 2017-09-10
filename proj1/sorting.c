#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"

int *Make_Seq(int Size);

long *Load_From_File(char *Filename, int *Size)
{
	FILE *file;
	long * Array = NULL;
	long size = 0;
	
	file = fopen(Filename, "rb");
	if(!file)
	{
		fprintf(stderr, "Can't open file\n");
		return NULL;
	}
	fseek(file, 0L, SEEK_END);
	long position = ftell(file);
	size = position / sizeof(long);
	fseek(file, 0L, SEEK_SET);	
    *Size = size;		
	
	Array = (long*) malloc(sizeof(long) * size);
	fread(Array, sizeof(long), size, file);
	if(!Array)
	{
		fprintf(stderr, "Memory Error!");
		fclose(file);
		return 0;
	}
	
	fclose(file);
	return Array;
}

int Save_To_File(char *Filename, long *Array, int Size)
{
	FILE * file;
	file = fopen(Filename, "wb");
	
	fwrite(Array, sizeof(long), Size, file);

	fclose(file);
	
	free(Array);
	return 0;
}


void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
	int max3 = 1;
	int max2 = 1;
	int numLevel3 = 0;
	int numLevel2 = 0;
	int Level = 0;
	int temp = 0;
	int temp_elem = 0;
	int temp_max = max2;
	int i = 0;
	int j = 0;
	int * Seq = NULL;
	int value;
	int temp_sort;
	int holder;

	*N_Comp = 0;
	*N_Move = 0;

	Seq = Make_Seq(Size);

	while(max3 <= Size)
	{
		max3 *= 3;
		numLevel3++;
	}
	
	while(max2 <= Size)
	{
		max2 *= 2;
		numLevel2++;
	}
	
	for(temp = numLevel3; temp > 0; temp--)
	{
		temp_elem += temp;
	}
	
	Level = numLevel2;
	
	while(numLevel2 > numLevel3)
	{
		max2 /= 2;
		numLevel2--;
	}
	
	while(numLevel3 < Level)
	{
		temp_max = max2;
		while(temp_max < Size)
		{
			temp_max /= 2;
			temp_max *= 3;
			temp_elem++;
		}
		
		numLevel3++;
		max2 *= 2;
	}

	for(i = temp_elem - 1; i >= 0; i--)
	{
		value = Seq[i];
		value = (value - 1)/2;

		for(j = value; j < Size; j++)
		{
			temp_sort = Array[j];
			*N_Move = *N_Move + 1;
			holder = j;
			while((holder >= value) && (Array[holder - value] > temp_sort))
			{
				Array[holder] = Array[holder - value];
				holder -= value;
				*N_Comp = *N_Comp + 1;
				*N_Move = *N_Move + 1;
			}
			Array[holder] = temp;
			*N_Move = *N_Move + 1;
		}
	}
	free(Seq);
}

void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
	int i;
	int j;
	int k;
	int value;
	int holder;
	int temp = 0;
	int max3 = 1;
	int max2 = 1;
	int temp_max = max2;
	int numLevel3 = 0;
	int numLevel2 = 0;
	int temp_elem = 0;
	int Level = 0;
	int *Seq = NULL;

	*N_Comp = 0;
	*N_Move = 0;
	
	Seq = Make_Seq(Size);
	
	while(max3 <= Size)
	{
		max3 *= 3;
		numLevel3++;
	}
	
	while(max2 <= Size)
	{
		max2 *= 2;
		numLevel2++;
	}
	
	for(temp = numLevel3; temp > 0; temp--)
	{
		temp_elem += temp;
	}
	
	Level = numLevel2;
	
	while(numLevel2 > numLevel3)
	{
		max2 /= 2;
		numLevel2--;
	}
	
	while(numLevel3 < Level)
	{
		temp_max = max2;
		while(temp_max < Size)
		{
			temp_max /= 2;
			temp_max *= 3;
			temp_elem++;
		}
		
		numLevel3++;
		max2 *= 2;
	}

	for(i = temp_elem - 1; i >= 0; i--)
	{
		value = Seq[i];
		value = (value - 1) / 2;
		for(j = value; j < Size; j++)
		{
			holder = j;
			for(k = j; k < Size; k++)
			{
				if(Array[k] < Array[holder])
				{
					*N_Comp = *N_Comp + 1;
					 holder = k;
				}
			}
				
			temp = Array[j];
			Array[j] = Array[holder];
			Array[holder] = temp;
			*N_Move = *N_Move + 3;
		}
	}

	free(Seq);
}

int *Make_Seq(int Size)
{
	int *Seq = NULL;
	int max3 = 1;
	int numLevel3 = 0;
	int numLevel2 = 0;
	int Level = 0;
	int max2 = 1;
	int temp_max = max2;
	int temp = 0;
	int temp_elem = 0;
	int startLevel = 1;
	int value = 1;
	int i = 1;
	int j = 1;
	int p = 0;
	int q = 0;
	int index = 1;

	while(max3 <= Size)
	{
		max3 *= 3;
		numLevel3++;
	}
	
	while(max2 <= Size)
	{
		max2 *= 2;
		numLevel2++;
	}
	
	for(temp = numLevel3; temp > 0; temp--)
	{
		temp_elem += temp;
	}
	
	Level = numLevel2;
	
	while(numLevel2 > numLevel3)
	{
		max2 /= 2;
		numLevel2--;
	}
	
	while(numLevel3 < Level)
	{
		temp_max = max2;
		while(temp_max < Size)
		{
			temp_max /= 2;
			temp_max *= 3;
			temp_elem++;
		}
		
		numLevel3++;
		max2 *= 2;
	}
	
	Seq = (int *) malloc((temp_elem + 1) * sizeof(int));
	Seq[0] = 1;
	temp_elem--;
	
	while(startLevel < Level && temp_elem > 0)
	{
		p = startLevel;
		q = 0;

		while(q <= startLevel && temp_elem > 0)
		{
			i = 1;
			j = 1;
			
			if(p == 0)
			{
				i = 1;
			}
			else
			{
				for(int count = 0; count < p; count++)
				{
					i *= 2;
				}
			}

			if(q == 0)
			{
				j = 1;
			}
			else
			{
				for(int count = 0; count < q; count++)
				{
					j *= 3;
				}
			}
			value = i * j;
			if(value <= Size)
			{
				Seq[index] = value;
				temp_elem--;
				index++;
			}
			p -= 1;
			q += 1;
		}
		
		startLevel++;
	}

	return Seq;
}


int Print_Seq(char *Filename, int Size)
{	
	FILE * fileOut;
	int * Seq = NULL;
	int i = 0;
	int max3 = 1;
	int max2 = 1;
	int temp = 0;
	int temp_max = max2;
	int temp_elem = 0;
	int numLevel3 = 0;
	int numLevel2 = 0;
	int Level = 0;
	
	while(max3 <= Size)
	{
		max3 *= 3;
		numLevel3++;
	}
	
	while(max2 <= Size)
	{
		max2 *= 2;
		numLevel2++;
	}
	
	for(temp = numLevel3; temp > 0; temp--)
	{
		temp_elem += temp;
	}
	
	Level = numLevel2;
	
	while(numLevel2 > numLevel3)
	{
		max2 /= 2;
		numLevel2--;
	}
	
	while(numLevel3 < Level)
	{
		temp_max = max2;
		while(temp_max < Size)
		{
			temp_max /= 2;
			temp_max *= 3;
			temp_elem++;
		}
		
		numLevel3++;
		max2 *= 2;
	}

	fileOut = fopen(Filename, "w");
	Seq = Make_Seq(Size);
	for(i = 0; i < temp_elem; i++)
	{
		fprintf(fileOut, "%d\n", Seq[i]);
	}
	free(Seq);
	fclose(fileOut);
	return(temp_elem);
}

