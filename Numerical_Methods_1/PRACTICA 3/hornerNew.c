#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double hornerNew (int, double*, double*, double);

double hornerNew (int n , double *b , double *x , double z){
	int i;
	double y;
	
	y=b[n];

	for(i=n-1;i>=0;i--)
		y=y*(z-x[i])+b[i];


	return y;
}
