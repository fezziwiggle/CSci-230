#include <stdlib.h>
#include <stdio.h>


struct myStruct {
	char S1[20];
	float F;
	int I;
	char S2[20];
};
	

int main(void) 

{
	struct myStruct arr_myStruct[100];

	
	FILE *stream;
	stream = fopen("hw2.data", "r");

	if (stream == NULL ) 
		{
		exit(0);
		}
	
	int currentElement;
	currentElement = 0;
			
	while (fscanf(stream, "%s %f %d %s", 
	arr_myStruct[currentElement].S1,
	&arr_myStruct[currentElement].F, 
	&arr_myStruct[currentElement].I, 
	arr_myStruct[currentElement].S2) == 4)

	{	
	currentElement += 1;
	}
	
	fclose(stream);

return 0;

}
