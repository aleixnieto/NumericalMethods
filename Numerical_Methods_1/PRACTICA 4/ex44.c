#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double f(double );
double df(double );
int newton(double, int, double *, double);
int main(void){
	int it_max, result;
	double x0, sol, tol; 
	
	
	printf("Dona'm (x0, tol i el nombre màxim d'iteracions:\n");
   	scanf("%le %le %d", &x0, &tol, &it_max);

   	result = newton(x0, it_max, &sol, tol);
   	switch(result){
   		case 0:
      			printf("Hi ha hagut convergència \n");
      			printf("x = %17.10le\n", sol);
      			printf("f(x) = %17.10le\n", f(sol));
      			break;
   		case 1:
     			printf("S'ha arribat al màxim d'iteracions sense tenir convergència\n");
      			break;
   		case 2:
      			printf("La derivada s'anul·la\n");
      			break;
   		default:
			break;
	}
   return 0;
} 	

int newton(double x0, int it_max, double *sol, double tol){
   int i;
   double x1;

   x1 = x0 - f(x0)/df(x0);
   
   	for(i = 1; i <= it_max && fabs(x1 - x0) >= tol && fabs(f(x1)) >= tol && fabs(df(x1)) >= tol; i++){
		x0 = x1;
		x1 = x0 - f(x0)/df(x0);
	}

   	if(i > it_max){
      		return 1;
   	}	
   
  	 if(fabs(df(x1)) < tol){
      		return 2;
   	}	

   	*sol = x1;

	printf("Ha convergit en %d iteracions\n", i);
   		
	
	return 0;
}	

double f(double x){

        return log(x)-x*x+4*x-4;
}

double df(double x){

        return -2*x +1/x +4;
}


