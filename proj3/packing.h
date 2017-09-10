#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tree{
	int label;
	char slice;
	double width;
	double height;
	double x;
	double y;
	struct Tree *left;
	struct Tree *right;
}Tree;

typedef struct _lnode {
	Tree * tree;
	struct _lnode *next;
}lnode;

Tree * a;
FILE * Open(char * filename, char * mode);
Tree * Load_binary_tree_from_file(char *Filename);
lnode * push(lnode * stack, Tree * tree);
Tree * pop(lnode ** stack);
void Save_packing_to_file(Tree * root, char * Filename, long nodes);
void inorder_print(Tree * root, FILE * fp);
int Number(Tree * root);
void search(Tree * root, int * number, double * width, double * height, double * x, double * y);
double MaxHeight(Tree * root);
double MaxWidth(Tree * root);
void pack(Tree * root);
void create_coordinates(Tree * root);
void removeNode(lnode* to_delete, lnode* node);
