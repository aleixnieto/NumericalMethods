#include <stdio.h>
#include <math.h>

int main (void) {

	double TOL, polinomi, successio, x;
	int i=1;

	printf("Dona'm el valor de x\n");
	scanf("%le", &x);

	polinomi = 1 + x;
	successio = x;
	TOL = fabs (exp(x) - polinomi);
	
	printf("Grau                Exp(x)              Valor_polinomi            Error absolut\n");
	printf("%d                   %le        %le              %le\n", i, exp(x), polinomi, TOL);
	
	for(i=2; TOL>=1e-8; i++){

	successio = successio*(x/(double)i);
	polinomi = polinomi + successio;
	TOL = fabs(exp(x) - polinomi);
	
	printf("%d                   %le        %le              %le\n", i, exp(x), polinomi, TOL);

	}

	printf("S'ha necessitat arribar a un polinomi de Taylor de grau %d per obtenir una tolerància menor que 1e-8\n", i-1);
	
 return 0;
}
