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
			
			current->word = (char*)malloc(strlen(wordTok) + 1);
			strcpy(current->word, wordTok);
			
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

		//printf("**%s %s\n", current->word1, current->word2);
		
		current->next = (struct _codex*)malloc(sizeof(struct _codex)); //allocate next node
		current = current->next;
		
	}
	
	fclose(stream);
}
		
	
void SPELLCHECK(struct _node *(*dataHead), struct _codex *(*codexHead)) {

	struct _node *dataCurrent;
	dataCurrent = (struct _node*)malloc(sizeof(struct _node));
	dataCurrent = (*dataHead);
	
	struct _codex *codexCurrent;
	codexCurrent = (struct _codex*)malloc(sizeof(struct _codex));
	
	while (dataCurrent->next != NULL) { //start traversing the data list
	
		codexCurrent = (*codexHead);
		
		while (codexCurrent->next != NULL) { //traverse the codex list for each word in data list
			
			if (strcmp(dataCurrent->word, codexCurrent->word1) == 0) { //we found a matching word in the codex
		
				printf("We will replace %s with %s\n", dataCurrent->word, codexCurrent->word2);
				
				
				
				
				
				
			}
			codexCurrent = codexCurrent->next;
		}
		dataCurrent = dataCurrent->next;
	}
}



void PRINTDATA(struct _node *(*dataHead)) {

	struct _node *temp;
	
	temp = (*dataHead);
	
	printf("\nhw8data.txt:\n");
	
	while (temp != NULL) {
		printf(" %s", temp->word);
		temp = temp->next;
	}
}


void PRINTCODEX(struct _codex *(*codexHead)) {

	struct _codex *temp;
	
	temp = (*codexHead);
	
	printf("\nhw8codex.txt:\n");
	
	while (temp != NULL) {
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
	
	//printf("%s\n", );
	
	dataSize = SCAN(1);
	codexSize = SCAN(2);
	
	//printf("data size: %d\n", dataSize);
	//printf("codex size: %d\n", codexSize);

	DATALIST(&dataHead, dataSize);
	CODEXLIST(&codexHead);
	
	//PRINTDATA(&dataHead);
	//PRINTCODEX(&codexHead);
	
	SPELLCHECK(&dataHead, &codexHead);






return 0;
}


