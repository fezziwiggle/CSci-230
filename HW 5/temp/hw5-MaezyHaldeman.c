//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 5

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "hw5-A-MaezyHaldeman.h"
#include "hw5-B-MaezyHaldeman.h"
#include "hw5-C-MaezyHaldeman.h"
#include "hw5-D-MaezyHaldeman.h"


/*struct _data {
	char *name;
	long number;
};*/

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

