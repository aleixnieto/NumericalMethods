/* Interpolació de Lagrange:
 
Donats n+1 punts del pla (xi, fi) , i = 0,1,2,...,n amb totes les abscisses xi diferents entre si, volem determinar un
polinomi p(x) de grau menor o igual a n tal que p(xi) = fi , i = 0,1,2,...,n

Per obtenir aquest polinomi:

2.Mètode de les diferències dividides de Newton:
En aquest cas escrivim el polinomi p com a p(x) = b0 + b1 (x − x0) + b2(x − x0)(x − x1) +···+ bn(x − x0)·...·(x − xn−1),  i calculem les diferències dividides, definides de forma recurrent. Crearem una funció on donats dos vectors (x,f) un amb les   xi i un altre amb les fi, ens omplirà el vector f amb les diferències dividides. Guardarem aquesta funció en un fitxer    de nom difDiv.c. Escriurem una altra funció hornerNew que, donats els vectors x i b, que contenen xi i les diferències    dividides respectivament, avalua el polinomi interpolador en un punt z, usant la regla de Horner. Guardarem la funció en  un fitxer de nom hornerNew.c. */

/* PER EXECUTAR EL PROGRAMA COMPILEM TOTS ELS ARXIUS X SEPARAT I gcc part2.o difDiv.o hornerNew.o -o part2.exe -lm */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void dif_div (int, double*, double*);
double hornerNew (int, double*, double*, double);


int main(void){


 	int n,i;
	double *x, *f, valor,*b;

        /* Llegim n per determinar els n+1 punts del pla i el polinomi interpolador de gran <=n*/

        printf("DONA'M EL GRAU DEL POLINOMI (n+1) punts\n");
        scanf("%d", &n);
       
	n=n+1;

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

	/* CREEM UN VECTOR B PERQUÈ AIXÍ AL FINAL CONSERVEM EL VECTOR f PER PODER COMPROVAR QUE LES Xi EVALUADES EN EL POLINOMI INTERPOLADOR DONEN LES fi */

	 b = (double*)malloc(n*sizeof(double));

                if(b==NULL){
                        printf("Error al guardar memòria per f\n");
                        exit(1);
                }

        /*Llegim els vectors x i f respectivament */

        printf("Dona'm els punts (Xi, Fi) i=0,...,%d\n", n-1);
        for(i=0;i<n;i++)
                scanf("%le %le", &x[i], &f[i]);

	 for(i=0;i<n;i++)
                b[i]=f[i];

	/* OBTENIM ELS COEFICIENTS DEL POLINOMI INTERPOLADOR */
	 
        dif_div (n,x,b);

	printf("Els coeficients del polinomi interpolador són:\n");

	for(i=0;i<n;i++){
		printf("%15.8le  ", b[i]);

	}

	printf("\n");

	printf("%5s %12s %12s\n", "i", "p(xi)", "fi");

	for(i=0; i<n; i++){
		/* n-1 ja que s'ha d'introduir el grau del polinomi i a l'inici del programa hem fet n=n-1 */
		valor = hornerNew(n-1, b, x, x[i]);
		printf("%5d %12.5le %12.5le\n", i, valor, f[i]);
		}

	printf("\n");

return 0;
}
