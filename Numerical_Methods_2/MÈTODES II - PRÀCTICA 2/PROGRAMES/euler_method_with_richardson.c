/*Mètode d'euler amb un pas d'extrapolació de Richardson (m=1) per q=2*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double f(double,double);

int main(void){
        double a, b, y0, x0, y1, y2,  y, h0;
        int n, i, q=2, j;
        FILE *sortida;
        char sor[30];

        /*Llegim i obrim el fitxer de sortida*/

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
         
	for(i=0;i<n;i++){
		x0 = a;
        	y0 = 1/sqrt(3);
		
	/*Mètode d'euler per h0*/	
		for(j=0;j<(i+1);j++){
			y1 = y0 + h0*f(x0,y0);
               		y0 = y1;
			x0 = x0 + h0;
			}
		
		y0 = 1/sqrt(3);
		x0 = a;
	/*Mètode d'euler per h1=h0/2*/
		for(j=0;j<(2*(i+1));j++){
			y2 = y0 + (h0/q)*f(x0,y0);
			y0 = y2;
			x0 = x0 + h0/q;
			}	
		
	/*Apliquem l'algorisme (1) de Richardson de la pràctica*/
	y = y2 + (y2 - y1) / (q - 1);

	fprintf(sortida,"%22.16le\n", y);
	}
        
	fclose(sortida);

return 0;
}

