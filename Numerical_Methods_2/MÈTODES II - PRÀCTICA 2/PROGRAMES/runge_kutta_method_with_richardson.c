/* Mètode de Runge-Kutta amb un pas d'extrapolació de Richardson */
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double f(double,double);

int main(void){
        double a, b, x0, y0, y1, y2, y, h0, h1, k1, k2, k3, k4;
        int n, i, j, q=2;
        FILE *sortida;
        char sor[30];

        /*Obrim el fitxer de sortida*/

        printf("Dona'm el nom del fitxer on vols imprimir les dades\n");
        scanf("%s", sor);

        sortida = fopen(sor, "w");
        if(sortida == NULL){
                printf("No s'ha pogut obrir el fitxer\n");
                exit(1);

        }

        /* Sabem que 4*atan(1) = PI */

        a = (4*atan(1))/6;
        b = (4*atan(1))/3;
       
       	n = 10;
        h0 = (b-a)/n;
	h1 = h0/q;

        for(i=0;i<n;i++){
                x0 = a;
                y0 = 1/sqrt(3);

                for(j=0;j<(i+1);j++){
                k1 = h0*f(x0,y0);
                k2 = h0*f(x0 + 0.5*h0, y0 + 0.5*k1);
                k3 = h0*f(x0 + 0.5*h0, y0 + 0.5*k2);
                k4 = h0*f(x0 + h0, y0 + k3);

                y1 = y0 + (1/6.)*(k1 +2*k2 + 2*k3 + k4);
                y0 = y1;
                x0 = x0 + h0;
		}

                y0 = 1/sqrt(3);
                x0 = a;

                for(j=0;j<(2*(i+1));j++){
		k1 = h1*f(x0,y0);
                k2 = h1*f(x0 + 0.5*h1, y0 + 0.5*k1);
                k3 = h1*f(x0 + 0.5*h1, y0 + 0.5*k2);
                k4 = h1*f(x0 + h1, y0 + k3);

                y2 = y0 + (1/6.)*(k1 +2*k2 + 2*k3 + k4);
                y0 = y2;
                x0 = x0 + h1;
		}

	/*Aquí pk serà 4 a diferència del mètode d'euler que és 1*/

        y = y2 + (y2 - y1) / (q*q*q*q - 1);

        fprintf(sortida,"%22.16le\n", y);
        }

        fclose(sortida);

return 0;
}

