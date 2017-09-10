#include "packing.h"

int main(int argc, char* argv[])
{
	Tree * root = NULL;
	int nodes = 0;
	if(argc < 3)
	{
		printf("not enough arguments\n");
		return 0;
	}
	
	root = Load_binary_tree_from_file(argv[1]);
	nodes = Number(root);
	if(root == NULL)
	{
		printf("Error in loading tree\n");
	}
	pack(root);
	create_coordinates(root);

	Save_packing_to_file(root, argv[2], nodes);


	printf("Width: %le\n", root -> width);
	printf("Height: %le\n", root -> height);

	double width = 0;
	double height = 0;
	double x = 0;
	double y = 0;
	search(root, &nodes, &width, &height, &x, &y);
	printf("X-Coordinate: %le\n", x);
	printf("Y-Coordinate: %le\n\n", y);
	free(a);
	return 0;
}
