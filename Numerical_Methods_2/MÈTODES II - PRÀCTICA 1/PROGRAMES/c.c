/*MÈTODE DE SOBRERELAXACIÓ(SOR) PER A GAUSS - SEIDEL ALEIX NIETO JUSCAFRESA*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double norma(double*, double*, int);
double p(double);
double q(double);
double r(double);
double*saveSpace(int);

int main(void){
        int n, i, max_iter, iterats=0;
        double a, b, w, epsilon, h, x, alpha, beta, sum, error, norma2=1, norma1;
        double *u0, *u1, *vecr;
        FILE *sortida;
	char sor[30];

        /*No llegeixo a i b, ja que a la pràctica només utilitzem a = 0 i b = 2*PI, igualo b a 8*atan(1) per no perdre precisió al llegir per pantalla*/

        a = 0;
        b = 8*atan(1);
        printf("L'inverval en el que treballarem és [%4.2f , %4.2f]\n", a, b);

        /*Llegim la dimensió de la matriu d'iteració*/
        printf("Dona'm el nombre de punts a l'interior de l'interval [%4.2f, %4.2f]\n", a, b);
        scanf("%d", &n);
	
	/*Llegim el factor de relaxació w per pantalla*/
	printf("Dona'm omega\n");
	scanf("%le", &w);

        /*Llegim alpha i beta*/
        printf("Dona'm alpha i beta\n");
        scanf("%le %le", &alpha, &beta);


        /*Llegim la tolerància d'error absolut de la solució*/
        printf("Dona'm la precisió amb la que vols efectuar el mètode\n");
        scanf("%le", &epsilon);

        /*LLegim el màxim d'iteracions*/
        printf("Dona'm el màxim d'iteracions\n");
        scanf("%d", &max_iter);

        /*Guardo memòria per r, u0 i u1 amb la funció saveSpace*/

        u1 = saveSpace(n);
        u0 = saveSpace(n);
        vecr = saveSpace(n);

        /*Defineixo h*/

        h=(b-a)/(n+1);

        /* / AQUÍ COMENÇA EL MÈTODE DE SOBRERELAXACIÓ / */

	/*Inicialitzó la iteració inicial a (0,.....,0)*/

        for(i=0; i<n; i++){
                u0[i]=0;
                }

        do{

        for (i = 0; i < n; i++){

        x = a + ((i+1)*h);

        sum = 0;

                if(i==0 || i==(n-1)){
                        if(i==0){
                                sum = (-0.5)*(1 - (h/2)*p(x)) * u0[i+1] + (1+((h*h)/2)*q(x))*u0[i];
                                vecr[i] = h*h*0.5*r(x) + alpha*(0.5)*(1 + (h/2)*p(x));
                        }else{
                                sum = (-0.5)*(1 + (h/2)*p(x)) * u1[i-1] + (1+((h*h)/2)*q(x))*u0[i];
                                vecr[i] = h*h*(0.5)*r(x) + beta*(0.5)*(1 - (h/2)*p(x));
                        }

                }else{

                        sum =  -(0.5)*(1 - (h/2)*p(x))*u0[i+1] -(0.5)*(1 + (h/2)*p(x))*u1[i-1] + (1+((h*h)/2)*q(x))*u0[i];
                        vecr[i] = h*h*(0.5)*r(x);


                }

                u1[i] = u0[i] + w*((1/(1+((h*h)/2)*q(x)))*(vecr[i]-sum));
        }


        /*Aquí utilitzo una variable auxiliar norma1 per tenir la norma de la iteració anterior i poder calcular l'error*/
        norma1 = norma2;
        norma2 = norma(u0,u1,n);
        error = (norma2*norma2)/(norma1 - norma2);

        iterats++;

        for (i = 0; i < n; i++){
                        u0[i] = u1[i];
                }


        }while(epsilon < fabs(error) && iterats < max_iter);

        /* Poso fabs(error) per si la resta del denominador de l'error fos negativa*/

        /*Obrim el fitxer de sortida*/
	printf("Dona'm el nom del fitxer de sortida\n");
	scanf("%s", sor);

        sortida = fopen(sor, "w");

        if(sortida == NULL){
                printf("No s'ha pogut obrir el fitxer\n");
                exit(1);
        }

        /*Escrivim al fitxer tots els resultats*/

        fprintf(sortida, "%le  %le  %d  %le  %le  %le  %d  %le  %d  %le\n\n", a, b, n, w, alpha, beta,  max_iter, epsilon, iterats, error);

        for (i = 0; i < n; i++){
                                fprintf(sortida, "%+34.26le\n", u0[i]);
        }


        free(u0);
        free(u1);
        free(vecr);
	fclose(sortida);

        return 0;

}

double *saveSpace(int n){
        double *vec;

        vec=(double*)malloc(n*sizeof(double));

        if(vec==NULL){
                printf("Error memòria\n");
                exit(4);
        }
        return vec;
}

double norma(double *x0, double *x1, int n){
        int i;
        double max;

        /*Calculo la norma infinit del vector x0-x1*/


        for(i=0; i<n; i++){
                x0[i] = x1[i] - x0[i];
        }

        max = fabs(x0[0]);

        for(i=1;i<n;i++){

                if(fabs(x0[i] >= max)){
                        max = fabs(x0[i]);
                }
        }

        return max;
}

