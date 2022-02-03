
#include <stdio.h>
#include <math.h>
#define PI 4*atan(1)

int main(void){

        int k=4, vertexs;
        double aproxsk1, aproxsk2, errorsk1, errorsk2, sk1, sk2;

        do{
                printf("Dona'm el nombre k de vèrtex del polígon regular\n");
                scanf("%d", &vertexs);

        }while(vertexs <4);

        k = 4;
        sk1 = sqrt(2);  /* SK1 FÒRMULA ENUNCIAT */
	sk2 = sqrt(2);  /* SK2 FORMULA MILLORADA */
        aproxsk1 = k*sk1;
        errorsk1 = (aproxsk1 - 2*PI)/aproxsk1;
        aproxsk2 = k*sk2;
        errorsk2 = (aproxsk2 - 2*PI)/aproxsk2;

        printf(" %d     %le     %le     %le     %le\n", k, aproxsk1, errorsk1, aproxsk2, errorsk2);

        for(k=8; k<=vertexs; k=k*2){

                sk1 = sqrt(2-sqrt(4-(sk1*sk1)));
                aproxsk1 = k*sk1;
                errorsk1 = (aproxsk1 - 2*PI)/aproxsk1;
		sk2 = sk2/(sqrt(2+sqrt(4-(sk2*sk2))));
                aproxsk2 = k*sk2;
                errorsk2 = (aproxsk2 - 2*PI)/aproxsk2;
		

                printf(" %d     %le     %le     %le     %le\n", k, aproxsk1, errorsk1, aproxsk2, errorsk2);
        }

        return 0;
}

/* plot 'dades.dad' u(log($1)):(log($3)) w l, 'dades.dad' u(log($1)):(log($5)) w l */
