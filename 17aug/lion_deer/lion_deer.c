#include <stdio.h>
#include <stdlib.h>

#define TOTAL_TIME 100000
#define deltat 0.0001
#define init_x 5
#define init_y 5
#define alpha 4
#define beta 2
#define delta 3
#define gama 4

void main (){
		//double x[TOTAL_TIME], y[TOTAL_TIME];
		FILE *fp1, *fp2;
		fp1 = fopen ("Explicit.dat","w");
		
		double dxdt;
		double dydt;
		int t;
		double x=init_x,x_tilde;
		double y=init_y,y_tilde;
	
	//EXPLICIT
		for (t=0; t< TOTAL_TIME ; t++)
		{
			
			dxdt = alpha*x - beta*x*y;
			dydt = delta*x*y - gama*y;
			
			x += dxdt * deltat;
			y += dydt * deltat;
			fprintf (fp1,"%le %le\n", x, y);
		}
		fclose (fp1);
		
	//PREDICTOR_CORRECTOR
		fp2 = fopen ("pred_corr.dat","w");
		x=init_x;
		y=init_y;
		for (t=0; t< TOTAL_TIME ; t++)
		{
			
			dxdt = alpha*x - beta*x*y;
			dydt = delta*x*y - gama*y;
			
			x_tilde = dxdt * deltat;
			y_tilde= dydt * deltat;
			
			dxdt += alpha*x_tilde - beta*x_tilde*y_tilde;
			dydt += delta*x_tilde*y_tilde - gama*y_tilde;
			
			x += 0.5*dxdt*deltat;
			y += 0.5*dydt*deltat;
			
			fprintf (fp2,"%le %le\n", x, y);
		}
		fclose (fp2);
}
