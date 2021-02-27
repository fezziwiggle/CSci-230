//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 11

#ifndef HW11_StatLib
#define HW11_StatLib

struct _data {
	char *name;
	long number;
};

int SCAN(FILE *(*stream));

struct _data *LOAD(FILE *stream, int size);

void SEARCH(struct _data *BlackBox, char *name, int size);

void FREE(struct _data *BlackBox, int size);

#endif
