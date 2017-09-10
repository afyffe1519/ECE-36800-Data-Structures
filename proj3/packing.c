#include "packing.h"
#include <stdio.h>

FILE * Open(char * filename, char * mode)
{
	FILE * ptr = NULL;
	ptr = fopen(filename, mode); //opens the file
	if(ptr == NULL)
	{
		printf("Can't open file\n");
		return NULL;
	}
	return ptr;
}

Tree * Load_binary_tree_from_file(char * Filename)
{
	Tree * root = NULL;
	FILE * ptr = NULL;
	int counter = 0;
	a = NULL;
	if((ptr = Open(Filename, "r")) == NULL)
	{
		return NULL;
	}
	char ch;
	while(!feof(ptr))
	{
		ch = fgetc(ptr);
		if(ch == '\n')
		{
		     counter++; //counts the number of tree nodes in the input
		}
	}
	if(fseek(ptr, 0, SEEK_SET) != 0) //puts the file back at the beginning
	{
		fprintf(stderr, "fseek failed\n");
		return NULL;
	}
        a = malloc(sizeof(Tree) * counter); //mallocs enough space for the tree
	
	for(int i = 0; i < counter; i++) //initializes and reads in everything
	{
		a[i].left = NULL;
		a[i].right = NULL;
		a[i].x = 0;
		a[i].y = 0;
		fscanf(ptr, "%c", &(a[i].slice));
		if(((a[i].slice) == 'H') || ((a[i].slice) == 'V')) //if a non-leaf node
		{
			fscanf(ptr, "\n");
			a[i].width = 0;
			a[i].height = 0;
			a[i].label = 0;
		}
		else
		{
			fseek(ptr, -(sizeof(char)), SEEK_CUR); //finds the correct place to start in the line
			fscanf(ptr, "%d", &(a[i].label));
			fscanf(ptr, "(%le,", &(a[i].width));
			fscanf(ptr, "%le)\n", &(a[i].height));
		}
	}
	lnode * node = NULL; //points to the stack
	root = a; //reassigns root
	root -> left = NULL;
	root -> right = NULL;
	node = push(node, root); //builds the stack
	for(int j = 1; j < counter; j++) //builds the tree
	{
		root = a + j;
		if((a[j].slice) == 'H' || (a[j].slice) == 'V')
		{
			root -> right = pop(&node);
			root -> left = pop(&node);
		}
		else
		{
			root -> right = NULL;
			root -> left = NULL;
		}
		node = push(node, root); //pushs the next number onto the stack
	}
	lnode * to_delete = node; 
	removeNode(to_delete, node); //frees the stack pointer
	fclose(ptr);		

	return root;
}

lnode * push(lnode * stack, Tree * tree)
{
	lnode * new = malloc(sizeof(lnode)); //makes space in the stack
	new -> tree = tree;
	new -> next = stack;
	return new;
}

Tree * pop(lnode ** stack)
{
	lnode * returned_node = *stack; //builds the tree from bottom up
	*stack = returned_node -> next;
	Tree * tree = returned_node -> tree;
	free(returned_node);
	return tree;
}

void Save_packing_to_file(Tree * root, char * Filename, long nodes)
{
	FILE * ptr = NULL;

	if((ptr = Open(Filename, "w")) == NULL)
	{
		return;
	}
	inorder_print(root, ptr); //prints the results into a file
	fclose(ptr);
}

void inorder_print(Tree * root, FILE * fp)
{
	int number = 0;
	double w = 0;
	double h = 0;
	double x = 0;
	double y = 0;
	if(root != NULL)
	{
		inorder_print(root -> left, fp); 
		number = root -> label;
		search(root, &number, &w, &h, &x, &y); //finds width, height and x and y coordinates for each node
		if(root -> label != 0)
		{
			fprintf(fp, "%d %le %le %le %le\n", number, w, h, x, y);
		}
		inorder_print(root -> right, fp);
	}
}

int Number(Tree * root)
{
	if(root == NULL)
	{
		return 0;
	}
	if(root -> left == NULL && root -> right == NULL)
	{
		return 1;
	}
	else
	{
		return Number(root -> left) + Number(root -> right); //finds the largest label of the nodes
	}

	return 0;
}

void search(Tree * root, int * number, double * width, double * height, double * x, double * y)
{
  int num = 0;
	if(root != NULL)
	{
		search(root -> left, number, width, height, x, y);
		num = *number;
		if(root -> label == num) //resets the width, height, and coordinates for each leaf node
		{
			*width = root -> width;
			*height = root -> height;
			*x = root -> x;
			*y = root -> y;
		}

		search(root -> right, number, width, height, x,y);
	}
}

void create_coordinates(Tree * root)
{
	//finds the x and y coordinates based of the type of cuts and height/width of each box
	if(root == NULL)
	{
		return;
	}

	if(root -> slice == 'H')
	{
		root -> left -> x = root -> x; 
		root -> left -> y = root -> y + root -> right -> height;
		root -> right -> x = root -> x;
		root -> right -> y = root -> y;
	}
	else if(root -> slice == 'V')
	{
		root -> left -> x = root -> x;
		root -> left -> y = root -> y;
		root -> right -> x = root -> x + root -> left -> width;
		root -> right -> y = root -> y;
	}
	create_coordinates(root -> left);
	create_coordinates(root -> right);
	
	
	return;
}

void pack(Tree * root)
{
	//packs all of the boxes based on the cuts.
	if(root -> left == NULL)
	{
		return;
	}

	if(root -> left -> height == 0.0)
	{
		pack(root -> left);
	}
	if(root -> right -> height == 0.0)
	{
		pack(root -> right);
	}

	if(root -> slice == 'H')
	{
		root -> height = root -> left -> height + root -> right -> height;
		root -> width = MaxWidth(root);
	}
	else if(root -> slice == 'V')
	{
		root -> height = MaxHeight(root);
		root -> width = root -> left -> width + root -> right -> width;
	}

	return;
}

double MaxHeight(Tree * root)
{
	double dtemp = root -> left -> height;
	double dtemp2 = root -> right -> height;
	
	if(dtemp >= dtemp2)
	{
		return dtemp;
	}
	else
	{
		return dtemp2;
	}
	return 0;
}

double MaxWidth(Tree * root)
{
	double dtemp = root -> left -> width;
	double dtemp2 = root -> right -> width;

	if(dtemp >= dtemp2)
	{
		return dtemp;
	}
	else
	{
		return dtemp2;
	}
}

void removeNode(lnode * to_delete, lnode * node)
{
	while(to_delete != NULL)
	{
		node = node -> next;
		free(to_delete);
		to_delete = node;
	}
}
