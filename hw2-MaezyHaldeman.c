//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

	//initializes a blank structure
	struct myStruct {
	char S1[20];
	float F;
	int I;
	char S2[20];
	};
	

//function to read file contents into an array of structs
int readFileToStruct(struct myStruct x[]) //takes an array of myStructs
{
	FILE *stream;
	stream = fopen("hw2.data", "r");

	if (stream == NULL ) 
		{
		exit(0);
		}
	
	int currentElement;
	currentElement = 0;
			
	//reads contents of file into individual elements of the struct
	while (fscanf(stream, "%s %f %d %s", 
	x[currentElement].S1,
	&x[currentElement].F, 
	&x[currentElement].I, 
	x[currentElement].S2) == 4)

	{	
	currentElement += 1;
	}
	
	fclose(stream);
	
	return currentElement; //returns the number of elements in the array of myStructs
}

//function to sort int high
void sortInt(struct myStruct arrMystruct[], int n) //takes the array of structs and number of elements
{
	int x, y, z; //placeholders for reordering the array of structs
	
	for (x = 0; x < n-1; x++)
	{
		for (y = 0; y < n-x-1; y++)
		{
			if (arrMystruct[y].I < arrMystruct[y+1].I) //comparing int values of the elements of the array of structs
			{ 
				z = arrMystruct[y].I; //reordering the array of structs by int value
				arrMystruct[y].I = arrMystruct[y+1].I; 
				arrMystruct[y+1].I = z;
			}
		}
	}
}


//function to sort float high
void sortFloat(struct myStruct arrMystruct[], int n) //takes the array of structs and number of elements
{
	int x, y, z; //placeholders for reordering the array of structs
	
	for (x = 0; x < n-1; x++)
	{
		for (y = 0; y < n-x-1; y++)
		{
			if (arrMystruct[y].F < arrMystruct[y+1].F) //comparing float values of the elements of the array of struct
			{ 
				z = arrMystruct[y].F; //reordering the array of structs by float value
				arrMystruct[y].F = arrMystruct[y+1].F;
				arrMystruct[y+1].F = z;
			}
		}
	}
}


//Function to print int or float high-low
void printHigh(struct myStruct arrMystruct[], int n) //takes the array of structs and number of elements
{
	int p; 
	
	for (p = 0; p < n; p++) //traversing the array of structs from the first (highest) value
	{
		printf("%s %f %d %s\n", arrMystruct[p].S1, arrMystruct[p].F, arrMystruct[p].I, arrMystruct[p].S2); //printing in high to low order
	}
}


//Function to print int or float low-high
void printLow(struct myStruct arrMystruct[], int n) //takes the array of structs and number of elements
{
	int p;
	
	for (p = n-1; p >= 0; p--) //traversing the array of structs from the last (lowest) value
	{
		printf("%s %f %d %s\n", arrMystruct[p].S1, arrMystruct[p].F, arrMystruct[p].I, arrMystruct[p].S2); //printing in low to high order
	}
}



int main(void)
{
int choice;
int numElements;
struct myStruct arrMystruct[100];

	while (1) //infinite loop to display menu until user chooses option 5
	{

		printf("1. Sort data by float - print high to low\n"
				"2. Sort data by float - print low to high\n"
				"3. Sort data by int - print high to low\n"
				"4. Sort data by int - print low to high\n"
				"5. Exit\n");
		printf("\n");
		
		scanf("%d", &choice); //reads user's menu choice
		
		if (choice == 5)
		{
			exit(0); //exits infinite loop
		}


		numElements = readFileToStruct(arrMystruct);
		
		
		if (choice == 1)
		{
			sortFloat(arrMystruct, numElements);
			printHigh(arrMystruct, numElements);
			printf("\n");
		}
			
		if (choice == 2)
		{
			sortFloat(arrMystruct, numElements);
			printLow(arrMystruct, numElements);
			printf("\n");
		}
			
		if (choice == 3)
		{
			sortInt(arrMystruct, numElements);
			printHigh(arrMystruct, numElements);
			printf("\n");
		}
			
		if (choice == 4)
		{	
			sortInt(arrMystruct, numElements);
			printLow(arrMystruct, numElements);
			printf("\n");
		}
	}

return 0;
}



