/* fem una funció que resol un sistema no singular de dimensió n amb matriu matA i terme independent b
la variable tipus indica el tipus de sistema:
0 triangular inferior
1 triangular superior
-1 triangular inferior amb 1's a la diagonal
el vector solució es guarda en b*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define PI 4*atan(1)
void triang (int, double**, double*, int);
int main (void){
	FILE *sortida;
	char nom[50];
	int i, j, limit, n;
	double *b, angle;
	double **matA, secs;
	clock_t t_ini, t_fin;

	printf("Dona la dimensió de la matriu \n");
	scanf("%d", &n);
	
	/*Comprovem que la dimensió de la matriu és superior a 0*/
	
	while (n<=0) {
		printf("Torna a introduir la dimensió de la matriu\n");
		scanf("%d", &n);
		}

	/*Guardem memòria per a la matriu*/
	
	matA = (double**) malloc (n*sizeof(double*));

	if (matA==NULL) {
		printf("No hi ha prou memòria\n");
		exit(1);
		}

	for(i=0; i<n; i++){
		matA[i] = (double*) calloc (n, sizeof(double));
			if(matA[i] == NULL){
				printf("No hi ha prou memòria\n");
				exit (1);
				}
			}
	
	/*Guardem memòria per al vector de termes independents*/

	b = (double*) malloc (n*sizeof(double));
	if (b==NULL){
		printf("No hi ha prou memòria\n");
		exit(1);
		}

	/*APLICACIÓ*/
	/*En aquest cas el tipus serà 1 perquè la matriu és triangular superior*/

	do{
	printf("Dona'm l'angle per resoldre el sistema  Kn(θ)x = e(n)\nAmb aquest angle calcularem el temps d'execució per als diferents valors de n\n");
	scanf("%le", &angle);
	}while(angle<(5*PI)/16 || angle>(PI/2));
	
		/*Aqui creo la matriu de l'aplicació que és triangular superior*/
		matA[0][0]=1;
		for (i=1; i<n; i++){
			matA[i][i]=sin(angle)*matA[i-1][i-1];
				}
		for(j=1;j<n;j++){
			matA[0][j]=-cos(angle);
			}

		for(i=1;i<n;i++){
			for(j=i+1;j<n;j++){
				matA[i][j]=matA[i-1][j]*sin(angle);
			}
		}

		
	/*Creem el vector de termes independents, en aquest cas és e(n)*/
	
	for(i=0;i<n-1;i++){
		b[i]=0;
		}
		b[n-1]=1;
	
	 /*Calculem el vector solució mitjançant la funció triang*/

                triang(n, matA, b, 1);

	/*tenim les solucions guardades al vector b i les imprimim per pantalla*/

	printf("Les solucions del sistema són:\n");
        for( i=0; i<n; i++){
                printf("x%d = %12.5le\n", i+1, b[i]);
                }

	    for(i=0;i<n;i++){
                free(matA[i]);
        }
        free(matA);
        free(b);


	  printf("Dona'm el nom del fitxer de sortida\n");
        scanf("%s", nom);

        sortida=fopen(nom,"w");

        if(sortida==NULL){
                printf("Error al crear el fitxer\n");
                exit(1);
        }


	/*Ara generarem valors aleatoris en l'interval dels angles x fer les gràfiques dels temps en funcions dels angles per a diferents n */
	/*Ara només fem dos gràfiques, per n=60 i n=70, pero podem fer les que volguem*/

	printf("Dona'm una n fins a la cual calcularem el temps d'execució\n");
	scanf("%d", &limit);	
	
	for(n=10;n<=limit;n=n+10){
			
		fprintf(sortida, "%d  ",n); 

		 matA = (double**) malloc (n*sizeof(double*));

        /*comprovem que s'ha pogut guardar memòria per a la matriu*/

        if (matA==NULL) {
                printf("No hi ha prou memòria\n");
                exit(1);
                }

        for(i=0; i<n; i++){
                matA[i] = (double*) calloc (n, sizeof(double));
                        if(matA[i] == NULL){
                                printf("No hi ha prou memòria\n");
                                exit (1);
                                }
                        }

        /*guardem memòria per al vector de termes independents*/
        b = (double*) malloc (n*sizeof(double));
        if (b==NULL){
                printf("No hi ha prou memòria\n");
                exit(1);
                }


		matA[0][0]=1;
                
		for (i=1; i<n; i++){
                        matA[i][i]=sin(angle)*matA[i-1][i-1];
                                }
                for(j=1;j<n;j++){
                        matA[0][j]=-cos(angle);
                        }

                for(i=1;i<n;i++){
                        for(j=i+1;j<n;j++){
                                matA[i][j]=matA[i-1][j]*sin(angle);
                        }
                }

		for(i=0;i<n-1;i++){
                b[i]=0;
                }
                b[n-1]=1;

		t_ini = clock();
		triang(n,matA, b, 1);
		t_fin = clock();

		secs = (double)(t_fin-t_ini)/CLOCKS_PER_SEC;

		fprintf(sortida,"%15.7le\n", secs);
		
		     for(i=0;i<n;i++){
                free(matA[i]);
        }
       		free(matA);
        	free(b);
		}

		printf("S'han generat les dades x la gràfica en el fitxer de sortida\n");	


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
				for(j=n-1; j>i ; j--){
					suma += matA[i][j]*b[j];
					}
				b[i] = (b[i]-suma)/matA[i][i];
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
