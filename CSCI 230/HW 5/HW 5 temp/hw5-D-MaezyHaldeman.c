//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hw5-A-MaezyHaldeman.h"
#include "hw5-B-MaezyHaldeman.h"
#include "hw5-C-MaezyHaldeman.h"
#include "hw5-D-MaezyHaldeman.h"

//function to free the dynamic memory we allocated



void FREE(struct _data *BlackBox, int size) {
int i;

	for (i = 0; i < size+1; i++) {
		free(BlackBox[i].name);
	}

	free(BlackBox);
}
