#include <stdio.h>
#include <math.h>

int main(void){
	double in2, e0, eN, successio, errorsuccessio, in1;
	int n, i, k;

	printf("Dona'm quantes iteracions vols fer de l'algorisme\n");
	scanf("%d", &n);
	
	

	in1 = 0.125657; /* Arrodonim in1, que en aquest cas es IO per començar la recurrència amb l'aproximació que ens demana l'enunciat*/
	in2= (1/2.)*log(9/7.);   /* I0 SENSE ARRODONIR*/
	
	e0= in1-in2; /*ERROR INICIAL*//***NEGATIU***/
	printf("%le\n", e0);
	printf(" n        in1               in2               errorsuccessio                   algorisme error\n");

	/* Calulem le dues recurrencies, in1 amb l'error inicial de in0 i in2 amb cap arrodoniment inicial */

	for(i=1;i<=n;i++){
	
	in1 = (1/2.)*((1/(double)i)-7*in1);

	in2 = (1/2.)*((1/(double)i)-7*in2);
	
	errorsuccessio= in1-in2;  /*Error calculat amb la diferència de les dues recurrencies, una on I0 ha estat aproximada a 6 decimals, i l'altra on 
				   agafem tots els decimals possibles en el cas inicial I0 */
	
	
	/* En aquí calcularem l'error mitjançant la fòrmula de l'error que hem deduït, en = (-1)^n*(7/2)^n*e0, vegem que si n es divisible per 2, l'error 	    serà negatiu ja que e0 es negatiu i (-1) elevat a un nombre positiu també és positiu */
	
	if (i%2==0){
		successio=1;
		for(k=1;k<=i;k++){
			successio = successio*(7/2.);
		}	
		
	eN = successio*e0;

	printf(" %d       %f          %le         %le                  %le\n", i, in1, in2, errorsuccessio, eN);

	}else{
		successio=1;
                for(k=1;k<=i;k++){
                        successio = successio*(7/2.);
                }

        eN =-successio*e0;

	printf(" %d       %f          %le         %le                  %le\n", i, in1, in2, errorsuccessio, eN);
	}
}


return 0;

}
