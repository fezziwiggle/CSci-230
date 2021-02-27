//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 3

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


	struct myStruct {
	char S1[20];
	float F;
	int I;
	char S2[20];
	}temp;
	

int getSize(void) {
int size = 0;
FILE *data;
   data = fopen("hw3.data", "r");
   while (1) {
      fscanf(data, "%s %f %d %s", temp.S1, &temp.F, &temp.I, temp.S2);
      if (feof(data)) break;
      size++;
   }
   return size;
}


//function to read file contents into an array of structs
int readFileToStruct(struct myStruct x[]) 
{
	FILE *stream;
	stream = fopen("hw3.data", "r");

	if (stream == NULL ) 
		{
		exit(0);
		}
	
	int currentElement;
	currentElement = 0;
			
	
	while (fscanf(stream, "%s %f %d %s", 
	x[currentElement].S1,
	&x[currentElement].F, 
	&x[currentElement].I, 
	x[currentElement].S2) == 4)

	{	
	currentElement += 1;
	}
	
	fclose(stream);
	
	return currentElement; 
}

//function to sort int high
void sortInt(struct myStruct arrMyStruct[], int n) 
{
	int x, y;
	struct myStruct z; 
	
	for (x = 0; x < n-1; x++)
	{
		for (y = 0; y < n-x-1; y++)
		{
			if (arrMyStruct[y].I < arrMyStruct[y+1].I) 
			{ 
				z = arrMyStruct[y]; 
				arrMyStruct[y] = arrMyStruct[y+1]; 
				arrMyStruct[y+1] = z;
			}
		}
	}
}


//function to sort float high
void sortFloat(struct myStruct arrMyStruct[], int n) 
{
	int x, y;
	struct myStruct z; 
	
	for (x = 0; x < n-1; x++)
	{
		for (y = 0; y < n-x-1; y++)
		{
			if (arrMyStruct[y].F < arrMyStruct[y+1].F) 
			{ 
				z = arrMyStruct[y]; 
				arrMyStruct[y] = arrMyStruct[y+1];
				arrMyStruct[y+1] = z;
			}
		}
	}
}


//Function to print int or float high-low
void printHigh(struct myStruct arrMyStruct[], int n) 
{
	int p; 
	
	for (p = 0; p < n; p++) 
	{
		printf("%s %f %d %s\n", arrMyStruct[p].S1, arrMyStruct[p].F, arrMyStruct[p].I, arrMyStruct[p].S2); 
	}
}


//Function to print int or float low-high
void printLow(struct myStruct arrMyStruct[], int n) 
{
	int p;
	
	for (p = n-1; p >= 0; p--) 
	{
		printf("%s %f %d %s\n", arrMyStruct[p].S1, arrMyStruct[p].F, arrMyStruct[p].I, arrMyStruct[p].S2); 
	}
}



int main(void)
{
int choice;
int numElements;
int size;
struct myStruct *arrMyStruct;
//struct myStruct arrMystruct[100];

	size = getSize();
	arrMyStruct = (struct myStruct *)malloc(size * sizeof(struct myStruct));


	while (1) 
	{

		printf("1. Sort data by float - print high to low\n"
				"2. Sort data by float - print low to high\n"
				"3. Sort data by int - print high to low\n"
				"4. Sort data by int - print low to high\n"
				"5. Exit\n");
		printf("\n");
		
		scanf("%d", &choice); 
		
		if (choice == 5)
		{
			exit(0); 
		}


		numElements = readFileToStruct(arrMyStruct);
		
		
		if (choice == 1)
		{
			sortFloat(arrMyStruct, numElements);
			printHigh(arrMyStruct, numElements);
			printf("\n");
		}
			
		if (choice == 2)
		{
			sortFloat(arrMyStruct, numElements);
			printLow(arrMyStruct, numElements);
			printf("\n");
		}
			
		if (choice == 3)
		{
			sortInt(arrMyStruct, numElements);
			printHigh(arrMyStruct, numElements);
			printf("\n");
		}
			
		if (choice == 4)
		{	
			sortInt(arrMyStruct, numElements);
			printLow(arrMyStruct, numElements);
			printf("\n");
		}
	}
free(arrMyStruct);
return 0;
}



