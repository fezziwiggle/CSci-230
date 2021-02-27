//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 5
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hw5-A-MaezyHaldeman.h"
#include "hw5-B-MaezyHaldeman.h"

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
