#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void dif_div (int, double*, double*);


void dif_div (int n , double *x , double *f ){
	int i, k;



	for(k=1; k<n+1;k++){
		for(i=n; i>=k; i--){
			f[i] = (f[i] -f[i-1])/(x[i]-x[i-k]);
			}
		}
	return;
	}
