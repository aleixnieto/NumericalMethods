/* ALEIX NIETO JUSCAFRESA */
/* En aquest programa aproximaré el valor de 2PI mitjançant dues successions recurrents, una que aproxima 2PI mitjançant polígons circumscrits a la 
 * circumferència unitat i una altra que aproxima 2PI mitjançant polígons inscrits a la circumferència unitat, en ambdós casos, anem augmentant el
 * nombre de vèrtex de polígons per poder aproximar-nos cada cop més al valor de 2PI, en el primer cas mitjançant una successió monòtona decreixent,
 * i en el segon cas mitjançant una successió monòtona creixent*/

/* Per cada successió calcularem l'error absolut de 2PI amb el valor de l'aproximació de la successió, i l'error relatiu. Ho farem amb precisió simple i amb precisió double. Al acabar farem una gràfica dels errors en funció dels nombre de vertex usant una escala logarítmica */

#include <stdio.h>
#include <math.h>
#define PI 4*atan(1)

int main(void){

	int k=4, vertexs;
	double aproxsk, aproxck, errorsk, errorck, sk;

	do{
		printf("Dona'm el nombre k de vèrtex del polígon regular\n");
		scanf("%d", &vertexs);
	
	}while(vertexs <4);

	/******************************* Ho dividim per l'aproximació per 2PI, ja que a la pràctica calculem l'error relatiu dividint per l'aproximació, 	  però en aquest cas tenim el valor exacte de 2PI **************************************/


	k = 4;
	sk = sqrt(2);
	aproxsk = k*sk;
	errorsk = (aproxsk - 2*PI)/aproxsk;  /*A la pràctica usarem l'aproximació com a quocient del valor relatiu*/
	aproxck = k*(2*sk)/sqrt(4 - (sk*sk));
	errorck = (aproxck - 2*PI)/aproxck;

	printf(" %d    	 %le	 %le	 %le	 %le\n", k, aproxsk, errorsk, aproxck, errorck);

	for(k=8; k<=vertexs; k=k*2){

		sk = sqrt(2-sqrt(4-(sk*sk)));
		aproxsk = k*sk;
       		errorsk = (aproxsk - 2*PI)/aproxsk;
        	aproxck = k*(2*sk)/sqrt(4 - (sk*sk));
        	errorck = (aproxck - 2*PI)/aproxck;	

	printf(" %d	 %le	 %le	 %le	 %le\n", k, aproxsk, errorsk, aproxck, errorck);
	
	}


	return 0;
}
