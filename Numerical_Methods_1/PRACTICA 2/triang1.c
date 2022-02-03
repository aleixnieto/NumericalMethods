/* fem una funció que resol un sistema no singular de dimensió n amb matriu matA i terme independent b
la variable tipus indica el tipus de sistema: 
0 triangular inferior
1 triangular superior
-1 triangular inferior amb 1's a la diagonal
el vector solució es guarda en b*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void triang (int, double**, double*, int);
int main (void){
	int tipus, i, j, n;
	double *b;
	double **matA;
	printf("Dona la dimensió de la matriu que introduiràs després\n");
	scanf("%d", &n);
	/*Comprovem que la dimensió de la matriu és superior a 0*/
	while (n<=0) {
		printf("Torna a introduir la dimensió de la matriu\n");
		scanf("%d", &n);
		}
	printf("Especifica el tipus de matriu que introduiràs:\n posa un 1 si la matriu serà triangular superior,\n 0 si serà triangular inferior i\n -1 si serà triangular inferior amb 1s a la diagonal\n");
	scanf("%d", &tipus);
	/*comprovem que el numero llegit sigui 1, 0 o -1 i sino tornem a demanar que especifiquin el tipus de matriu*/
	while(tipus!=1 && tipus!=0 && tipus!=-1){
		printf("Si us plau torna a introduir el tipus\n");
		scanf("%d", &tipus);
		}
	/*guardem memòria per a la matriu*/
	matA = (double**) malloc (n*sizeof(double*));
	/*comprovem que s'ha pogut guardar memòria per a la matriu*/
	if (matA==NULL) {
		printf("No hi ha prou memòria\n");
		exit(1);
		}
	if (tipus == 1){
		/*guardem memòria per a una matriu triangular superior*/
		for(i=0; i<n; i++){
			matA[i] = (double*) calloc (n-i, sizeof(double));
			if(matA[i] == NULL){
				printf("No hi ha prou memòria\n");
				exit (1);
				}
			}
		} else {
		/*guardem memòria per a una matriu triangular inferior*/
		for(i=0; i<n; i++){
			matA[i] = (double*) calloc (i+1, sizeof(double));
			if(matA[i] == NULL){
				printf("No hi ha prou memòria\n");
				exit(1);
				}
			}
		}
	/*guardem memòria per al vector de termes independents*/
	b = (double*) malloc (n*sizeof(double));
	if (b==NULL){
		printf("No hi ha prou memòria\n");
		exit(1);
		}
	/*llegim la matriu matA (nomes els numeros de la diagonal cap amunt (si és superior) o de la diagonal cap abaix(si es inferior)*/
	printf("Dona la matriu matA del sistema d'equacions\n");
	if(tipus == 1){
		/*llegim la matriu si és superior*/
		for (i=0; i<n; i++){
			for(j=0; j<n-i; j++){
				scanf("%le", &matA[i][j]);
				}
			}
		} else {
		/*llegim la matriu si és inferior*/
		for(i=0; i<n; i++){
			for(j=0; j<i+1; j++){
				scanf("%le", &matA[i][j]);
				}
			}
		}
	/*llegim el vector de termes independents*/		
	printf("Dona al vector de termes independents\n");
	for(i=0; i<n; i++){
		scanf("%le", &b[i]);
		}
	/*calculem el vector solució mitjançant la funció triang*/
	triang(n, matA, b, tipus);
	/*ara podem alliberar memòria per a matA*/
	for(i=0; i<n; i++){
		free(matA[i]);
		}
	free(matA);
	/*tenim les solucions guardades al vector b i les imprimim per pantalla*/
	printf("Les solucions del sistema són:\n");
	for( i=0; i<n; i++){
		printf("x%d = %12.5le\n", i+1, b[i]);
		}
	/*alliberem memòria per a b*/
	free(b);

	return 0;	

}

void triang (int n, double **matA, double *b, int tipus){
	int i, j;
	double suma;
	/* com que la matriu és singular, determinant serà diferent de 0 i tindrà solució*/
	switch(tipus) {
		case 0:/*el sistema serà triangular inferior, el resolem per substitució cap endavant*/ 
			for(i=0; i<n; i++){
				suma = 0;
				for(j=0; j<i; j++){
					suma+= matA[i][j]*b[j];	
					}
				b[i] = (b[i]-suma)/matA[i][i];
				}
		case 1: /*el sistema serà triangular superior, el resolem per substitució cap enrera*/
			for(i=n-1; i>=0; i--){
				suma = 0;
				for(j=1; j<n-i ; j++){
					suma += matA[i][j]*b[j+i];
					}
				b[i] = (b[i]-suma)/matA[i][0];
				}
		case -1: /*el sistema serà triangular inferior amb 1's a la diagonal*/
			for(i=0; i<n; i++){
                                suma = 0;
                                for(j=0; j<i; j++){
                                        suma+= matA[i][j]*b[j];
                                        }
                                b[i] -= suma;
                                }
		}
	}
