/* Donada una funció f (x) definida en un interval fitat [a, b], volem calcular la integral entre a i b de f(x)
Dos fórmules per a calcular una aproximació de I(f) són la fórmula dels trapezis T(h) i la fórmula de Simpson composta S(h). */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double trapezis (double, double, int);
double Simpson (double, double, int);
double f(double);
double integralf(double, double);

int main(void){
	
	double tol, a, b;
	int n;

	printf("Dona'm a, b per integrar la funció en l'integral [a,b]\n");
	scanf("%le %le", &a, &b);

	printf("Dona'm la tolerància\n");
	scanf("%le", &tol);

	/*És un for buit ja que quan s'assoleixi la condició sortirà directament i llavors aquell sera el valor de T(h) i S(h) respectivament*/
	
	for(n=1;fabs(integralf(a, b)-trapezis(a,b,n))>=tol;n++){}
	
	printf("Valor integral(Th):%23.15le  Intervals:%d \n", trapezis(a,b,n), n);

	for(n=1;fabs(integralf(a, b)-Simpson(a, b, n))>=tol;n++){}

	printf("Valor integral(Sh):%23.15le  Intervals(2n):%d \n",Simpson(a,b,n), 2*n);

return 0;
}

double trapezis (double a, double b, int n){
	double valor,h;
	int i;

	h=(b-a)/(double)(n);

	valor=f(a)/2;
	
	for(i=1;i<n;i++){
		valor+=f(a+(i*h));
	}
	valor+=f(b)/2;
	valor=valor*h;

return valor;
}

double Simpson (double a, double b, int n){
	double valor, h;
	int i;

	h=(b-a)/(double)(2*n);
	
	valor=f(a);

	for(i=1;i<2*n;i++){
		if(i%2==0){
                	valor+=2*f(a+(i*h));
		}else{
			valor+=4*f(a+(i*h));
        	}
	}

	valor+=f(b);
	valor=valor*(h/3);

	return valor;
}

#include <math.h>
#include <stdio.h>
double f(double x){

        return 1/(1+x);
}

double devf(double x){

        return -1/((1+x)*(1+x));
}

double integralf(double a, double b ){

        return (log(fabs(b+1))-log(fabs(a+1)));


}
