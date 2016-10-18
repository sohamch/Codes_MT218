#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MESHX 500
#define MESHY 500

int status[MESHX][MESHY];


void main ()
{
	long x,y;
	for (x=0;x<MESHX;x++)
	{
		for (y=0;y<MESHY;y++)
		{
			status[x][y] = 0; // 1 denotes solid, 0 liquid
		}
	}
	for (x=0;x<MESHX;x++)
	{
		for (y=0;y<=1;y++)
		{
			status[x][y] = 1; // we make every point upto y=1 solid.
		}
	}
	
	 
	 int ymax=10; //ymax = starting distance from the y co-ordinate of the farthest solidified point in the y direction.
	 double rv;
	
	while (ymax<(MESHY-1))
	{
		//we start from a random point in the x-direction and which is atleast ymax units away from the last solidified point in the y direction.
		x = floor(drand48()*500);
		y = ymax; 
			
		while (status[x][y]==0)
		{
			rv = drand48();
			if ((rv>=0)&&(rv<=0.25))
			{
				x++;
			}
			if ((rv>0.25)&&(rv<=0.5))
			{
				x--;
			}
			if ((rv>0.5)&&(rv<=0.75))
			{
				y++;
			}
							
			if ((rv>0.75)&&(rv<=1))
			{
				y--;
			}
			if (x<0)
			{
				x=x+MESHX;
			}
			if (x>MESHX-1)
			{
				x=x-MESHX;  // a point that leaves the box from one vertical side (x=0/x=meshx) enters through the other vertical side(x=meshx/x=0).
			}
			if (y>MESHY-1) 
				break;
			//if y crosses MESHY, then we discard it and start from another random point 
			//(we cannot use PBC in this case as the base is fixed)						
				
			if ((x>0)&&(x<MESHX-1)&&(y>0)&&(y<MESHY-1)&&((status[x+1][y]==1) || (status[x-1][y]==1) || (status[x][y-1]==1)))
			{
				status[x][y] = 1;
			}
		}
		if (status[x][y] == 1 && y<MESHY-1 ) // second check is to ensure that the first loop ended normally and not because of the break statement
				ymax = y+10; // shifting ymax to 10 from the furthest solidified point (the next random walker approaches from further 10 units away)
	}	
	FILE *fp;
	fp = fopen ("solid.dat","w");
	
		for (x=0;x<MESHX;x++)
		{
			for (y=0;y<MESHY;y++)
			{
				fprintf(fp,"%ld %ld %d\n",x,y,status[x][y]);
			}
			fprintf(fp,"\n");
		}
	
	fclose (fp);
}
