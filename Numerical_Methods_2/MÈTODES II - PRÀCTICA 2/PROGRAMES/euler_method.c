/*Programa que resol mitjançant el mètode d'Euler, que és un mètode numèric de primer ordre, una equació diferencial ordinària amb un valor conegut a la frontera dins d'un interval [a,b] fixat*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double f(double,double);

int main(void){
	double a, b, x0, y0, y, h;
	int n, i;
	FILE *sortida;
	char sor[30];

	/* Sabem que 4*atan(1)= PI */
	/* Setejem els següents valors de a a, b, x0, y0, n ja que són els que utilitzarem durant tota la pràctica i no se'ns demana llegir-los per pantalla*/
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
	
	/*Algorisme del mètode d'Euler, on busquem y a partir de la iteració y0, com la primera ja la sabem es pot procedir a calcular els valors de y a punts equidistants entre a i b */

	for(i=0;i<n;i++){
		y = y0 + h*f(x0, y0);
		y0 = y;
		x0 = x0 + h;
		fprintf(sortida,"%22.16le\n",  y);
	}	
	
	fclose(sortida);

return 0;
}
