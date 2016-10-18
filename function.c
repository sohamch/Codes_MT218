#include <stdio.h>
#include <stdlib.h>
 void main () {
 FILE *fp ;
 fp = fopen ("data.dat","w");
 int k;
 int sum;
 for (k=0;k<500;k++)
	{
		sum +=arr[k] + arr[999-k];
		fprintf (fp,"%d\n",sum);
	}
 fclose (fp);
}
int add () {
	 double arr[1000];
	 int k;
	 for (k=0;k<1000;k++)
 	 {
		arr[k] = k+1;
	 }
	 for (k=0;k<500;k++)
	{
		sum +=arr[k] + arr[999-k];
		//fprintf (fp,"%d\n",sum);
	}
	return sum;
}

