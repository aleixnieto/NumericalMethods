/*aplicarem la extrapolacio de Richardson a alguns exemples */
/*fem una taula d'aproximacions i parem quan dues siguin prou properes*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double f (double);
double derCen (double, double);
double trapezis (double, double, int);
int main (void){

	double q,a, b, h, x0, tol, f2, f2o, f3;
	int cas;
	q=2;
	printf("Dona el pas h(recorda que ha no pot ser molt propera a 0 perquè es produeix cancel·lació\n");
	scanf("%le", &h);
	printf("Dona'm la tolerancia\n");
	scanf("%le", &tol);
	printf("Què vols extrapolar? 1-derivada / 2-integral\n");
	scanf("%d", &cas);

	if(cas==1){
		printf("Dona'm el valor de x0\n");
		scanf("%le", &x0);
		printf("%10s %15s %15s %15s\n", "h", "F1(h)", "F2(h)", "F3(h)");
		printf("%10.2le %15.7le\n", h, derCen(x0,h));
		h=h/q;
		f2 = derCen(x0, h)+(derCen(x0, h)-derCen(x0, q*h))/(q*q-1);
		printf("%10.2le %15.7le %15.7le\n", h, derCen(x0, h), f2);
		if(fabs(derCen(x0, h)-derCen(x0, q*h))< tol){
			exit(1);
			}
		do{
			h/= q;
			f2o = f2;
			f2 = derCen(x0, h)+(derCen(x0, h)-derCen(x0, q*h))/(q*q-1);
			f3 = f2 + (f2-f2o)/(q*q*q*q-1);
			printf("%10.2le %15.7le %15.7le %15.7le\n", h, derCen(x0, h), f2, f3);
			} while(fabs(derCen(x0, h)-derCen(x0, q*h))>= tol && fabs(f2-f2o)>= tol);
		} else {
		printf("Dona a i b corresponents a l'interval [a, b] en que s'estudia l'integral\n");
		scanf("%le %le", &a, &b);
		printf("%10s %15s %15s %15s\n", "h", "T1(h)", "T2(h)", "T3(h)");
                printf("%10.2le %15.7le\n", h, trapezis(a, b, (b-a)/h));
                h=h/q;
		f2 = trapezis(a, b, (b-a)/h)+(trapezis(a, b, (b-a)/h)-trapezis(a, b, (b-a)/(q*h)))/(q*q-1);
                printf("%10.2le %15.7le %15.7le\n", h, trapezis(a, b, (b-a)/h), f2);
		if(fabs(trapezis(a, b, (b-a)/h)-trapezis(a, b, (b-a)/(q*h)))< tol){
                        exit(1);
                        }
		do{
                        h/= q;
                        f2o = f2;
                        f2 = trapezis(a, b, (b-a)/h)+(trapezis(a, b, (b-a)/h)-trapezis(a, b, (b-a)/(q*h)))/(q*q-1);;
                        f3 = f2 + (f2-f2o)/(q*q*q*q-1);
                        printf("%10.2le %15.7le %15.7le %15.7le\n", h, trapezis(a, b, (b-a)/h), f2, f3);
                        } while(fabs(trapezis(a, b, (b-a)/h)-trapezis(a, b, (b-a)/(q*h)))>= tol && fabs(f2-f2o)>= tol);
		}
	return 0;
}

double derCen(double x0, double h){
        double valor;

        valor=(f(x0+h)-f(x0-h))/(2*h);

return valor;
}
double trapezis (double a, double b, int n){
        double valor,h;
        int i;

        h=(b-a)/(double)(n);

        valor=f(a)/2;

        for(i=1;i<n;i++){
                valor+=f(a+(i*h));
        }
        valor+=f(b)/2;
        valor=valor*h;

return valor;
}
double f(double x){

	return x*exp(x);
}
