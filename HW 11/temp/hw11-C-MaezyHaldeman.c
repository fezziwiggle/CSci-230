//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 11
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./hw11-lib-MaezyHaldeman.h"

//#include "hw11-A-MaezyHaldeman.h"
//#include "hw11-B-MaezyHaldeman.h"
//#include "hw11-C-MaezyHaldeman.h"

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
