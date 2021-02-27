//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 5

#ifndef hw5-A-MaezyHaldeman_h_
#define hw5-A-MaezyHaldeman_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//function to search the dynamic array of struct for a name 

struct _data {
	char *name;
	long number;
};

void SEARCH(struct _data *BlackBox, char *name, int size);

#endif
