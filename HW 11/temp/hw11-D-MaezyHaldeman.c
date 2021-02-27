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
//#include "hw11-D-MaezyHaldeman.h"

//function to free the dynamic memory we allocated



void FREE(struct _data *BlackBox, int size) {
int i;

	for (i = 0; i < size+1; i++) {
		free(BlackBox[i].name);
	}

	free(BlackBox);
}
