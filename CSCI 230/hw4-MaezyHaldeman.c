//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 4

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct _data {
	char *name;
	long number;
};


//function to open a file(stream) and return an integer indicating the num of lines

int SCAN(FILE *(*stream)) {
int size = 0;
*stream = fopen("hw4.data", "r");
char name[20];
int number;
	while (1) {
		fscanf(*stream, "%s %d\n", name, &number);
		if (feof(*stream)) break;
		size++;
	}
	fclose(*stream);
	return size;
}


//function to create a dynamic array (of size) and read data from the file (stream) into the _data struct dynamic array. Returns the populated array of struct

struct _data *LOAD(FILE *stream, int size) {

rewind(stream);
stream = fopen("hw4.data", "r");

char *buffer = NULL; //buffer is the string containing the characters of a line in the file
size_t bufSize = 0;
ssize_t fileLine;
int i = 0;

	struct _data *BlackBox;
	BlackBox = (struct _data *)malloc(size * sizeof(struct _data));
	
	while ((fileLine = getline(&buffer, &bufSize, stream)) != -1) {
		
	char *token;
	char *nameEntry;
	char *nameCpy;
	char *numEntry;
	long intNumEntry;
		
		token = strtok(buffer, " ");
		nameEntry = strcpy(nameCpy, token);

		token = strtok(NULL, " ");
		numEntry = token;
		intNumEntry = atol(numEntry);
		
		int nameLen;
		nameLen = strlen(nameEntry);
		
		BlackBox[i].name = (char *)malloc(nameLen * sizeof(BlackBox[i].name));
		
		strcpy(BlackBox[i].name, nameEntry);
		BlackBox[i].number = intNumEntry;
		
		i++;
	}
	
	fclose(stream);
	
	return BlackBox;	
}


//function to search the dynamic array of struct for a name 

void SEARCH(struct _data *BlackBox, char *name, int size) {

int i;
bool f = false;

	for (i = 0; i < size+1; i++) {
		
		if (strcmp(BlackBox[i].name, name) == 0) {
			printf("'%s' was found at entry %d\n", name, i);
			f = true;
		}
	}
	
	if (f == false) {
		printf("'%s' was not found\n", name);
	}

}


//function to free the dynamic memory we allocated 

void FREE(struct _data *BlackBox, int size) {
int i;
	
	for (i = 0; i < size+1; i++) {
		free(BlackBox[i].name);
	}
	
	free(BlackBox);
}


int main(int argv, char **argc) {

int size;
struct _data *BlackBox;

FILE *stream;

	if (argv == 2) {
		size = SCAN(&stream);
		BlackBox = LOAD(stream, size);
		SEARCH(BlackBox, argc[1], size);
		FREE(BlackBox, size);
	}
	
	else if (argv > 2) {
		printf("Too many arguments (one expected)\n");
	}
	
	else {
		printf("You must include a name to search for\n");
	}
	
	
}











