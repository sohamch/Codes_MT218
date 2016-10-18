#include <stdio.h>
#include <stdlib.h>

#define xrange (1.0)
#define yrange (1.0)

#define NRAM 40000000

void main ()
{
	double x,y;
	
	long accept=0;
	long iter;
	
	for (iter=0;iter<NRAM;iter++)
	{
		x= -1.0 + xrange*(drand48());
		y= -1.0 + yrange*(drand48());
		
		if ((x*x+y*y)<=1.0)
		{
			accept++;
		}
	}
	printf("pi = %le\n",(double)(accept)/(double)(NRAM)*4.0);
}
