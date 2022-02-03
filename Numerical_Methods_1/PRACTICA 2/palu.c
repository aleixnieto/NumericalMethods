/* Escriurem una funció que calculi la factoritzacio PA=LU d’una matriu donada A de dimensio n×n, usant eliminacio gaussiana amb pivotatge maximal per columnes, la matriu L és        la matriu que obtenim amb els multiplicadors que es creen en l'eliminació gaussiana, té 1's a l diagonal i si permutem la matriu A en qualsevol pas, la matriu L també permuta de filesper tant la matriu L serà triangular inferior. La matriu U és la matriu que ens queda al final un cop feta l'eliminació gaussiana, per tant serà triangular superior */
/*Què és el pivotatge maximal per columnes? En el pas k de l'eliminació gaussiana cal buscar l'element de la columna k més gran en magnitud, és a dir en valor absolut, per tal de     miniminitzar l'error en l'arrodoniment a l'hora de fer l'eliminació gaussiana, max |aik^(k)|=|ark|, (i=k,...,n), aleshores si r=k fem eliminació gaussiana, contrariament intercanviem les files i,k i fem el pas d'eliminació gaussiana */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void triang (int, double**, double*, int);
int lu (double**, int, int*, double);

int main (void){

/*Llegirem la matriu A, i a la sortida guardarem la descomposició LU en la mateixa A, per sota de la diagonal guardarem   els multiplicadors (L) i en la resta la matriu esglaonada de l'eliminacio gaussiana (U), un cop feta eliminació gaussiana per trobar els valors de x resoldrem dos sistemes, el priemr Ly=Pb on obtindrem y i P es la matriu de permutacions que    generarem a partir del vector perm, u cop obtinguda la y resoldrem el sistema Ux=y i trobarem x, el primer el resoldrem amb tipus -1 i el segon amb tipus 1 en la funcio triang*/
/* (perm) és el vector on es retorna la permutacio de files de A: ∀i = 0,..,n−1, la fila i de PA es la fila perm[i] de A*/
	
	int i, j, n, m, permutacions, *perm;
	double **L, suma=0, **a, **coef, tol= 1e-8, *suprem, max=0, *piv, *vec;
	char nom1[50],nom2[50];
	FILE *entrada, *sortida;
	
	/* LLEGEIM EL FITXER D'ENTRADA */

	printf("Introdueix el nom del fitxer de lectura\n");
	scanf("%s",nom1); /*No fa falta & */

	entrada = fopen(nom1,"r");
   
	if(entrada==NULL){
      		printf("Error de lectura\n");
      		exit(1);
   	}

	/*OBRIM EL FITXER DE SORTIDA*/

        printf("Introdueix el nom del fitxer de sortida\n");
        scanf("%s",nom2);

        sortida = fopen(nom2,"w");

        if(sortida==NULL){
                printf("Error de lectura\n");
                exit(1);
        }

  	
   	/* Llegim n */
   
	printf("Dona'm n\n");
	scanf("%d", &n);
	
	/* Llegim m */
	printf("Dona'm m\n");
	scanf("%d", &m);

	/*Guardem memòria per a les matrius (nxn) dels sistemes lineals i (mxn) de termes independents */
	/* A l'enunciat ens diu que la matriu de coeficients ha de ser nxm pero la llegeixo mxn perquè es molt mes facil a l hora de passar files per resoldre el sistema amb la funcio           que resol matrius triangulars*/

	a= (double**)malloc(n*sizeof(double*));

		if(a==NULL){
			printf("No s'ha pogut guardar memòria correctamentx\n");
			exit(1);
		}
	for(i=0; i<n; i++){
		a[i]= (double*)calloc(n,sizeof(double));
			if(a[i]==NULL){
				printf("No s'ha pogut guardar memòria correctamenty\n");
				exit(1);
			}
	}

	coef= (double**)malloc(n*sizeof(double*));

                if(coef==NULL){
                        printf("No s'ha pogut guardar memòria correctamentz\n");
                        exit(2);
                }
        for(i=0; i<n; i++){
                coef[i]= (double*)calloc(m,sizeof(double));
                        if(coef[i]==NULL){
                                printf("No s'ha pogut guardar memòria correctament\n");
                                exit(2);
                        }
        }

	/*Llegim la matriu nxn de sistemes lineals */

   	for (i=0; i<n; i++){
		for(j=0; j<n; j++){
			fscanf(entrada, "%le", &a[i][j]);
		}
   	}	

	/*Llegim la matriu nxm de termes independents*/
   
  	for (i=0; i<n; i++){
	 	for (j=0; j<m; j++){
			fscanf(entrada, "%le", &coef[i][j]);
	  	}	
  	}

	 /*Guardem memòria per al vector de les permutacions */

        perm= (int*)malloc(n*sizeof(int));

                if(perm==NULL){
                        printf("No s'ha pogut guardar memòria correctament\n");
                 	exit(4);
                }

	/*Aquí calculem el suprem de la matriu dels sistemes perquè sinó després modifiquem la matriu inicual per la factorització lu*/
	
	/* Crearé un vector per veure la suma dels elements de cada fila i d'aqui extreure'n el suprem */

      	suprem= (double*)malloc(n*sizeof(double));

	if(suprem==NULL){
                        printf("No s'ha pogut guardar memòria correctament\n");
                        exit(3);
             }

		for(i=0; i<n; i++){
	        	suma=0;
	              	for(j=0; j<n; j++){
	                	suma+= fabs(a[i][j]);
	                    	}
	           	suprem[i] = suma;
	       	}
		
		for(i=0; i<n; i++){
			if(suprem[i]>max){
			max=suprem[i];
			}
		}


	/* FEM LA FACTORITZACIÓ LU*//* L'ESCRIUREM EN EL FITXER */

	permutacions= lu(a, n, perm, tol);

	 for(i=0; i<n; i++){
                for(j=0; j<n; j++){
                        fprintf(sortida, " %le   ", a[i][j]);
                }
                fprintf(sortida,"\n");
        }
	 fprintf(sortida,"\n\n");
		
	 /*RESOLEM ELS M SISTEMES*/	
	 /*PRIMER RESOLDREM EL SISTEMA Ly=Pb*/
	/*Creearé una matriu L triangular inferior que la igualaré a A i li posaré 1's a la diagonal*/

	vec=(double*)malloc(n*sizeof(double*));

	if(vec==NULL){
		printf("Error al guardar memòria per vec\n");
		exit(1);
	}

	L=(double**)malloc(n*sizeof(double*));

                if(L==NULL){
                        printf("No s'ha pogut guardar memòria correctamentx\n");
                        exit(1);
                }
        for(i=0; i<n; i++){
                L[i]= (double*)calloc(i+1,sizeof(double));
                        if(L[i]==NULL){
                                printf("No s'ha pogut guardar memòria correctamenty\n");
                                exit(1);
                        }
        }

	for(i=0;i<n;i++){
		for(j=0;j<i;j++){
			L[i][j]=a[i][j];
			}

		L[i][i]=1;

		}

	 for(i=0; i<n; i++){
                for(j=0; j<=i; j++){
                        fprintf(sortida, " %le   ", L[i][j]);
                }
                fprintf(sortida,"\n");
        }

	 fprintf(sortida,"\n\n");

	/*Abans de fer aquest pas hem d'intercanviar totes le files dels termes independents de forma corresponent*/
	
	for(i=0;i<n;i++){
		if(perm[i]!=i){
		piv = coef[i];
                coef[i] = coef[perm[i]];
                coef[perm[i]] = piv;
                 }
	}


	for(i=0; i<m; i++){

		  for(j=0;j<n;j++)
                        vec[j]=coef[j][i];

		triang(n, L, vec, -1);
		
		  for(j=0;j<n;j++)
                        coef[j][i]=vec[j];

		}

	  for(i=0; i<n; i++){
                for(j=0; j<m; j++){
                        fprintf(sortida, " %le   ", coef[i][j]);
                }
                fprintf(sortida,"\n");
	  }
	  fprintf(sortida,"\n\n");

	/*Ara resoldrem el sistema Ux=y*/

	  for(i=0; i<m; i++){

                  for(j=0;j<n;j++)
                        vec[j]=coef[j][i];
	
		  triang(n,a,vec,1); /*AQUÍ ESTA EL PUTO ERROR*/
                        			   
		  for(j=0;j<n;j++){
			coef[j][i]=vec[j];
			}
                }
	
	/*IMPRIMIM LA MATRIU NXM DE SOLUCIONS */

	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			fprintf(sortida, " %le   ", coef[i][j]);
		}
		fprintf(sortida,"\n");
	}
	fprintf(sortida,"\n\n");
	
	fprintf(sortida, "\nPermutacions = %d", permutacions);
	fprintf(sortida, "\nLa norma del suprem de la matriu dels sistemes és %le", max);

	/*Calculem la norma del suprem */

	 for(i=0; i<n; i++){
                        suma=0;
                        for(j=0; j<m; j++){
                                suma+= fabs(coef[j][i]);
                                }
                        suprem[i] = suma;
                }

                for(i=0; i<n; i++){
			if(suprem[i]>max){
                        max=suprem[i];
                        }
                }
		
	fprintf(sortida, "\nLa norma del suprem de la matriu de solucions és %le", max);

	return 0;

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
				
				for(j=k+1; j<=n; j++) {
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

		case 1: /*el sistema serà triangular superior, el resolem per substitució cap enrera*/
                        for(i=n-1; i>=0; i--){
                                suma = 0;
                                for(j=n-1; j>=i ; j--){
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
                                b[i] = b[i]- suma;
                                }
		}
	}







