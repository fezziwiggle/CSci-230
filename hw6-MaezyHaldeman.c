//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 6

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


struct _dirEntry {
	char circle[42];
	int startBlock;
};

struct _fat {
	char name[42];
	char number[8];
	int next; 
	int previous;
};


void ADD(char *circle, char *name, char *number, int i, struct _dirEntry directory[], struct _fat fat[]) {

int j; //element counter for the directory
int k; //element counter for the FAT
bool circleExists = false;

	int startBlock;	
	int currentBlock;
	
	printf("\nAdding %s to %s...\n", name, circle);
	
	for (j = 0; j < 10; j++) { //if the circle exists, add the name to the circle
	
		if (strcmp(circle, directory[j].circle) == 0) {
			
			startBlock = directory[j].startBlock; //gets the start of the circle's linked list in the FAT
			currentBlock = startBlock;
			
			while (fat[currentBlock].next != 0) { //find the end of the linked list in the FAT
			
				currentBlock = fat[currentBlock].next;
			}
			
			for (k = 0; k < 100; k++) {
				if (strcmp(fat[k].name, "") == 0) { //find the next empty spot in the FAT
					
					strcpy(fat[k].name, name);
					strcpy(fat[k].number, number); 
					
					fat[currentBlock].next = k; 
					
					fat[k].previous = currentBlock;
					break;
				}	
			}
			
			circleExists = true;
		} 
	}
	
	if (circleExists == false) { //if the circle doesn't exist, create circle in the directory
		
		for (j = 0; j < 10; j++) {
			if (strcmp(directory[j].circle, "") == 0) { //find the next empty spot in the directory
				strcpy(directory[j].circle, circle);
				
				for (k = 0; k < 100; k++) {
					if (strcmp(fat[k].name, "") == 0) { //find the next empty spot in the FAT
					
						strcpy(fat[k].name, name);
						strcpy(fat[k].number, number); 
					
						fat[k].previous = -(j); 
					
						break;
					}	
				}
				
				directory[j].startBlock = k;
				
				circleExists = true;
				break;
			}
		}
	}

}


void DELETE(char *circle, char *name, char *number, struct _dirEntry directory[], struct _fat fat[]) {

int j; //element counter for the directory
int k; //element counter for the FAT
bool circleExists = false;

	int startBlock;	
	int currentBlock;
	int previousBlock;
	int nextBlock;
	bool fatExists = false;
	
	int directoryEntry;
	
	printf("\nDeleting %s from %s...\n", name, circle);
	
	for (j = 0; j < 10; j++) { //if the circle exists, enter its linked list
	
		if (strcmp(circle, directory[j].circle) == 0) {
			
			startBlock = directory[j].startBlock; //gets the start of the circle's linked list in the FAT
			currentBlock = startBlock;
			
			if (fat[currentBlock].next == 0) { //if there is only one entry in the linked list
				if (strcmp(fat[currentBlock].name, name) == 0) { //find a matching name in the FAT
					fatExists = true;
				}
			}
			
			while (fat[currentBlock].next != 0) { //start looking through the linked list
			
				if (strcmp(fat[currentBlock].name, name) == 0) { //find a matching name in the FAT
					fatExists = true;
					
					break;
				}
				
				currentBlock = fat[currentBlock].next;
				
				if (fat[currentBlock].next == 0) { //catches when the last node in the linked list is the matching name
					if (strcmp(fat[currentBlock].name, name) == 0) { 
						fatExists = true;
						break;
					}
				}
			}
			
			int temp;
			
			for (temp = 0; temp < 10; temp++) { //this will find the directory entry of the circle we are deleting from
				if (strcmp(directory[temp].circle, circle) == 0) {
					break;
				}
			}
			
			if (fatExists == true) { //if the name is in the FAT, delete that entry
			
				if (directory[temp].startBlock != currentBlock) { //if the entry is NOT the first entry in its circle
					previousBlock = fat[currentBlock].previous;
					nextBlock = fat[currentBlock].next;
				
					fat[previousBlock].next = fat[currentBlock].next;
					
					if (nextBlock != 0) { //if we are not deleting the last node in the linked list
						fat[nextBlock].previous = fat[currentBlock].previous;
						
						strcpy(fat[currentBlock].name, "");
						strcpy(fat[currentBlock].number, "");
						fat[currentBlock].previous = 0;
						fat[currentBlock].next = 0;
					}
					
					else { //we ARE deleting the last node in the linked list, so reset the last node
						strcpy(fat[currentBlock].name, "");
						strcpy(fat[currentBlock].number, "");
						fat[currentBlock].previous = 0;
						fat[currentBlock].next = 0;
					}					
				}
				
				else { //if the node is the first node in its circle, see if it is the only node in its circle
					directoryEntry = -(fat[currentBlock].previous);
					
					if (fat[currentBlock].next != 0) { //the node is NOT the only node in the circle

						nextBlock = fat[currentBlock].next;
						previousBlock = fat[currentBlock].previous;
						
						directory[directoryEntry].startBlock = nextBlock;
						fat[nextBlock].previous = -(directoryEntry);
						fat[previousBlock].next = fat[currentBlock].next;
						
						strcpy(fat[currentBlock].name, "");
						strcpy(fat[currentBlock].number, "");
						fat[currentBlock].previous = 0;
						fat[currentBlock].next = 0;
						
					}	
						
					else { //the node IS the only node in the circle, so delete the node AND the circle
						strcpy(directory[directoryEntry].circle, "");
						directory[directoryEntry].startBlock = 0;

						strcpy(fat[currentBlock].name, "");
						strcpy(fat[currentBlock].number, "");
						fat[currentBlock].previous = 0;
						fat[currentBlock].next = 0;	
					}		
				}
			}
			
			if (fatExists == false) { //if the name is not in the FAT, print an error message
				
				printf("Cannot delete a nonexistent entry from the FAT\n");
			}
			
			circleExists = true;
		} 
	}
	
	if (circleExists == false) { //if the circle doesn't exist, print an error message
		
		printf("Cannot delete a name from a nonexistent circle\n");
		
	}
}



void QUERY(char *circle, char *name, char *number, struct _dirEntry directory[], struct _fat fat[]) {

int j; //element counter for the FAT
bool entryExists = false;

	
	for (j = 0; j < 100; j++) { //find name in FAT
	
		if (strcmp(name, fat[j].name) == 0) {
			
			printf("\nQuery for %s:\n", name);
			
			if (fat[j].previous <= 0 && fat[j].next == 0) { //if there is only one node in the linked list
				printf("%s %s\n", fat[j].name, fat[j].number);
			}
			
			else { //if there is more than one node in the linked list
				while (fat[j].previous >= 0) { //go to the first node
					j = fat[j].previous;
					if (fat[j].previous <= 0) { 
						if (fat[j].previous == 0) { //catches the case when .previous is entry 0 in the FAT
							j = fat[j].previous;
						}
						break;
					}
				}
				
				while (fat[j].next != 0) { //start from the first node and print all subsequent nodes in linked list
					printf("%s %s\n", fat[j].name, fat[j].number);
					j = fat[j].next;
					
					if (fat[j].next == 0) {
						printf("%s %s\n", fat[j].name, fat[j].number);
						break;
					}
				}
			}
			
			entryExists = true;
			break;
		} 
	}
	
	if (entryExists == false) { //if the entry isn't in the FAT, print an error message
		
		printf("\nQuery for %s:", name);
		printf("\nCannot query a nonexistent entry from the FAT\n");
	}
}



int main(void) {

FILE *stream;

char circle[42];
char name[42];
char number[9];
char action[2];

int i = 0;
int j = 0;


	struct _dirEntry directory[10]; //creates a blank directory with 10 spots
	struct _fat fat[100]; //creates a blank FAT with 100 spots
	
	for (j = 0; j < 100; j++) { //initializes all 100 entries to "" or 0
		strcpy(fat[j].name, "");
		strcpy(fat[j].number, "");
		fat[j].previous = 0;
		fat[j].next = 0;
	}

	stream = fopen("hw6(2).data", "r");
	
	//loop will get the character (a, d, or q) from the end of each line in a file
	//if statements will make a function call to either the add, delete, or query function
	
	while (fscanf(stream, "%s %s %s %s", circle, name, number, action) == 4) {
		
		if (strcmp(action, "a") == 0) {
					
			ADD(circle, name, number, i, directory, fat);
		}
		else if (strcmp(action, "d") == 0)  {
			
			DELETE(circle, name, number, directory, fat);	
		}
		else if (strcmp(action, "q") == 0)  {
			
			QUERY(circle, name, number, directory, fat);
		}
		
		i++;
	}
	
	int h;
	printf("\nDIRECTORY\n");
	for (h = 0; h < 10; h++) {
		if (strcmp(directory[h].circle, "") != 0) {
			printf("%d Circle: %s Start Block: %d\n", h, directory[h].circle, directory[h].startBlock);
		}
	}
	
	printf("\nFAT\n");
	for (h = 0; h < 100; h++) { 
		if (strcmp(fat[h].name, "") != 0) {
			printf("%d Name: %s Number: %s Previous: %d Next: %d\n", h, fat[h].name, fat[h].number, fat[h].previous, fat[h].next);
		}
	}
	
	fclose(stream);
	
return 0;
}
	
