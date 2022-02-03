/* La primera derivada d’una funció f(x) en un punt x0 es pot aproximar, si h és prou petit, per dues expressions F1 i F2.
Programeu les funcions (1)double der(double x0, double h); (2)double derCen(double x0, double h);
que, donats x0 i h retornen F1(x0, h) i F2(x0, h), respectivament.
Programeu una funció main que llegeixi x0 i un pas h, avaluı̈ F1(x0, h) i F2(x0, h) per a valors decreixents del pas i escrigui en un fitxer,       
per a cada pas, el seu valor i l’error en les aproximacions (en punt flotant amb notació exponencial i controlant el nombre de dı́gits de la mantissa).
Feu una gràfica dels errors en funció del pas. Comenteu els resultats.
Podeu aplicar-lo a les funcions f1(x) = 1/(1+x), f2(x) = e^2x*sin(3x) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Cal aclarar que les funcions f1 i f2 estan en altres fitxers, els quals compilarem junts per a poder obtenir el resultat */

double der(double, double);
double derCen(double, double);
double f(double);
double devf(double);

int main(void){
		
	double i, x0, h, tol;
	char sor[50];
	FILE *sortida;
	
	printf("Dona'm el valor de x0\n");
	scanf("%le", &x0);

	printf("Dona'm el valor del pas h\n");
	scanf("%le", &h);

	printf("Introdueix el nom del fitxer de sortida\n");
   	scanf(" %s",sor);

	printf("Dona'm el valor mínim que pot assolir la h (tol)\n");
	scanf("%le", &tol);

	/*Obrim el fitxer i comprovem que es faci correctament */
   	sortida = fopen(sor,"w");

   		if(sortida==NULL){
      			printf("Error al crear el fitxer de sortida\n");
      			exit(1);
   		}
	
	fprintf(sortida, "%23s %23s %23s %23s %23s\n", "h", "F1", "ERROR F1", "F2", "ERROR F2");

	/*Imprimim al fitxer amb 15 decimals exactes fins que la h es tan petita com hem donat*/
	for(i=h;i>=tol;i=i/2){
		fprintf(sortida,"%23.15le    ", i);
		fprintf(sortida,"%23.15le %23.15le    ", der(x0, i), fabs(devf(x0)-der(x0,i)));
		fprintf(sortida,"%23.15le %23.15le\n", derCen(x0, i), fabs(devf(x0)-derCen(x0,i)));
	}

	fclose(sortida);

return 0;
}

/*fórmula descentrada */
double der(double x0, double h){
	double valor;

	valor= (f(x0+h)-f(x0))/h;

return valor;
}

/*fórmula centrada */
double derCen(double x0, double h){
	double valor;

	valor=(f(x0+h)-f(x0-h))/(2*h);		

return valor;
}
double f(double x){

        return sin(x);
}

double devf(double x){

        return cos(x);
}
