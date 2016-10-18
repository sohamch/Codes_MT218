#include <stdio.h>
#include <stdlib.h>
 void main () {
 FILE *fp ;
 fp = fopen ("data.dat","w");
 double arr[1000];
 int k;
 int sum;
 for (k=0;k<1000;k++)
 	{
 	arr[k] = k+1;
	}
 for (k=0;k<500;k++)
	{
		sum +=arr[k] + arr[999-k];
		fprintf (fp,"%d\n",sum);
	}
 fclose (fp);
}

// this file is ok!!!!
