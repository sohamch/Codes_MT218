#include <stdio.h>
#include <stdlib.h>

#define TOTAL_TIME 5 //look up this syntax
#define deltat_exp 0.01
#define deltat_imp 0.01
#define deltat_pc 0.01
#define TOT_ITER 10
void main () {
	
		double x_exp[TOT_ITER];
		double x_imp[TOT_ITER]; 
		double x_pc[TOT_ITER];
		int t;
		double x_pc_pred;
		FILE *fp1, *fp2, *fp3;
		x_exp[0] = 0.0;
		x_imp[0] = 0.0;
		x_pc[0] = 0.0;
		
		fp1 = fopen ("Exponential_expl.dat","w");
		fp2 = fopen ("Exponential_imp.dat","w");
		fp3 = fopen ("Exponential_pc.dat","w");
		
		for (t=0;t<TOT_ITER-1;t++){
			//explicit
			x_exp[t+1]  = x_exp[t] + (2*x_exp[t] +3 )*deltat_exp;
			//implicit
			x_imp[t+1] = (x_imp[t] + 3*deltat_imp)/(1-2*deltat_imp);
			//predictor_corrector
			//x_pc_pred = (2*x_pc[t]+3)*deltat_pc + x_pc[t] ;
			x_pc[t+1] = x_pc[t] + (2*(x_pc[t]+((2*x_pc[t]+3)*deltat_pc + x_pc[t])) + 6)*deltat_pc/2;
			fprintf (fp1, "%le %le\n", (t+1)*deltat_exp, x_exp[t+1]);
			fprintf (fp2, "%le %le\n", (t+1)*deltat_imp, x_imp[t+1]);
			fprintf (fp3, "%le %le\n", (t+1)*deltat_pc, x_pc[t+1]); 
			}
			fclose (fp1);
			fclose (fp2);
			fclose (fp3);
}
