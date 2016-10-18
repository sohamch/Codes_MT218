#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NJUMPS 100
#define NSEQUENCES 1000

void main ()
{
	long x[NSEQUENCES][NJUMPS];
	long y[NSEQUENCES][NJUMPS];
	
	long i, j, seed;
	double rv;
	double rand;
	
	printf("Enter seed\n");
    scanf("%ld",&seed);	
	
	for (i=0; i < seed; i++)
	{
		rv = drand48();
	}
	
	for (i=1;i<NSEQUENCES;i++)
	{
		x[i][j] = 0;
		y[i][j] = 0;
		
		for (j=1;j<NJUMPS;j++)
		{
			rv = drand48();
			if ((rv>=0) && (rv<=0.25))
			{
				x[i][j] = x[i][j-1] + 1;
				y[i][j] = y[i][j-1];
			}
			if ((rv>0.25) && (rv<=0.5))
			{
				x[i][j] = x[i][j-1] - 1;
				y[i][j] = y[i][j-1];
			}
			if ((rv>0.5) && (rv<=0.75))
			{
				x[i][j] = x[i][j-1];
				y[i][j] = y[i][j-1] + 1;
			}
			if ((rv>0.75) && (rv<=1))
			{
				x[i][j] = x[i][j-1];
				y[i][j] = y[i][j-1] -1;	
			}
		
		}
	
	}
	double av_r2mean;
	FILE *fp;
	
	fp = fopen ("r2mean.dat","w");
	
	for (j=1;j<NJUMPS;j++)
	{
		av_r2mean = 0;
		for (i=1;i<NSEQUENCES;i++)
		{
			av_r2mean += x[i][j]*x[i][j] + y[i][j]*y[i][j];
		}		
	    av_r2mean /=NSEQUENCES;
	    fprintf(fp,"%ld %le\n", j, av_r2mean);
	}
	fclose(fp);
}

