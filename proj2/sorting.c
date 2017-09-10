#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"

Node *Make_Seq(int Size);
int Num_Elements(Node * head);
void reverse(Node ** head);
long findValue(Node * head, int val);
void destroyList(Node ** head);
void Insert(Node ** head, Node * new);

Node *Load_From_File(char *Filename)
{
	FILE *file; //pointer to the file
	long number; //the value of the number being read
	long size; //amount of long numbers in the file
	Node * head = NULL; //the beginning of the list
	Node * pointer = NULL; //the pointer to the current node
	Node * temp = NULL; //temporary value for holding a node
	
	file = fopen(Filename, "rb"); //opens the file

	//error checking to make sure the file opened correctly
	if(!file)
	{
		fprintf(stderr, "Can't open file\n");
		return NULL;
	}
	fseek(file, 0L, SEEK_END); //finds the end of the file
	long position = ftell(file);
	size = position / sizeof(long);
	fseek(file, 0L, SEEK_SET); //rewinds to the beginning of the file

	//Creates the first head Node
	if(head == NULL && size > 0)
	{
		head = malloc(sizeof(Node));
		fread(&number, sizeof(long), 1, file);
		head -> value = number;
		head -> next = NULL;
		size = size - 1;
	}
	
	//Creates the second Node
	if(size > 0)
	{
		pointer = malloc(sizeof(Node));
		fread(&number, sizeof(long), 1, file);
		pointer -> value = number;
		pointer -> next = NULL;
		head -> next = pointer; //connects the head and this new node
		size = size - 1;
	}

	//Creates the rest of the Nodes
	while(size > 0)
	{
		temp = malloc(sizeof(Node));
		fread(&number, sizeof(long), 1, file);
		temp -> value = number;
		temp -> next = NULL;
		pointer -> next = temp; //connects it to the previous node
		pointer = pointer -> next; //moves pointer in the list to the next node
		size = size - 1;
	}	
	fclose(file); //closes the file
	return head; //returns the head of the list
}

int Save_To_File(char *Filename, Node * list)
{
	FILE * file;
	Node * temp = NULL;
	int counter = 0;
	file = fopen(Filename, "wb"); //opens the file to write in binary
	temp = list;
	long value;
	while(temp)
	{
		value = temp -> value;
		fwrite(&value, sizeof(long), 1, file); //writes one number at a time
		temp = temp -> next; //goes to the next number
		counter++;
	}
	destroyList(&list);
	fclose(file);

	return counter;
}


Node * Shell_Sort(Node * list)
{
	int Size; //size of the numbers in the original file
	int size2 = 0; //size of numbers in the sequence
	Node *Seq = NULL; //Sequence list
	int k = 0;
	Node *temp = NULL;
	Node *sorted = NULL;
	Node *curr = list;
		
	temp = list;
	Size = Num_Elements(temp); //finds the number of elements in the original list
	Seq = Make_Seq(Size);
	temp = Seq;
	size2 = Num_Elements(temp); //finds the size in the sequence list
	reverse(&Seq); //reverses the list so it moves on
	
	for(k = 0; k < size2; k++) //for each number in the sequence
	{
		long value = findValue(Seq, k); //finds the sequence number
		if(value <= Size) //if the value in the sequence is less the than list's size
		{
			while(curr != NULL)
			{
				Node *next = curr -> next;

				Insert(&sorted, curr); //utilizes insertion sort
				curr = next;
			}
		}
		
	}

	list = sorted; //reassigns the list to the sorted list
	destroyList(&Seq); //frees the sequence list
		
	return list;
}

void Insert(Node ** head, Node* new)
{
	Node * curr;
	if(*head == NULL || (*head) -> value >= new -> value)
	{
		new -> next = *head; //checks if the number needs to go at the head
		*head = new;
	}
	else
	{
		curr = *head;
		while(curr -> next != NULL && curr -> next -> value < new-> value)
		{
			curr = curr -> next; //finds the correct spot to insert the new node
		}
		new -> next = curr -> next;
		curr -> next = new; //places the new node
	}
}
void reverse(Node ** head)
{
	Node * prev = NULL;
	Node * curr = *head;
	Node * next = NULL;
	while(curr != NULL) //reverses the list
	{
		next = curr -> next;
		curr -> next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

long findValue(Node * head, int val)
{
	//finds the value that the function needs based on the value
	Node * temp = head;
	long num = 0;
	while(val > 0)
	{
		val--;
		temp = temp -> next;
	}
	num = temp -> value;
	return num;
}
	
int Num_Elements(Node * head)
{
	//counts the number of nodes in a list
	int counter = 0;
	Node * temp_list = head;

	while(temp_list != NULL)
	{
		temp_list = temp_list -> next;
		counter++;
	}

	return counter;
}

void destroyList(Node ** head)
{
	//traverses through the list and frees each node
	Node * curr = *head;
	Node* next = NULL;

	while(curr != NULL)
	{
		next = curr -> next;
		free(curr);
		curr = next;
	}
	*head = NULL;
}

Node * Make_Seq(int Size)
{
	Node* head = NULL;
	Node* Seq = NULL;
	Node* curr = NULL;
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

	while(max3 <= Size)
	{
		max3 *= 3;
		numLevel3++;//finds the highest level multiples of three can go to
	}
	
	while(max2 <= Size)
	{
		max2 *= 2;
		numLevel2++;//finds the highest level multiples of two can go to
	}
	
	for(temp = numLevel3; temp > 0; temp--)
	{
		temp_elem += temp; //finds the number of elements up to the third level
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
			temp_elem++; //finds the total number of elements
		}
		
		numLevel3++;
		max2 *= 2;
	}
	head = malloc(sizeof(Node)); //allocates space for the head node

	head -> value = 1; //the first node will always be 1
	head -> next = NULL;
	curr = head;
	curr = curr -> next;
	temp_elem--;
	
	while(startLevel < Level && temp_elem > 0)
	{
	//finds the rest of the sequence
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
				if(head -> next == NULL)
				{
					curr = malloc(sizeof(Node));
					curr -> value = value;
					head -> next = curr;
					temp_elem--;
					curr -> next = NULL;
				}
				else
				{
					Seq = malloc(sizeof(Node));
					Seq -> value = value;
					Seq -> next = NULL;
					curr -> next = Seq;
					curr = curr -> next;
				}
					
			}
			p -= 1;
			q += 1;
		}
		
		startLevel++;
	}
	curr -> next = NULL;
	return head;
}
