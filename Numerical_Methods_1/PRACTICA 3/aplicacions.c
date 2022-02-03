/* Volem aproximar diferents valors de e^x utilitzant polinomis. Compararem el polinomi de Taylor de la funció en el punt x0 = 0 amb el de Lagrange       per a diferents abcisses en l'interval [-1, 1]. Proveu-lo per a diferents valors del grau n. */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(void){
	double h, punt, terme=1, taylor=1, lj, lagrange;
        int i, j, n;
	
	/*El que faré és demanar n, i faré n+1 punts on crearé el polinomi de Lagrange amb aquests n+1 punts, i crearé el polinomi de Taylor
	  fins a grau n, aleshores demanaré el valor d'un nombre i compararé en una taula la funció exp , el polinomi de Taylor i el polinomi
	  de Lagrange evaluats en aquest nombre*/
	
	printf("DONA'M EL GRAU DEL POLINOMI (n+1) punts\n");
        scanf("%d", &n);
        n=n+1;


        printf("Dona'm el valor del punt on avaluarem e^x, el polinomi de Taylor, i el polinomi de Lagrange\n");
        scanf("%le", &punt);

        for(i=1;i<=n;i++){
	 
       		terme=terme*(punt/i);
        	taylor=taylor+terme;
	 	}

	/*Generarem n+1 abcises equidistants entre -1 i 1, evaluarem aquestes abcisses en e^x per trobar les fi i aleshores poder crear el polinomi de 
	  Lagrange */

	h= (2)/(double)n;
	/*Distància entre cada punt és a dir punt final - punt inicial dividit per n*/
	printf("  %s %25s %26s\n", "exp(x)", "Taylor", "Lagrange");
	for(j=0;j<n;j++){
		lj=1;
		for(i=0;i<n;i++){
			if(i!=j){
			lj*=(punt-(-1+(h*i)))/((-1+(h*j))-(-1+(h*i)));
			}
		}
		lagrange+= exp(-1+(h*j))*lj;
	}
	
	printf(" %24.17le  %24.17le %24.17le\n", exp(punt), taylor, lagrange);

	return 0;
	 }



