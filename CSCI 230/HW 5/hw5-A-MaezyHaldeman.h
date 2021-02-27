//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 5

#ifndef hw5-A-MaezyHaldeman_h_
#define hw5-A-MaezyHaldeman_h_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//function to open a file(stream) and return an integer indicating the num of lines

struct _data {
	char *name;
	long number;
};

int SCAN(FILE *(*stream));

#endif
