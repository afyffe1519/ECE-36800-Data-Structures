#include <stdio.h>
#include <stdlib.h>

typedef struct _tnode {
	int value;
	struct _tnode *left;
	struct _tnode *right;
}tnode;

tnode* mergeTrees(tnode* t1, tnode* t2);
void inorder(tnode* root);


tnode* mergeTrees(tnode* t1, tnode* t2)
{
	if(t1 == NULL)
	{
		return t2;
	}
	if(t2 == NULL)
	{
		return t1;
	}
	t1 -> value = (t1 -> value) + (t2 -> value);
	t1 -> left = mergeTrees(t1 -> left, t2 -> left);
	t1 -> right = mergeTrees(t1 -> right, t2 -> right);
	return t1;
}

void inorder(tnode* root)
{
	if(root == NULL)
	{
		return;
	}
	inorder(root -> left);
	printf("%d\n", root -> value);
	inorder(root -> right);
}
