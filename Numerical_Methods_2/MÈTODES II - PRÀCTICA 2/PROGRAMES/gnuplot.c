#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double f(double,double);

int main(void){
	double y, x, a, b, h;
        int i, n;
	FILE *sortida, *entrada1, *entrada2, *entrada3, *entrada4, *entrada5;
        char sor[30];

        /*Obrim el fitxer de sortida*/

        printf("Dona'm el nom del fitxer on vols imprimir les dades\n");
        scanf("%s", sor);

        sortida = fopen(sor, "w");
        if(sortida == NULL){
                printf("No s'ha pogut obrir el fitxer\n");
                exit(1);
	}
	
	entrada1 = fopen("euler.out", "r");
        if(sortida == NULL){
                printf("No s'ha pogut obrir el fitxer\n");
                exit(2);
	}
	
	entrada2 = fopen("euler_richardson.out", "r");
        if(sortida == NULL){
                printf("No s'ha pogut obrir el fitxer\n");
                exit(3);
	}

	entrada3 = fopen("adams2.out", "r");
	if(sortida == NULL){
                printf("No s'ha pogut obrir el fitxer\n");
                exit(4);
	}
		
	entrada4 = fopen("runge.out", "r");
        if(sortida == NULL){
                printf("No s'ha pogut obrir el fitxer\n");
                exit(5);
	}
		
	entrada5 = fopen("runge_richardson.out", "r");
        if(sortida == NULL){
                printf("No s'ha pogut obrir el fitxer\n");
                exit(6);
	}

	a = (4*atan(1))/6;
        b = (4*atan(1))/3;
        x = a;
        
        n = 10;
        h = (b-a)/n;
	
	/* A cada columna primer imprimim la x, despres el valor de tan(x) que sabem que és la solució correcta, i després l'aproximació de y(x) per els mètodes realitzats en l'ordre de la pràctica */
        
	for(i=0;i<n;i++){
		x = x + h;	
		fprintf(sortida, "%22.16le ", x);
                
		fprintf(sortida, "%22.16le ", tan(x));
                
		fscanf(entrada1, "%le", &y);
		fprintf(sortida, "%22.16le ", y);

	        fscanf(entrada2, "%le", &y);
                fprintf(sortida, "%22.16le ", y);

	    	fscanf(entrada3, "%le", &y);
                fprintf(sortida, "%22.16le ", y);
   
	       	fscanf(entrada4, "%le", &y);
                fprintf(sortida, "%22.16le ", y);
  
	      	fscanf(entrada5, "%le", &y);
                fprintf(sortida, "%22.16le ", y);
		
		fprintf(sortida, "\n");
	}

	fclose(sortida);
	fclose(entrada1);
	fclose(entrada2);
	fclose(entrada3);
	fclose(entrada4);
	fclose(entrada5);
return(0);
}

