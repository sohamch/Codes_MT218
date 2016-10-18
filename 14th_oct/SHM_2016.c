#include <stdio.h>
#include <stdlib.h>

#define m 1.0
#define k 1.0

#define deltat 0.01
#define ntimesteps 10000

//#define trivial
#define verlet
//#define mod_verlet
//#define leapfrog

void main ()
{
	int t;
	double x[ntimesteps];
	double v[ntimesteps];
	double a[ntimesteps];
	
	FILE *fp;
	
#ifdef trivial
	fp  = fopen ("shm_trivial.dat","w");
	x[0] = 0;
	v[0] = 1;
	
	for (t=0;t<ntimesteps-1;t++)
	{
		x[t+1] = x[t] + v[t]*deltat + 0.5*(-k*x[t]/m)*deltat*deltat;
		v[t+1] = v[t] + a[t]*deltat;
		fprintf (fp, "%le %le %le\n" , t*deltat, x[t+1], v[t+1]);
	}
	fclose (fp);
#endif

#ifdef verlet
	x[0] = 0;
	v[0] = 1;
	fp  = fopen ("shm_verlet.dat","w");
	
	double x_old = x[0] - v[0]*deltat + 0.5*(-k*x[0]/m)*deltat*deltat; //going back in time from x=0 gives 	
	
	for (t=1;t<ntimesteps-1;t++)
	{
		if(t==0)
		{
			x[t+1] = 2*x[t] - x_old + (-k*x[t]/m)*deltat*deltat;
		}
		else
		{
			x[t+1] = 2*x[t] - x[t-1] + (-k*x[t]/m)*deltat*deltat;
		}
		fprintf (fp, "%le %le %le\n" , t*deltat, x[t+1], v[t+1]);
	}
	fclose (fp);
#endif

#ifdef mod_verlet
	fp  = fopen ("shm_modverlet.dat","w");
	x[0] = 0;
	v[0] = 1;
	
	for (t=1;t<ntimesteps-1;t++)
	{
		
			x[t+1] = x[t] +v[t]*deltat + 0.5*(-k*x[t]/m)*deltat*deltat;
			v[t+1] = v[t] + 0.5*(-k*(x[t]+x[t+1])/m)*deltat;
	        fprintf (fp,"%le %le %le\n" , t*deltat, x[t+1], v[t+1]);		
	}
	fclose (fp);
#endif

#ifdef leapfrog
	fp  = fopen ("leapfrog.dat","w");
    x[0] = 0;
	v[0] = 1;
	
	double v_old = v[0] - 0.5*(-k*x[t]/m)*deltat;
	
	for (t=0;t<ntimesteps-1;t++)
	{
		if(t==0)
		{
			v[t+1] = v_old + (-k*x[t]/m)*deltat;
		}
		else
		{
			v[t+1] = v[t] + (-k*x[t]/m)*deltat;	
		}
		x[t+1]= x[t] + v[t+1]*deltat;
		fprintf (fp,"%le %le %le\n" , t*deltat, x[t+1], v[t+1]);
	}
	fclose (fp);
#endif	
}

