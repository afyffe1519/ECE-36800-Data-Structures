#include "shortestpath.h"

int** Initialize(int* points, char * Filename)
{
	int index; //counter
	int i;
	int points1 = 0; //number of points
	int edges = 0; //numbers of edges
	int point_A = 0; //where the path starts
	int point_B = 0; //where the path ends
	int x = 0;
	int y = 0;
	int label = 0;
	int edge_label = 0;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	FILE * fptr = fopen(Filename, "r");
	
	
	
	fscanf(fptr, "%d %d", &points1, &edges);
	Point * arr_points = malloc(sizeof(Point) * points1);
	Edge * arr_edges = malloc(sizeof(Edge) * edges);

	for(index = 0; index < points1; index++)
	{
		fscanf(fptr, "%d %d %d\n", &label, &x, &y);
		arr_points[index].label = label;
		arr_points[index].x = x;
		arr_points[index].y = y;
		
	}

	for(index = 0; index < edges; index++)
	{
		fscanf(fptr, "%d %d\n", &point_A, &point_B);
		addPoint(arr_edges, index, point_A, point_B);
	}
	int * * PE_matrix = malloc(sizeof(int*) * points1);
	for(index = 0; index < points1; index++)
	{
		PE_matrix[index] = malloc(sizeof(int) * points1);
		for(i = 0; i < points1; i++)
		{
			PE_matrix[index][i] = 0;
		}
	}
	for(index = 0; index < edges; index++)
	{
		point_A = arr_edges[index].point_A;
		point_B = arr_edges[index].point_B;
		x1 = arr_points[point_A].x;
		y1 = arr_points[point_A].y;
		x2 = arr_points[point_B].x;
		y2 = arr_points[point_B].y;

		edge_label = addEdge(x1, y1, x2, y2);

		PE_matrix[point_A][point_B] = edge_label;
		PE_matrix[point_B][point_A] = edge_label;
	}
	*points = points1;
	free(arr_points);
	free(arr_edges);
	fclose(fptr);
	return PE_matrix;
}

Paths * LoadPaths(int* paths, char * Filename)
{
	int index;
	int paths1;
	Paths * list = malloc(sizeof(Paths) * paths1);
	int begin;
	int end;

	FILE * fptr = fopen(Filename, "r");
	fscanf(fptr, "%d\n", &paths1);
	for(index = 0; index < paths1; index++)
	{
		fscanf(fptr, "%d %d\n", &begin, &end);
		list[index].point_A = begin;
		list[index].point_B = end;
	}
	fclose(fptr);
	*paths = paths1;
	return list;
}

void addPoint(Edge * array, int i, int A, int B)
{
	array[i].point_A = A;
	array[i].point_B = B;
}

int addEdge(int x1, int y1, int x2, int y2)
{
	int index = 0;
	while(pow(index, 2) <= (pow((x1 - x2),2) + pow((y1 - y2), 2)))
	{
		index = index + 1;
	}
	return --index;	
}


void Shortest(int ** PE_matrix, int begin, int end, int points)
{
	int * len = malloc(points * sizeof(int));
	int * prev = malloc(points * sizeof(int));
	int * cur = malloc(points * sizeof(int));
	int index;
	int min;
	int index2;
	int temp;

	for(index = 0; index < points; index++)
	{
		len[index] = INT_MAX;
		prev[index] = -1;
		cur[index] = 0;
	}

	len[begin] = 0;

	for(index = 0; index < points; index++)
	{
		min = getMin(len, cur, points);
		if(min == end)
		{
			break;
		}

		cur[min] = 1;
		for(index2 = 0; index2 < points; index2++)
		{
			temp = len[min] + PE_matrix[min][index2];	
			if(cur[index2] == 0 && PE_matrix[min][index2] != 0 && temp < len[index2])
			{
				prev[index2] = min;
				len[index2] = len[min] + PE_matrix[min][index2];
			}
		}
	}

	printf("%d\n", len[end]);
	FinalPrint(prev, end);
	free(len);
	free(prev);
	free(cur);
}

int getMin(int* len, int * cur, int points)
{
	int min = INT_MAX;
	int temp = 0;
	int index;
	for(index = 0; index < points; index++)
	{
		if(len[index] <= min && cur[index] == 0)
		{
			min = len[index];
			temp = index;
		}
	}
	return temp;
}

void FinalPrint(int * prev, int end)
{
	if(prev[end] == -1)
	{
		printf("%d ", end);
		return;
	}
	FinalPrint(prev, prev[end]);
	printf("%d ", end);
}
