//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 5

#include "hw5-D-MaezyHaldeman.h"

//function to free the dynamic memory we allocated 



void FREE(struct _data *BlackBox, int size) {
int i;
	
	for (i = 0; i < size+1; i++) {
		free(BlackBox[i].name);
	}
	
	free(BlackBox);
}
