#include "shortestpath.h"

int main(int argc, char * argv[])
{
	if(argc != 3)
	{
		printf("NOT ENOUGH ARGUMENTS");
		return 0;
	}
	
	int points = 0;
	int paths = 0;
	int index;
	int ** PE_matrix;
	
	PE_matrix = Initialize(&points, argv[1]);
	Paths* path = LoadPaths(&paths, argv[2]);

	for(index = 0; index < paths; index++)
	{
		if((path[index]).point_A >= points || (path[index]).point_B >= points)
		{
			printf("INF\n%d %d\n", (path[index]).point_A, (path[index]).point_B);
			break;
		}
		Shortest(PE_matrix, (path[index]).point_A, (path[index]).point_B, points);
		printf("\n");
	}
	free(path);
	for(index = 0; index < points; index++)
	{
		free(PE_matrix[index]);
	}
	free(PE_matrix);
	return 1;
}

