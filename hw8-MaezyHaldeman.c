//Maezy Haldeman: maezy.haldeman@und.edu
//CSCI 230: HW 8

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct _node {
	char *word;
	struct _node *next;
};

struct _codex {
	char *word1; 
	char *word2;
	struct _codex *next;
};


int SCAN(int fileChoice) { //will return the num of lines in whichever file we are reading			
char *buffer = NULL; //buffer is the string containing the characters of a line in the file
size_t bufSize = 0;
ssize_t fileLine;

int size = 0;

FILE *stream;
	
	if (fileChoice == 1) {
		stream = fopen("hw8data.txt", "r");
	}
	
	else if (fileChoice == 2) {
		stream = fopen("hw8codex.txt", "r");
	}

	while (1) {

     		buffer = NULL;
     		getline(&buffer, &bufSize, stream);
     		free(buffer);
     		if (feof(stream)) break;
     		size++;
  	}
   	return size;
}

void DATALIST(struct _node *(*dataHead), int size) {

char *buffer = NULL; //buffer is the string containing the characters of a line in the file
size_t bufSize = 0;
ssize_t fileLine;

int i;
int j;


FILE *stream;

	stream = fopen("hw8data.txt", "r");
	
	struct _node *current;
	current = (struct _node*)malloc(sizeof(struct _node));
	
	(*dataHead) = current;
	
	for (i = 0; i < size; i++) { //for every line in the file
	
		getline(&buffer, &bufSize, stream);
	
		char *wordTok;
		wordTok = strtok(buffer, " "); //gets the first word in the line	
		
		while (wordTok != NULL) { //gets the other words in the line
		
			// is wordTok grabbing the carriage returns too?
			
			int tokLen;
			
			tokLen = strlen(wordTok);
			
			if (strcmp(&wordTok[tokLen - 2], ",\n") == 0) { //if the word to add has a comma in it
				
				char *subTok1;
				char *subTok2;
				
				subTok1 = strtok(wordTok, ",");
				strcpy(subTok2, ",");
				
				current->word = (char*)malloc(strlen(subTok1) + 1); //
				strcpy(current->word, subTok1);
				
				current->next = (struct _node*)malloc(sizeof(struct _node)); //allocate next node
				current = current->next;
				
				current->word = (char*)malloc(strlen(subTok2) + 1);
				strcpy(current->word, subTok2);
			}
			
			else if (strcmp(&wordTok[tokLen - 2], ".\n") == 0) { //if the word to add has a period in it
				
				char *subTok1;
				char *subTok2;
				
				subTok1 = strtok(wordTok, ".");
				strcpy(subTok2, ".");
				
				current->word = (char*)malloc(strlen(subTok1) + 1);
				strcpy(current->word, subTok1);
				
				current->next = (struct _node*)malloc(sizeof(struct _node)); //allocate next node
				current = current->next;
				
				current->word = (char*)malloc(strlen(subTok2) + 1);
				strcpy(current->word, subTok2);			
			}
			
			
			else {
				current->word = (char*)malloc(strlen(wordTok) + 1);
				strcpy(current->word, wordTok);
			}
			
			
			wordTok = strtok(NULL, " ");
			
		
			current->next = (struct _node*)malloc(sizeof(struct _node)); //allocate next node
			current = current->next;
			
		}
	}
	fclose(stream);
}



void CODEXLIST(struct _codex *(*codexHead)) {

char *buffer = NULL; //buffer is the string containing the characters of a line in the file
size_t bufSize = 0;
ssize_t fileLine;

FILE *stream;

	stream = fopen("hw8codex.txt", "r");
	
	struct _codex *current;
	current = (struct _codex*)malloc(sizeof(struct _codex));
	
	(*codexHead) = current;
	
	while ((fileLine = getline(&buffer, &bufSize, stream)) != -1) {

		char *tok1;
		char *tok2;
	
		tok1 = strtok(buffer, " "); //gets the first word in the line
		tok2 = strtok(NULL, "\n"); //gets the second word in the line
		
		current->word1 = (char*)malloc(strlen(tok1) + 1);
		current->word2 = (char*)malloc(strlen(tok2) + 1);
		
		strcpy(current->word1, tok1);
		strcpy(current->word2, tok2);
		
		current->next = (struct _codex*)malloc(sizeof(struct _codex)); //allocate next node
		current = current->next;
		
	}
	
	fclose(stream);
}
		
	
void SPELLCHECK(struct _node *(*dataHead), struct _codex *(*codexHead)) {

int i = 0;

	struct _node *dataCurrent;
	dataCurrent = (struct _node*)malloc(sizeof(struct _node));
	dataCurrent = (*dataHead);
	
	struct _codex *codexCurrent;
	codexCurrent = (struct _codex*)malloc(sizeof(struct _codex));
	
	struct _node *obsoleteNode;
	obsoleteNode = (struct _node*)malloc(sizeof(struct _node));
	
	
	while (dataCurrent->next->word != NULL) { //start traversing the data list //FOR SOME REASON there is a (null) node at the end of both linked lists which is not being considered == NULL, hence wacky while condition. why is this happening???
	
		codexCurrent = (*codexHead);
		
		while (codexCurrent->next != NULL) { //traverse the codex list for each word in data list
		
				
			if (dataCurrent == (*dataHead) && strcmp(dataCurrent->word, codexCurrent->word1)) {//if we are replacing the first data list node
			
			struct _node *newNode;
			newNode = (struct _node*)malloc(sizeof(struct _node));
				
				obsoleteNode = dataCurrent; //save the node we are replacing so we can free it
				
				newNode->word = (char*)malloc(strlen(codexCurrent->word2) + 1); //allocate memory for our node with the replacement word
				strcpy(newNode->word, codexCurrent->word2); //throw the replacement word into our new node
				
				(*dataHead) = newNode;
				newNode->next = dataCurrent->next;
				
				free(obsoleteNode); //we can now free the node we've un-linked
				
				i++;
				break;
			}
			
			else if (strcmp(dataCurrent->next->word, codexCurrent->word1) == 0) { //we've found the location right before the node we are replacing
			
			struct _node *newNode;
			newNode = (struct _node*)malloc(sizeof(struct _node));
			
				if (strcmp(codexCurrent->word2, "skip") == 0) {
					obsoleteNode = dataCurrent->next;
					
					dataCurrent->next = dataCurrent->next->next;
					
					free(obsoleteNode);
				}
			
				else {
					obsoleteNode = dataCurrent->next;
					
					newNode->word = (char*)malloc(strlen(codexCurrent->word2) + 1);
					strcpy(newNode->word, codexCurrent->word2);
					
					newNode->next = obsoleteNode->next;
					dataCurrent->next = newNode;
					
					free(obsoleteNode);
				}
								
				i++;
				break;
			}
			codexCurrent = codexCurrent->next;
		}
		dataCurrent = dataCurrent->next;
	}
}


void PRINTDATA(struct _node *(*dataHead)) {

	struct _node *temp;
	
	temp = (*dataHead);
		
	while (temp->word != NULL) {
		
		if (strcmp(temp->word, ",") == 0 || strcmp(temp->word, ".") == 0) {
			printf("%s", temp->word);
		}
		
		else {		
			printf(" %s", temp->word);
		}
		temp = temp->next;
	}
}


void PRINTCODEX(struct _codex *(*codexHead)) {

	struct _codex *temp;
	
	temp = (*codexHead);
	
	printf("\nhw8codex.txt:\n");
	
	while (temp->word1 != NULL) {
		printf("%s %s\n", temp->word1, temp->word2);
		temp = temp->next;
	}
}



int main(void) {

int dataSize;
int codexSize;

	struct _node *dataHead;
	dataHead = NULL;
	
	struct _codex *codexHead;
	codexHead = NULL;
	
	dataSize = SCAN(1);
	codexSize = SCAN(2);

	DATALIST(&dataHead, dataSize);
	CODEXLIST(&codexHead);
	
	printf("\nhw8data.txt\n");
	PRINTDATA(&dataHead);
	//PRINTCODEX(&codexHead);
	
	SPELLCHECK(&dataHead, &codexHead);
	
	printf("\nhw8data.txt (spellchecked)\n");
	PRINTDATA(&dataHead);





return 0;
}


