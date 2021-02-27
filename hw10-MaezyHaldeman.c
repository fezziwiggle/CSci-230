//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 10

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct _node {
	char name[10];
	struct _node *previous;
	struct _node *next;
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


//initialize newNode

struct _node *NEWNODE(char *name) {

	struct _node *newNode = (struct _node*)malloc(sizeof(struct _node));
	
	strcpy(newNode->name, name);
	newNode->next = NULL;
	newNode->previous = NULL;
	
	return newNode;

}

//add to linked list

void ADD(struct _node *(*head), struct _node *(*tail), struct _node *newNode) {

struct _node *current;

	current = (struct _node*)malloc(sizeof(struct _node));
	
	if ((*head) == NULL) { //we are starting a new linked list
		strcpy(current->name, newNode->name);
		current->next = NULL;
		current->previous = NULL;
		(*head) = current;
		(*tail) = current;
	}
	
	else { //insert node into alphabetical location
		
		current = (*head);
		
		while (current != NULL) {
		
			if (current == (*head) && strcmp(current->name, newNode->name) > 0 ) { //if the location to insert is before the first node
							
				newNode->next = current;
				(*head) = newNode;
				
				newNode->previous = NULL;
				current->previous = newNode;
				
				break;
			}
			
			else if (current->next == NULL) { //we will be adding newNode to the end of the list
				
				newNode->next = current->next;
				(*tail) = newNode;
				current->next = newNode;
				newNode->previous = current;
								
				break;
			}
			
			else if (strcmp(current->next->name, newNode->name) > 0) { //we've found the node right before the location to insert newNode
			
				newNode->next = current->next;
				current->next->previous = newNode;
				current->next = newNode;
				newNode->previous = current;

				break;
			}
				
			else { //go to the next node and compare newNode again
			
				current = current->next;
			}
		}
	}
}


//delete from linked list

void DELETE(struct _node *(*head), struct _node *(*tail), char *name) {

struct _node *current;
struct _node *obsoleteNode;

	//we get here

	current = (struct _node*)malloc(sizeof(struct _node));
	
	current = (*head);
		
	while (current->next != NULL) { //this was originally current != NULL... caused segfault in line 141
		
		if (current == (*head) && strcmp(current->name, name) == 0) { //if we are deleting the first node
		
		//printf("Are we here?\n");
			
			obsoleteNode = (*head);
			(*head) = (*head)->next;
			
			(*head)->previous = obsoleteNode->previous;
			
			free(obsoleteNode);
			break;
			
		}
		
		else if (strcmp(current->next->name, name) == 0) { //we are deleting from the middle or end of the list
			
			obsoleteNode = current->next;
					
			if (obsoleteNode->next == NULL) { //we are deleting the last node
				(*tail) = obsoleteNode->previous;
			}
			
			else { //we are not deleting the last node
				current->next->next->previous = current;
			}
			
			current->next = current->next->next;			
			
			free(obsoleteNode);			
			break;
		}
		
		else { //keep looking
		//printf("Are we here?\n");
			current = current->next;
		}
	}
}


//print forward linked list

void PRINTFORWARD(struct _node *(*head)) {
	
struct _node *temp;
	
	temp = (*head);
	
	printf("\nLINKED LIST: ALPHABETICALLY INCREASING\n");
	
	while (temp != NULL) {
		printf("**%s\n", temp->name);
		temp = temp->next;
	}
}


//print backward linked list

void PRINTBACKWARD(struct _node *(*tail)) {

struct _node *temp;
	
	temp = (*tail);
	
	printf("\nLINKED LIST: ALPHABETICALLY DECREASING\n");
	
	while (temp!= NULL) {
		printf("**%s\n", temp->name);
		temp = temp->previous;
	}
}


//free linked list

void FREE(struct _node *(*head), struct _node *(*tail)) {
	
struct _node *current;
struct _node *freeNode;

	printf("\nFreeing linked list...\n");

	current = (struct _node*)malloc(sizeof(struct _node));
	
	current = (*head);
	
	while (current != NULL) {
		
		freeNode = current;
		current = current->next;
		free(freeNode);
	}
	
	(*head) = NULL;
	(*tail) = NULL;
}


int main(void) {

char name[42];
char action[2];
int size;
int i;

char *buffer;
size_t bufSize;

FILE *stream;

	//stream = fopen("hw7-Gill.data", "r");
	stream = fopen("hw7.data", "r");
	size = SCAN(&stream);
	
	struct _node *head;
	head = NULL;
	
	struct _node *tail;
	tail = NULL;
	
	rewind(stream); //have to rewind the file since we ran through it once in SCAN
	
	char *nameTok;
	char *actionTok;
	
	for (i = 0; i < size; i++) { //for every line in hw7.data
		
		buffer = NULL;
		getline(&buffer, &bufSize, stream);
		
		nameTok = strtok(buffer, " "); //gets the name
		actionTok = strtok(NULL, "\n"); //gets the action
		
		//printf("\n%s\n", nameTok);
		
		strncpy(name, nameTok, 10); //[10] = '\0';
		if (strlen(name) >= 10) {
			name[10] = '\0';
		}
		strncpy(action, actionTok, 2);
		
		//name[10] = '\0';
		
		//printf("After strncpy \n");
		//printf("%s\n", name);
		
		free(buffer);
		
		if (strcmp(action, "a") == 0) { 
			
			//printf("\nAdding %s\n", name);
			
			struct _node *newNode = NEWNODE(name);
			ADD(&head, &tail, newNode);
			//PRINTFORWARD(&head);
		}
		
		else if (strcmp(action, "d") == 0)  { //if we have cullencull in the list and try to delete cullen, this segfaults (same with vladvladvl and vlad) - something with strcmp in delete
		
			//printf("\nDeleting %s\n", name);
			
			DELETE(&head, &tail, name);
			//PRINTFORWARD(&head);
		}
	}
		
		
	/*while (fscanf(stream, "%s %s", name, action) == 2) {
	
		if (strcmp(action, "a") == 0) {
			
			//printf("\nAdding %s\n", name);
			
			struct _node *newNode = NEWNODE(name);
			ADD(&head, &tail, newNode);
		}
		
		else if (strcmp(action, "d") == 0)  {
		
			//printf("\nDeleting %s\n", name);
			
			DELETE(&head, &tail, name);
		}
	}*/
	
	PRINTFORWARD(&head);
	PRINTBACKWARD(&tail);
	
	FREE(&head, &tail);

return 0;
}
