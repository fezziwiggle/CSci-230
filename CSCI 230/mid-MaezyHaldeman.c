//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: MIDTERM

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
} *FAT;


int SCAN(FILE *(*stream)) { //gets the number of file lines with action "a"

int size = 0;
*stream = fopen("hw6(2).data", "r");
char circle[42];
char name[42];
char number[8];
char action[2];

	while (fscanf(*stream, "%s %s %s %s", circle, name, number, action) == 4) {
		if (strcmp(action, "a") == 0) {
			size++;
		}
		
	}
	fclose(*stream);

	return size;
}


struct _fat *ADD(char *circle, char *name, char *number, int i, struct _dirEntry directory[], struct _fat *FAT, int size) {

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
			
			while (FAT[currentBlock].next != 0) { //find the end of the linked list in the FAT
			
				currentBlock = FAT[currentBlock].next;
			}
			
			
			for (k = 0; k < size; k++) {

				if (strcmp(FAT[k].name, "") == 0) { //find the next empty spot in the FAT
					
					
					strcpy(FAT[k].name, name);
					strcpy(FAT[k].number, number); 
					
					FAT[currentBlock].next = k; 
					
					FAT[k].previous = currentBlock;
				
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
				
				for (k = 0; k < size; k++) {

					if (strcmp(FAT[k].name, "") == 0) { //find the next empty spot in the FAT

						strcpy(FAT[k].name, name);
						strcpy(FAT[k].number, number); 
					
						FAT[k].previous = -(j); 
					
						break;
					}	
				}
				
				directory[j].startBlock = k;
				
				circleExists = true;
				break;
			}
		}
	}
	
	return FAT;

}


void DELETE(char *circle, char *name, char *number, struct _dirEntry directory[], struct _fat *FAT) {

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
			
			if (FAT[currentBlock].next == 0) { //if there is only one entry in the linked list
				if (strcmp(FAT[currentBlock].name, name) == 0) { //find a matching name in the FAT
					fatExists = true;
				}
			}
			
			while (FAT[currentBlock].next != 0) { //start looking through the linked list
			
				if (strcmp(FAT[currentBlock].name, name) == 0) { //find a matching name in the FAT
					fatExists = true;
					
					break;
				}
				
				currentBlock = FAT[currentBlock].next;
				
				if (FAT[currentBlock].next == 0) { //catches when the last node in the linked list is the matching name
					if (strcmp(FAT[currentBlock].name, name) == 0) { 
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
					previousBlock = FAT[currentBlock].previous;
					nextBlock = FAT[currentBlock].next;
				
					FAT[previousBlock].next = FAT[currentBlock].next;
					
					if (nextBlock != 0) { //if we are not deleting the last node in the linked list
						FAT[nextBlock].previous = FAT[currentBlock].previous;
						
						strcpy(FAT[currentBlock].name, "");
						strcpy(FAT[currentBlock].number, "");
						FAT[currentBlock].previous = 0;
						FAT[currentBlock].next = 0;
					}
					
					else { //we ARE deleting the last node in the linked list, so reset the last node
						strcpy(FAT[currentBlock].name, "");
						strcpy(FAT[currentBlock].number, "");
						FAT[currentBlock].previous = 0;
						FAT[currentBlock].next = 0;
					}					
				}
				
				else { //if the node is the first node in its circle, see if it is the only node in its circle
					directoryEntry = -(FAT[currentBlock].previous);
					
					if (FAT[currentBlock].next != 0) { //the node is NOT the only node in the circle

						nextBlock = FAT[currentBlock].next;
						previousBlock = FAT[currentBlock].previous;
						
						directory[directoryEntry].startBlock = nextBlock;
						FAT[nextBlock].previous = -(directoryEntry);
						FAT[previousBlock].next = FAT[currentBlock].next;
						
						strcpy(FAT[currentBlock].name, "");
						strcpy(FAT[currentBlock].number, "");
						FAT[currentBlock].previous = 0;
						FAT[currentBlock].next = 0;
						
					}	
						
					else { //the node IS the only node in the circle, so delete the node AND the circle
						strcpy(directory[directoryEntry].circle, "");
						directory[directoryEntry].startBlock = 0;

						strcpy(FAT[currentBlock].name, "");
						strcpy(FAT[currentBlock].number, "");
						FAT[currentBlock].previous = 0;
						FAT[currentBlock].next = 0;	
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



void QUERY(char *circle, char *name, char *number, struct _dirEntry directory[], struct _fat *FAT, int size) {

int j; //element counter for the FAT
bool entryExists = false;

	
	for (j = 0; j < size; j++) { //find name in FAT
	
		if (strcmp(name, FAT[j].name) == 0) {
			
			printf("\nQuery for %s:\n", name);
			
			if (FAT[j].previous <= 0 && FAT[j].next == 0) { //if there is only one node in the linked list
				printf("%s %s\n", FAT[j].name, FAT[j].number);
			}
			
			else { //if there is more than one node in the linked list
				while (FAT[j].previous >= 0) { //go to the first node
					j = FAT[j].previous;
					if (FAT[j].previous <= 0) { 
						if (FAT[j].previous == 0) { //catches the case when .previous is entry 0 in the FAT
							j = FAT[j].previous;
						}
						break;
					}
				}
				
				while (FAT[j].next != 0) { //start from the first node and print all subsequent nodes in linked list
					printf("%s %s\n", FAT[j].name, FAT[j].number);
					j = FAT[j].next;
					
					if (FAT[j].next == 0) {
						printf("%s %s\n", FAT[j].name, FAT[j].number);
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
char number[8];
char action[2];

int i = 0;
int j = 0;

int size;


	struct _dirEntry directory[10]; //creates a blank directory with 10 spots
	
	for (j = 0; j < 10; j++) { //initializes all directory entries to "" or 0
		strcpy(directory[j].circle, "");
		directory[j].startBlock = 0;
	}
	
	size = SCAN(&stream); //gets number of file lines with action "a"
	
	FAT = (struct _fat *)malloc(size * sizeof(struct _fat));
	
	for (j = 0; j < size; j++) { //initializes all FAT entries to "" or 0
		strcpy(FAT[j].name, "");
		strcpy(FAT[j].number, "");
		FAT[j].previous = 0;
		FAT[j].next = 0;
	}
	
	//free(FAT);

	stream = fopen("hw6(2).data", "r");
	
	//loop will get the character (a, d, or q) from the end of each line in a file
	//if statements will make a function call to either the add, delete, or query function
	
	while (fscanf(stream, "%s %s %s %s", circle, name, number, action) == 4) {
		
		if (strcmp(action, "a") == 0) {
					
			ADD(circle, name, number, i, directory, FAT, size);

		}
		else if (strcmp(action, "d") == 0)  {
			
			DELETE(circle, name, number, directory, FAT);	
		}
		else if (strcmp(action, "q") == 0)  {
			
			QUERY(circle, name, number, directory, FAT, size);
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
	for (h = 0; h < size; h++) { 
		if (strcmp(FAT[h].name, "") != 0) {
			printf("%d Name: %s Number: %s Previous: %d Next: %d\n", h, FAT[h].name, FAT[h].number, FAT[h].previous, FAT[h].next);
		}
	}
	
	free(FAT);
	
	fclose(stream);
	
	
	
return 0;
}
	
