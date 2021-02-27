//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 11

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <dlfcn.h> //required for dlopen and other dynamic shared library stuff
//#include "./hw11-lib-MaezyHaldeman.h"

//#include "hw11-A-MaezyHaldeman.h"
//#include "hw11-B-MaezyHaldeman.h"
//#include "hw11-C-MaezyHaldeman.h"
//#include "hw11-D-MaezyHaldeman.h"


/*struct _data {
	char *name;
	long number;
};*/

int main(int argv, char **argc) {

int size;
struct _data *BlackBox;

FILE *stream;

void *handle; //void pointer for handle
handle = dlopen("./hw11-lib-MaezyHaldeman.so", RTLD_LAZY);
    if (!handle) printf("%s\n", dlerror()); //check for error

int (*SCAN)(FILE *(*stream));
struct _data *(*LOAD)(FILE *stream, int); //should struct be struct _data? should (*LOAD) be *(*LOAD)?
void (*SEARCH)(struct _data *, char *, int); //should struct * be struct _data *?
void (*FREE)(struct _data *, int); //should struct * be struct _data *?

SCAN = dlsym(handle, "SCAN");
LOAD = dlsym(handle, "LOAD"); //should LOAD be a pointer?
SEARCH = dlsym(handle, "SEARCH");
FREE = dlsym(handle, "FREE");
    //check for error here?

    


	if (argv == 2) {
        
    		size = (*SCAN)(&stream);
		BlackBox = (*LOAD)(stream, size);
		(*SEARCH)(BlackBox, argc[1], size);
		(*FREE)(BlackBox, size);

		//size = SCAN(&stream);
		//BlackBox = LOAD(stream, size);
		//SEARCH(BlackBox, argc[1], size);
		//FREE(BlackBox, size);
	}
	
	else if (argv > 2) {
		printf("Too many arguments (one expected)\n");
	}
	
	else {
		printf("You must include a name to search for\n");
	}	
	
	dlclose(handle);
}

