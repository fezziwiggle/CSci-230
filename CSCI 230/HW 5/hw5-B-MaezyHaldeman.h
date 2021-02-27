//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 5

#ifndef hw5-A-MaezyHaldeman_h_
#define hw5-A-MaezyHaldeman_h_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct _data {
	char *name;
	long number;
};

struct _data *LOAD(FILE *stream, int size);

#endif
