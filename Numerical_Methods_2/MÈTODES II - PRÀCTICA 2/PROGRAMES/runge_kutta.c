/* Mètode de runge_kutta, on es calcula una aproximació de y al punt xn +h  mitjançant la combinació de diversos punts estratègics a l'interval (xn, xn + h). Aquest mètode es caracteritza per tenir un error de truncament d'ordre h⁴ */
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double f(double,double);

int main(void){
        double a, b, x0, y0, y, h, k1, k2, k3, k4;
        int n, i;
        FILE *sortida;
        char sor[30];

        /* Sabem que 4*atan(1)= PI */

        a = (4*atan(1))/6;
        b = (4*atan(1))/3;
	x0 = a;
        y0 = 1/sqrt(3);
        
	n = 10;
        h = (b-a)/n;

        /*Llegim el nom i obrim el fitxer de sortida*/

        printf("Dona'm el nom del fitxer on vols imprimir les dades\n");
        scanf("%s", sor);

        sortida = fopen(sor, "w");
        if(sortida == NULL){
                printf("No s'ha pogut obrir el fitxer\n");
                exit(1);
        }
	
	/* Algorisme de Runge-Kutta */

        for(i=0;i<n;i++){
		k1 = h*f(x0,y0);
		k2 = h*f(x0 + 0.5*h, y0 + 0.5*k1);
		k3 = h*f(x0 + 0.5*h, y0 + 0.5*k2);
		k4 = h*f(x0 + h, y0 + k3);

                y = y0 + (1./6.)*(k1 +2*k2 + 2*k3 + k4);
                y0 = y;
                x0 = x0 + h;
                fprintf(sortida,"%22.16le\n", y);
        }

        fclose(sortida);

return(0);
}

