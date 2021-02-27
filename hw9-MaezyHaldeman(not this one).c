//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 9

#include <stdlib.h>
#include <stdio.h>


struct myTree {
	int val;
	struct myTree *right, *left;
};


struct _link {
	int num;
	struct _link *next;
};


int SCAN(FILE *(*stream)) { //figures out size of the data file - passing stream by reference

char *buffer = NULL; //buffer is the string containing the characters of a line in the file
size_t bufSize = 0;
ssize_t fileLine;
int size = 0;

	while (1) {

     		buffer = NULL;
     		getline(&buffer, &bufSize, *stream);
     		free(buffer);
     		if (feof(*stream)) break;
     		size++;
  	}
  	//printf("size: %d\n", size);
   	return size;
}


int *INTARRAY(int size, FILE *(stream), int intArray[]) { //fills our array from integers from the data file

int i;
//int *intArray = (int *)malloc(size * sizeof(int));
	
	rewind(stream);

	for (i = 0; i < size; i++) {

     		fscanf(stream, "%d", &intArray[i]);
     		//printf("%d**\n", intArray[i]);
  	}
	return intArray;
}
	

void SORTARRAY(int intArray[], int start, int end, int balanced[]) { //sorts our array into a balanced array

int mid;
static int cnt = 0;
	
	if (start > end) return;
	
	mid = (start + end)/2;
	balanced[cnt++] = intArray[mid];
	SORTARRAY(intArray, start, mid-1, balanced);
	SORTARRAY(intArray, mid+1, end, balanced);
}
	

typedef struct myTree _node;


void INSERT(_node *(*tree), _node *item, struct _link *linkCurrent) { //should linkCurrent be passed by reference or value?

	if (!(*tree)) {
		*tree = item;
		linkCurrent->num = (*tree)->val;
		
		return;
	}
	
	if (item->val < (*tree)->val) {
		
		linkCurrent = linkCurrent->next;
		INSERT(&(*tree)->left, item, linkCurrent);
	}
	
	else if (item->val > (*tree)->val) {
		
		linkCurrent = linkCurrent->next;
		INSERT(&(*tree)->right, linkCurrent);
	}
}


void IN_ORDER(_node *tree) {
	if (tree->left != NULL) IN_ORDER(tree->left);
	printf("%d\n", tree->val);
	if (tree->right != NULL) IN_ORDER(tree->right);
}


void POST_ORDER(_node *tree) {
	if (tree->left != NULL) POST_ORDER(tree->left);
	if (tree->right != NULL) POST_ORDER(tree->right);
	printf("%d\n", tree->val);
}


void PRE_ORDER(_node *tree) {
	printf("%d\n", tree->val);
	if (tree->left != NULL) PRE_ORDER(tree->left);
	if (tree->right != NULL) PRE_ORDER(tree->right);
}


int main(void) {

int i;
int size;
int *intArray;
int *balanced;

int start; //start and end points of our array
int end;

_node *current, *root;

FILE *stream;

	stream = fopen("hw9.data", "r"); 
	size = SCAN(&stream);
	intArray = (int *)malloc(size * sizeof(int));
	intArray = INTARRAY(size, stream, intArray); //fill intArray with integers from file
	fclose(stream);
	
	start = 0;
	end = size;

				printf("intArray\n");
				for (i = 0; i < size; i++) {
					printf("%d\n", intArray[i]);
				}
				
	balanced = malloc(size * sizeof(int));		
	SORTARRAY(intArray, start, end, balanced);
				
				printf("\nbalanced\n");
				for (i = 0; i < size; i++) {
					printf("%d\n", balanced[i]);
				}
				printf("\n");
	
	struct _link *head;
	head = NULL;
	
	struct _link *linkCurrent;
	linkCurrent = (struct _link*)malloc(sizeof(struct _link));
	
	(*linkCurrent) = (*head);
				
	root = NULL;
	
	for (i = 0; i < size; i++) {
		
		current = (_node *)malloc(sizeof(_node));
		current->left = current->right = NULL;
		current->val = balanced[i];
		INSERT(&root, current, linkCurrent);
	}
	
	printf("\nIN ORDER\n");
	IN_ORDER(root);
	
	printf("\nPOST ORDER\n");
	POST_ORDER(root);
	
	printf("\nPRE ORDER\n");
	PRE_ORDER(root);
	
	
	
	
	
	
return 0;
}
