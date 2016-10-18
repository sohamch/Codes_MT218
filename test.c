#include <stdio.h>
#include <stdlib.h>

void main(){ /* name no other function as main. it gets compiled first */
// float i=5,j=3;
//	double sum,difference,remainder,quotient;
	//sum = i+j;
	//difference = i-j;
	//quotient  = i/j;
	//remainder = i%j;
	//printf(" sum %le \n difference %le \n quotient %.2le \n remainder %le \n" ,sum,difference,quotient,remainder);
		
//loops
	int i=0,fact = 1;
	int num =0;
	printf ("enter number \n");
	scanf ("%d",&num);
   for (i=num;i>=1;i--)
   {
	   fact = fact*i;
   }
   printf ("\n factorial %d = %d \n",num,fact);
}
