//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 5

#ifndef hw5-A-MaezyHaldeman_h_
#define hw5-A-MaezyHaldeman_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//function to free the dynamic memory we allocated 

struct _data {
	char *name;
	long number;
};

void FREE(struct _data *BlackBox, int size);

#endif
