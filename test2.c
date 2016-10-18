#include <stdio.h>
#include <stdlib.h>
void main ()
{
	// Arrays
	double arr[1000];
	int k;
	int sum;
	for (k=0;k<1000;k++)
	{
		arr[k] = k+1;
	}
	for (k=0;k<1000;k++)
	{
		sum +=arr[k];
	}
	printf ("/n %d",sum);	
}
