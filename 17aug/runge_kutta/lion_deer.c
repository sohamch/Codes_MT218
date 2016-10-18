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
		FILE *fp1, *fp2, *fp3;
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
	//RUNGE-KUTTA	
		fp3 = fopen ("RG4.dat","w");
		x=init_x;
		y=init_y;
		double x_tilde1,x_tilde2,x_tilde3,y_tilde1,y_tilde2,y_tilde3;
		double dxdt1, dxdt2, dxdt3, dxdt4;
		double dydt1, dydt2, dydt3, dydt4;
		for (t=0; t< TOTAL_TIME ; t++)
		{
			
			dxdt = alpha*x - beta*x*y;
			dydt = delta*x*y - gama*y;
			
			x_tilde1 = x + dxdt * deltat/2;
			y_tilde1 = y + dydt * deltat/2;
			
			dxdt1 = alpha*x_tilde1 - beta*x_tilde1*y_tilde1;
			dydt1 = delta*x_tilde1*y_tilde1 - gama*y_tilde1;
			
			x_tilde2 = x + dxdt1*deltat/2;
			y_tilde2 = y + dydt1*deltat/2;
			
			dxdt2 = alpha*x_tilde2 - beta*x_tilde2*y_tilde2;
			dydt2 = delta*x_tilde2*y_tilde2 - gama*y_tilde2;
			
			x_tilde3 = x + dxdt2*deltat;
			y_tilde3 = y + dydt2*deltat;
			
			dxdt3 = alpha*x_tilde3 - beta*x_tilde3*y_tilde3;
			dydt3 = delta*x_tilde3*y_tilde3 - gama*y_tilde3;
			
			dxdt4 = (2*dxdt1 + 2*dxdt2+ dxdt3 + dxdt)/6;
			dydt4 =  (2*dydt1 + 2*dydt2+ dydt3 + dydt)/6;
			
			x += dxdt4 * deltat;
			y += dydt4 * deltat;
			
			
			fprintf (fp2,"%le %le\n", x, y);
		}
		fclose (fp3);

}














