//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 9

#include <stdlib.h>
#include <stdio.h>


struct myTree {
	int val;
	struct myTree *right, *left;
};


struct _link {
	struct myTree *treeNode; //is this right?
	struct _link *next;
};



void BUBBLE_SORT(int array[], int count) { //from Marsh's solution
int i, j;
int swap;

  for (j = 0; j < count-1; j++) {
      for (i = 0; i < count-j-1; i++) {
          if (array[i] > array[i+1]) {
             swap       = array[i];
             array[i]   = array[i+1];
             array[i+1] = swap;
          }
      }
  }
}


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

            //should we test if the line in the file is empty? (only a newline character)

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


void INSERT(_node *(*tree), _node *item, struct _link *(*linkCurrent)) { //problem child

	if (!(*tree)) {
		*tree = item;
        
		while ((*linkCurrent)->next != NULL) {
           		*linkCurrent = (*linkCurrent)->next;
		}

		(*linkCurrent)->treeNode = *tree;
//		printf("Match: %d\n", (*linkCurrent)->treeNode->val);
		(*linkCurrent)->next = (struct _link*)malloc(sizeof(struct _link));
        	(*linkCurrent)->next->next = NULL;

		return;
	}
	
	if (item->val < (*tree)->val) {
		
//		printf("Left: %d\n", (*linkCurrent)->treeNode->val);
		INSERT(&(*tree)->left, item, &(*linkCurrent));
	}
	
	else if (item->val > (*tree)->val) {
//		printf("Right: %d\n", (*linkCurrent)->treeNode->val);
		INSERT(&(*tree)->right, item, &(*linkCurrent));
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


void FREE(struct _link *(*head)) { //frees the tree and list using the linked list
	struct _link *current;
	current = (*head);
	
	struct _link *obsoleteLink;
	obsoleteLink = (struct _link*)malloc(sizeof(struct _link));
	
	_node *obsoleteNode;
	obsoleteNode = (_node *)malloc(sizeof(_node));
	
	while (current->next != NULL) {
		obsoleteLink = current;
		obsoleteNode = current->treeNode;
		
		current = current->next;
		
		free(obsoleteNode);
		free(obsoleteLink);
	}
		
	
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

	//stream = fopen("hw9.data", "r"); 
	//stream = fopen("hw9-Gill.data", "r"); 
	stream = fopen("hw9-Gill-edited.data", "r"); 
	size = SCAN(&stream);
	intArray = (int *)malloc(size * sizeof(int));
	intArray = INTARRAY(size, stream, intArray); //fill intArray with integers from file - unsorted array
	fclose(stream);
	
	start = 0;
	end = size;

				/*printf("intArray\n");
				for (i = 0; i < size; i++) {
					printf("%d\n", intArray[i]);
				}*/
	
	BUBBLE_SORT(intArray, size); //sorts intArray in order
				
	balanced = malloc(size * sizeof(int));		
	SORTARRAY(intArray, start, end, balanced); //balances the sorted intArray
				
				/*printf("\nbalanced\n");
				for (i = 0; i < size; i++) {
					printf("%d\n", balanced[i]);
				}
				printf("\n");*/
	
	root = NULL;
	
	struct _link *linkCurrent;
	linkCurrent = (struct _link*)malloc(sizeof(struct _link));
	linkCurrent->next = NULL;
	
	struct _link *head;
    	head = linkCurrent;

	
	for (i = 0; i < size; i++) {
		
		current = (_node *)malloc(sizeof(_node));
		current->left = current->right = NULL;
		current->val = balanced[i];

		INSERT(&root, current, &linkCurrent);
	}
	
	printf("\nIN ORDER\n");
	IN_ORDER(root);
	
	printf("\nPOST ORDER\n");
	POST_ORDER(root);
	
	printf("\nPRE ORDER\n");
	PRE_ORDER(root);
	
	printf("\nLINKED LIST\n");
	
	struct _link *link;
	link = head;
	
	while (link->next != NULL) {
		printf("%d\n", link->treeNode->val);
		link = link->next;
	}
	
	printf("\nFreeing tree and linked list...\n");
	FREE(&head);	
	
	/*printf("\nFREED LINKED LIST\n");
	while (link->next != NULL) {
		printf("%d\n", link->treeNode->val);
		link = link->next;
	}*/


return 0;
}
