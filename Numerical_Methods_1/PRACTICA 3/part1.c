/* Interpolació de Lagrange:
 
Donats n+1 punts del pla (xi, fi) , i = 0,1,2,...,n amb totes les abscisses xi diferents entre si, volem determinar un
polinomi p(x) de grau menor o igual a n tal que p(xi) = fi , i = 0,1,2,...,n

Per obtenir aquest polinomi :

1. Resolució del sistema lineal:
Si escrivim el polinomi p com a p(x) = a0 + a1(x) +···+ an(x)^n , llavors, imposant les condicions d’interpolació,        el problema es pot plantejar com resoldre el sistema Ma = f. Crearem una funció on avalu el polinomi en un punt per mitjà de la regla de Horner, amb l'ajuda de la pràctica 2 resoldrem el sistema i veurem per mitjà de la funció horner que cada  abcisa que hem llegit , avaluada en el polinomi dona exactament la seva ordenada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double horner(int, double*, double);
void triang (int, double**, double*, int);
int lu (double**, int, int*, double);

int main (void){
	int n,i, j, permutacions, *perm;
	double *x, *f,**L, **M, tol=1e-8, *vec;

	/* Llegim n per determinar els n+1 punts del pla i el polinomi interpolador de gran <=n*/

	printf("DONA'M EL GRAU DEL POLINOMI (n+1) punts\n");
	scanf("%d", &n);
	n=n+1;	
	
	/*Creem dos vectors per poder llegir els punts, un vector per xi i l altre per fi i = 0,1,...,n */

	x = (double*)malloc(n*sizeof(double));

		if(x==NULL){
			printf("Error al guardar memòria per x\n");
			exit(1);
		}

	f = (double*)malloc(n*sizeof(double));

                if(f==NULL){
                        printf("Error al guardar memòria per f\n");
                        exit(1);
                }
		
		/* VECTOR AMB EL QUE PERMUTAREM EL VECTOR DE TERMES INDEPENDENTS fi del sistema al fer la factorització LU */

	 perm = (int*)malloc(n*sizeof(int));

                if(perm==NULL){
                        printf("Error al guardar memòria per perm\n");
                        exit(1);
                }

	/* Vector que utilitzo per a canviar les files amb el vector permutació i posteriorment per conservar els valors  	     de fi per avaluar el polinomi en Horner ja que f es modifica al llarg del programa */

	 vec = (double*)malloc(n*sizeof(double));

                if(vec==NULL){
                        printf("Error al guardar memòria per vec\n");
                        exit(1);
                }


	/*Llegim els vectors x i f respectivament */

	printf("DONA'M ELS %d PUNTS\n", n);
	for(i=0;i<n;i++)
		scanf("%le %le", &x[i], &f[i]);

	 for(i=0;i<n;i++){
                vec[i]=f[i];
        }


	/*Ara generarem la matriu Ma = M per poder resoldre el sistema Ma=f amb el programa de la pràctica 2*/

	/*Guardem memòria per Ma, matriu nxn */

	M = (double**)malloc(n*sizeof(double*));

		if(M==NULL){
			printf("Error al guardar memòria per M\n");
			exit(1);
		}

	for(i=0;i<n;i++){
	
		M[i]=(double*)malloc(n*sizeof(double));

		if(M[i]==NULL){
			printf("Error al guardar memòria per M\n");
			exit(1);
		}
	}

	/*Generem M a partir de les xi */

	for(i=0;i<n;i++)
		M[i][0]=1;

	for(i=0;i<n;i++){
		for(j=1;j<n;j++){
			M[i][j]=x[i]*M[i][j-1];
		}
	}
	
	 /*IMPRIMIM LA MATRIU M PER VEURE QUE L'HEM GENERAT CORRECTAMENT */

        printf("\nM\n\n");

        for(i=0; i<n; i++){
                for(j=0; j<n; j++){
                        printf("%15.8le    ", M[i][j]);
                }
                printf("\n");
        }

	/* Factorització LU*/
	permutacions = lu (M, n, perm, tol);
	
	if (permutacions==(-1)){
		printf("No s'ha pogut fer descomposició LU\n");
		exit (1);
	}

	/*IMPRIMIM LA FACTORITZACIÓ LU*/

	printf("\nFactorització LU\n\n");
	
	for(i=0; i<n; i++){
                for(j=0; j<n; j++){
                        printf("%15.8le    ", M[i][j]);
                }
                printf("\n");
        }
	printf("\n");

	/*PRIMER RESOLDREM EL SISTEMA Ly=Pb*/
	/*Creearé una matriu L triangular inferior que la igualaré a M i li posaré 1's a la diagonal*/

	L=(double**)malloc(n*sizeof(double*));

                if(L==NULL){
                        printf("No s'ha pogut guardar memòria correctament\n");
                        exit(1);
                }
        for(i=0; i<n; i++){
                L[i]= (double*)calloc(i+1,sizeof(double));
                        if(L[i]==NULL){
                                printf("No s'ha pogut guardar memòria correctament\n");
                                exit(1);
                        }
        }

	for(i=0;i<n;i++){
		for(j=0;j<i;j++){
			L[i][j]=M[i][j];
			}

		L[i][i]=1;

		}

	/*ESCRIVIM L PER SABER QUE L'HEM GENERAT CORRECTAMENT */

	printf("L\n\n");

	 for(i=0; i<n; i++){
                for(j=0; j<=i; j++){
                        printf("%15.8le    ", L[i][j]);
                }
                printf("\n");
        }

	 /*Abans de fer aquest pas hem d'intercanviar totes le files dels termes independents de forma corresponent*/
	
	/* Crearé un vector el que igualaré a f per intercanviar les components com indica el vector permutació*/

	for(i=0;i<n;i++){
		if(perm[i]!=i){
			f[i]=vec[perm[i]];
		}
	}

	printf("\n");
	printf("Vector Fi permutat\n");
	for(i=0;i<n;i++){
		printf("%15.8le  ", f[i]);
	}
	printf("\n\n");

	printf("Ly=Pb\n");

	triang(n, L, f, -1);

	for(i=0;i<n;i++){
		printf("%15.8le  ", f[i]);
	}
	printf("\n");
  	 
	/*Ara resoldrem el sistema Ux=y*/

	printf("\nUx=y\n\n");
	
	triang(n,M,f,1);
	
	/*Aquests hauren de ser els coeficients del polinomi interpolador*/

	for(i=0;i<n;i++){
                printf("%15.8le  ", f[i]);
        }

	printf("\n\n permtutacions = %d\n\n", permutacions);

	printf("\nOrdenades de les abcisses evaluades en el polinomi per Horner\n\n");

	for(i=0;i<n;i++){
		horner(n-1,f,vec[i]);
		printf("%15.8le  ", vec[i]);
	}
	printf("\n");

return 0;
}

double horner(int n, double *a, double z){
		int i;
		double y;

		y = a[n];
		for(i=n-1;i>=0;i--)
			y=y*z+a[i];
					
return y;
}

int lu (double **a, int n, int *perm, double tol){
	int i, j, vecaux, k, imax, canvi=0;
        double max, *aux, abs;

        /* *aux es el vector que pivota les files de la matriu*/

         /* Generarem el vector perm perm[0]=0,...,perm[n-1]=n-1 */

        for(i=0;i<n;i++){
                perm[i]=i;
        }


        /*Tecnicament tenim n-1 passos pero fem k<n perque em de comprovar que a[n-1][n-1] és diferent de 0 */

        for(k=0; k<n;k++){
                max=0;
                imax=k;
        for(i=k; i<n; i++){
                abs=fabs(a[i][k]);
                if(abs > max) {
                        max = abs;
                        imax = i;

                }
        }

        /*Intercanviem files i,k si s'escau */


	if(imax!=k) {

                /*Pivotem P, j és el valor auxiliar*/
                vecaux = perm[k];
                perm[k] = perm[imax];
                perm[imax] = vecaux;

                /*Pivotem les files de a */
                aux = a[k];
                a[k] = a[imax];
                a[imax] = aux;
                canvi++;
                }

                if(max<tol) return -1; /*Matriu degenerada*/


		for(i=k+1; i<n; i++){
                	a[i][k]=a[i][k]/a[k][k];
				
			for(j=k+1; j<n; j++) {
                                        a[i][j] = a[i][j] - a[i][k]*a[k][j];
                               	     	}
                        }

	  }

	  
 	return canvi;
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
			break;

		case 1: /*el sistema serà triangular superior, el resolem per substitució cap enrera*/
                        
			for(i=n-1; i>=0; i--){
                                suma = 0.;
                                for(j=n-1; j>i ; j--){
                                        suma += matA[i][j]*b[j];
                                        }
                                b[i] = (b[i]-suma)/matA[i][i];
                                }
			break;

		case -1: /*el sistema serà triangular inferior amb 1's a la diagonal*/
			for(i=0; i<n; i++){
                                suma = 0;
                                for(j=0; j<i; j++){
                                        suma+= matA[i][j]*b[j];
				} 
                                b[i] = b[i]- suma;
                                }
			break;
		}
	}
