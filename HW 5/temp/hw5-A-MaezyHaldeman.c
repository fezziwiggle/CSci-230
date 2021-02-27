//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hw5-A-MaezyHaldeman.h"

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
