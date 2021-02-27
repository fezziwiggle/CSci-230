//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 7

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct _node {
	char name[42];
	struct _node *next;
};


//initialize newNode

struct _node *NEWNODE(char *name) {

	struct _node *newNode = (struct _node*)malloc(sizeof(struct _node));
	
	strcpy(newNode->name, name);
	newNode->next = NULL;
	
	return newNode;

}

//add to linked list

void ADD(struct _node *(*head), struct _node *newNode) {

struct _node *current;

	current = (struct _node*)malloc(sizeof(struct _node));
	
	if ((*head) == NULL) { //we are starting a new linked list
		strcpy(current->name, newNode->name);
		current->next = NULL;
		(*head) = current;
	}
	
	else { //insert node into alphabetical location
		
		current = (*head);
		
		while (current != NULL) {
			
			if (current == (*head) && strcmp(current->name, newNode->name) > 0 ) { //if the location to insert is before the first node
				
				newNode->next = current;
				(*head) = newNode;
				break;
			}
			
			else if (current->next == NULL) { //we will be adding newNode to the end of the list
				newNode->next = current->next;
				current->next = newNode;
				break;
			}
			
			else if (strcmp(current->next->name, newNode->name) > 0) { //we've found the node right before the location to insert newNode
				
				newNode->next = current->next;
				current->next = newNode;
				break;
			}
				
			else { //go to the next node and compare newNode again
			
				current = current->next;
				
			}
		}
	
	}
}


//delete from linked list

void DELETE(struct _node *(*head), char *name) {

struct _node *current;
struct _node *obsoleteNode;

	current = (struct _node*)malloc(sizeof(struct _node));
	
	current = (*head);
		
	while (current != NULL) {
		
		if (current == (*head) && strcmp(current->name, name) == 0) { //if we are deleting the first node
			
			obsoleteNode = (*head);
			(*head) = (*head)->next;
			free(obsoleteNode);
			break;
			
		}
		
		else if (strcmp(current->next->name, name) == 0) { //we are deleting a node from the middle of the list
			
			obsoleteNode = current->next;
			current->next = current->next->next;
			free(obsoleteNode);
			break;
		}
		
		else {
			current = current->next;
		}
	}
}


//print linked list

void PRINT(struct _node *(*head)) {
	
struct _node *temp;
	
	temp = (*head);
	
	printf("\nLINKED LIST\n");
	
	while (temp != NULL) {
		printf("%s\n", temp->name);
		temp = temp->next;
	}
}



//free linked list

void FREE(struct _node *(*head)) {
	
struct _node *current;
struct _node *freeNode;

	current = (struct _node*)malloc(sizeof(struct _node));
	
	current = (*head);
	
	while (current != NULL) {
		
		freeNode = current;
		current = current->next;
		free(freeNode);
	}
	
	(*head) = NULL;
}


int main(void) {

char name[42];
char action[2];


FILE *stream;

	stream = fopen("hw7.data", "r");
	
	struct _node *head;
	head = NULL;
	

	
	while (fscanf(stream, "%s %s", name, action) == 2) {
	
		if (strcmp(action, "a") == 0) {
			
			//call add function
			
			printf("\nAdding %s\n", name);
			
			struct _node *newNode = NEWNODE(name);
			ADD(&head, newNode);
			
			PRINT(&head);
		}
		
		else if (strcmp(action, "d") == 0)  {
		
			//call delete function
			
			printf("\nDeleting %s\n", name);
			
			DELETE(&head, name);
			
			PRINT(&head);			
		}
	
	}
	
	PRINT(&head);
	printf("\nFreeing linked list...\n");
	FREE(&head);
	//PRINT(&head);

return 0;
}
