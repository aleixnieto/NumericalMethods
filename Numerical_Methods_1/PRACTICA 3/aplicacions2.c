/*Observarem el fenòmen de Runge amb el mètode de les diferencies dividides de Newton, ja que és millor que resolent el sistema*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void dif_div (int, double*, double*);
double hornerNew (int, double*, double*, double);


int main(void){

 	int n,i;
	double h, error, *x, *f,*b;
	char nom2[50];
	FILE *sortida;
        /* Llegim n per determinar els n+1 punts del pla i el polinomi interpolador de gran <=n*/

        printf("DONA'M EL GRAU DEL POLINOMI (n+1) punts\n");
        scanf("%d", &n);

	n=n+1;

	/*OBRIM EL FITXER DE SORTIDA*/

        printf("Introdueix el nom del fitxer de sortida\n");
        scanf("%s",nom2);

        sortida = fopen(nom2,"w");

        if(sortida==NULL){
                printf("Error de lectura\n");
                exit(1);
        }


        /*Creem dos vectors per poder llegir els punts, un vector per xi i l altre per fi i = 0,1,...,n */

        x = (double*)malloc(n+sizeof(double));

                if(x==NULL){
                        printf("Error al guardar memòria per x\n");
                        exit(1);
                }

        f = (double*)malloc(n*sizeof(double));

                if(f==NULL){
                        printf("Error al guardar memòria per f\n");
                        exit(1);
                }

	 b = (double*)malloc(n*sizeof(double));

                if(b==NULL){
                        printf("Error al guardar memòria per f\n");
                        exit(1);
                }

	/*Creem els punts xi equiespaiats a l'interval [-1,1] */

	h=2/((double)(n-1));

		for(i=0;i<n;i++){
			x[i]=(-1+(h*i));
			f[i]=1/(1+25*x[i]*x[i]);
		}


      for(i=0;i<n;i++)
                b[i]=f[i];

	/*Calculo els coeficients del polinomi interpolador */

        dif_div (n,x,b);


	for(i=0;i<n;i++){
                       fprintf(sortida, "%15.8le %15.8le %15.8le %15.8le\n", x[i], f[i], x[i],  hornerNew(n-1,b,x,x[i]));
                }


	/*Error en 0.6 */

	error= 1/(1+(25*((0.6)*(0.6)))) - hornerNew(n-1,b,x,0.6);

	printf("Error per x=0.6 : %le\n", error);
	
	/*Error en 0.8 */

	error= 1/(1+(25*((0.8)*(0.8)))) - hornerNew(n-1,b,x,0.8);

        printf("Error per x=0.8 : %le\n", error);

return 0;
}

