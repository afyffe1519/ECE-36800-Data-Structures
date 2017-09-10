#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define NUM_OF_POINTS 100000
#define MAX_X_Y INT_MAX


typedef struct Edge
{
	int point_A; //the start location
	int point_B; //the end location
	//int distance;
} Edge;

typedef struct Point
{
	int x; //coordinates of the point
	int y;
	int label; //head of the point
} Point;

typedef struct Paths
{
	int point_A;
	int point_B;
} Paths;

int** Initialize(int * points, char * Filename);
Paths* LoadPaths(int* paths, char * Filename);
void addPoint(Edge * array, int i, int A, int B);
int addEdge(int x1, int y1, int x2, int y2);
void Shortest(int ** PE_matrix, int begin, int end, int points);
int getMin(int * len, int * cur, int points);
void FinalPrint(int * prev, int end);
