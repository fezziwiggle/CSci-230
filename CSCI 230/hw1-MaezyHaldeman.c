
//Maezy Haldeman: maezy.haldeman@und.edu
// CSCI 230: HW 1

#include <stdlib.h>
#include <stdio.h>

int main(void) {

float r, B, P, I, PI, T;
int month;

r = 0.25;
B = 2000.0;
P = 0.0;
I = 0.0;
PI = 0.0;
T = 0.0;
month = 1;



    /*program statements*/
    printf("Enter your monthly payment: ");
    scanf("%f", &P);
    
    printf("Interest rate = %.2f\n", r);
    printf("Amount borrowed = %.2f\n", B);
    printf("Monthly payment = %.2f\n", P);
    
    if (month == 1) 
    {
    	I = (r/12)*B;
    	PI = I;
    	
    	printf("%d: %.2f | %.2f\n", month, I, B);
    	
    	T = T + I;
    	
    	month++;
    }
    
    
    if (month != 1)
    {
    	while (B >= 0)
    	{
    	    I = (r/12)*(B-P+PI);
    	    
    	    B = B-P+PI;
    	    
            PI = I;

    	    printf("%d: %.2f | %.2f\n", month, I, B);
    	    
            if (I >= 0) {
    	      T = T + I;
    	    }
    	    
    	    month++;
    	}
    }
    
    printf("Total interest paid: %.2f\n", T); 
    

    
    
    return 0;
}
