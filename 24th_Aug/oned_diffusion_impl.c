#include <stdio.h>
#include <stdlib.h>

#define MESHX 1000

#define ntime 20000
#define deltat 0.1
#define deltax 1.0
#define saveT 100

// #define DIRICHLET
#define NEUMANN
#ifdef DIRICHLET
 #define const_back 0.5
 #define const_front 0.5
#endif

//#define thomas
//define GS_RB
#define jacobi

void apply_bc();
void update (double *c_new, double *c_old);
void writetofile (FILE *fp, double *c);
void initialize(double *c);


void main (){
	long x,t,iter;
	double c_old[MESHX+2];
	double c_new[MESHX+2];
	double c_k[MESHX+2];
	
	double a[MESHX+1];
	double b[MESHX+1];
	double c[MESHX+1];
	double d[MESHX+1];
	
	double inv_deltax2 = 1.0/(deltax*deltax);
	char filename[1000];
	FILE *fp;
	
	double alpha = inv_deltax2*deltat;
	
	initialize (c_old);
	
	for (t=0;t<ntime;t++)
	{
		//create_matrix
		d[1] = c_old[0] + alpha*c_old[1];
		a[1] = 0.0;
		b[1] = 1+2*alpha;
		c[1] = -alpha;
		for (x=2;x<MESHX+1;x++)
		{
			a[x] = -alpha;
			b[x] = 1+2*alpha;
			c[x] = -alpha;
			d[x] = c_old[x];
	    }
	    c[MESHX]  = 0.0;
	    d[MESHX] = c_old[MESHX] + alpha*c_old[MESHX+1];
	    
#ifdef thomas
	    //transform_matrix (forward)
	    for (x=2;x<=MESHX;x++)
	    {
	    b[x] = -c[x-1]*a[x]/b[x-1] + b[x];
	    d[x] = -d[x-1]*a[x]/b[x-1] + d[x];
		}
		
		//backward_subst
		c_old[MESHX] = d[MESHX]/b[MESHX];
		for(x=MESHX-1;x>=1;x--)
		{
			c_old[x] = (d[x] - c[x]*c_old[x+1])/b[x];
		}
#endif
#ifdef GS_RB
//ODD_UPDATE
for(iter=0;iter<=10;iter++)
{
	for(x=1;x<=MESHX; x+=2)
	{
		c_old[x] = (d[x] - a[x]*c_old[x-1] - c[x]*c_old[x+1])/b[x];
	}
//EVEN_UPDATE
	for(x=2;x<=MESHX; x+=2)
	{
		c_old[x] = (d[x] - a[x]*c_old[x-1] - c[x]*c_old[x+1])/b[x];
	}
}	
#endif
#ifdef jacobi
long iter;
update(c_old,c_k);
for(iter=0;iter<10;iter++)
 { 
	for(x=1;x<MESHX+1; x++)
	{
		c_old[x] = (d[x] - a[x]*c_k[x-1] - c[x]*c_k[x+1])/b[x];
	}
	update(c_old,c_k);
 }
#endif
	    if (t%saveT == 0){
		sprintf(filename,"composition%ld.dat", t);
		fp=fopen (filename,"w");
		writetofile (fp, c_old);
		fclose (fp);
	    }
     
  }
}
void initialize(double *c)
{
 long x;
  for (x=0 ; x<(MESHX+2)/2; x++)
  {
	  c[x] = 0.1;
  }
  for (x=(MESHX+2)/2; x<MESHX+2; x++)
  {
	  c[x] = 0.5;
  }
}
void update (double *c_new, double *c_old)
{
long x;
for (x=0;x<MESHX+1;x++)
{
	c_old[x] = c_new[x];
}
}

void writetofile (FILE *fp, double *c) 
{
 long x;
 for (x=1;x<=MESHX;x++)
 {
		fprintf (fp, "%le %le\n",x*deltax, c[x]);
 }	
}
