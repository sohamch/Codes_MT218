#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MESHX 100
#define MESHY 100

#define MCS 5000 //each point atleast once - 1 MC step

#define T (3.0)
#define B (0.0)
#define J (1.0)

#define NUMPOINTS (MESHX*MESHY)
#define saveT 100

int FLAG [MESHX][MESHY];
int spin [MESHX][MESHY];
double compute_DELTAE (int neighbour_sum, int spin_i);
double initialize();

void main ()
{
	long x, y;
	long i; //MCS counter
	int neighbour_sum;
	double rv,avg,ens_avg;
	
	long count;
	double DELTAE;
	initialize();
	
	FILE *fp;
	char filename [1000];
	i=0;
	while (i < MCS)
	{
		for (x=0;x<MESHX;x++)
		{
			for (y=0;y<MESHY;y++)
			{
				FLAG[x][y] = 0;
			}
		}
		count = 0;	
		while (count < NUMPOINTS)
		{
			rv = drand48();
			
			x = (long)floor(NUMPOINTS*rv)/MESHY;
			y = (long)floor(NUMPOINTS*rv)%MESHY;
			
			neighbour_sum = spin[(x+1)%MESHX][y] + spin[(MESHX+x-1)%MESHX][y] + spin[x][(MESHY+y-1)%MESHY] + spin[x][(y+1)%MESHY];
			
			
			
			DELTAE = compute_DELTAE(neighbour_sum,spin[x][y]);
			
			if (DELTAE < 0.0)
			{
				spin[x][y] = -1 + fabs(spin[x][y]-1.0);
			}
			else
			{
				rv = drand48();
				if (rv < exp(-DELTAE/T))
				{
					spin[x][y] = -1 + fabs(spin[x][y]-1.0);
				}
			}
			if (FLAG[x][y] == 0)
			{
				FLAG[x][y] = 1;
				count ++;
			}
			//enter avg calculations
		}
		i++;
		if(i%saveT==0)
		{
			sprintf(filename,"MC_%ld.dat",i);
			fp = fopen (filename, "w");
			for (x=0;x<MESHX;x++)
			{
				for (y=0;y<MESHY;y++)
				{
					fprintf(fp,"%ld %ld %d\n",x,y,spin[x][y]); 
				}
				fprintf(fp,"\n");
			}
			fclose (fp);
		}
		
	}
			
}


double compute_DELTAE(int neighbour_sum, int spin_i)
{
	return (2.0*spin_i*(neighbour_sum -B));
}

double initialize()
{
	long x,y;
	for (x=0;x<MESHX;x++)
		{
			for (y=0;y<MESHY;y++)
			{
				spin[x][y] = -1;
			}
			
		}
}
