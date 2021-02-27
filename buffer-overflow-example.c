#include <stdio.h>
#include <stdlib.h>

void function(void) {

char string1[5], string2[1];
	
	printf("Enter test for string 1: ");
	scanf("%s", string1);
	
	printf("Enter text for string 2: ");
	scanf("%s", string2);
	
	printf("%s\n", string1);
	printf("%s\n", string2);
}

/****************************************************/
/* Test cases:                                      */
/* 12345 & abcde                                    */
/* 1234567890123456789012345678901234567890 & abcde */
/* 12345 & abcdefghijkhlmnoqrst                     */
/****************************************************/

int main(void) {
	function();
	return 0;
}
