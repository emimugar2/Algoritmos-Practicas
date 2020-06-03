#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


void inicializar_semilla() {
	srand(time(NULL));
}

// 	Se generan números pseudoaleatorio entre -n y +n 
void aleatorio(int v [], int n) {
	int i, m=2*n+1;
	for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;
}

// Se generan números en orden ascendente
void ascendente(int v [], int n) {
	int i;
	for (i=0; i < n; i++)
		v[i] = i;
}

// Se generan números en orden ascendente
void descendente(int v [], int n) {
	int i;
	for (i=0; i < n; i++)
		v[i] = n-i;
}
// Funcion intercambiar 
void intercambiar (int v[],int a, int b){
	int c;
	c = v[a];
	v[a] = v[b];
	v[b]=c;
}

// Ordenar examen
void auxord(int v[], int iz, int dr){
	int i,j;
	if(iz < dr){
		i =  iz;
		for(j= iz + 1;j <= dr; j++){
			if(v[j] < v[iz]){
				i = i + 1;
				intercambiar(v,i,j);
			}
		}
		intercambiar(v,iz,i);
		auxord (v,iz, i-1);
		auxord (v,i+1, dr);		
	}
}

void ordenar(int v[], int n){
	auxord(v,0,n-1);
}


void test(void (*ordenar)(int*,int),void (*inicializar)(int*,int),int n)
{
	int i;
	int *v = (int*)malloc(n*sizeof(int));
	
	inicializar(v,n);
	
	for (i = 0; i < n; i++)
		printf("%d%c",v[i],(i!=n-1)?',':'\n');
	
	ordenar(v,n);
	for (i = 0; i < n; i++)
		printf("%d%c",v[i],(i!=n-1)?',':'\n');
}

void mostrarTest(){
	int test_size = 10;
	printf("\nTest - auxord - Ascendente\n");
	test(ordenar,ascendente,test_size);
	printf("\nTest - auxord - Descendente\n");
	test(ordenar,descendente,test_size);
	printf("\nTest - auxord - Aleatorio\n");
	test(ordenar,aleatorio,test_size);
	printf("\n");
}


double microsegundos(){
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0)
		return 0.0;
	return(t.tv_usec + t.tv_sec * 1000000.0);
}

void complejidad(int n, double t,int comple){
		
	switch (comple){
	case 1: printf("%10d \t\t %0.3f \t %0.7f \t %0.7f \t %0.7f \n",
			n,t,t/pow(n, 1.8),t/pow(n,2),t/pow(n,2.2));
	break;
	case 2: printf("%10d \t\t %0.3f \t %0.7f \t %0.7f \t %0.7f \n",
			n,t,t/pow(n, 1.8),t/pow(n,2),t/pow(n,2.2));
	break;
	case 3: printf("%10d \t\t %0.3f \t %0.7f \t %0.7f \t %0.7f \n",
			n,t,t/pow(n,1.05),t/pow(n,1.2),t/pow(n, 1.8));
	default:break;

	}
}

void tiempos (int n,void ordenacion (int v[], int n),void generacion
                                                       (int v[], int n), int comple){
	int v[n];			
	double ta,tb,t;
	int i,k;
	k = 1000;
	generacion(v,n);
	ta = microsegundos();
	ordenacion(v,n);
	tb = microsegundos();
	t=tb-ta;
	if (t<500){
		ta = microsegundos();	
		for(i = 0;i<k;i++){
			generacion(v,n);
			ordenacion(v,n);
		}
		tb = microsegundos();                                            
		t=tb-ta;
		ta = microsegundos();
		for(i = 0;i<k;i++){												
			generacion(v,n);
		}
		tb = microsegundos();
		t= (t-(tb-ta))/k;	
		printf("*");
	}else printf(" ");
	complejidad(n,t,comple);

}


void medicion_tiempos(void ordenacion (int v[], int n),void generacion
                                                     (int v[], int n), int comple){
	int i;
	for (i=500;i<=128000;i=i*2){
		tiempos(i,ordenacion,generacion, comple);
	}
}


void mostrarTablasOrdenar(){
	printf("\nCALENTANDO MAQUINA\n");
	medicion_tiempos(ordenar,ascendente,1);
	
	printf("\nTabla tiempos - auxord - Ascendente\n");
 	printf("---------------------------------------------------------------"
		"------------------------\n");
	printf("   	  n \t\t t(n) \t\t t(n)/n^1.8 \t t(n)/n^2 \t t(n)/n^2.2\n" );
	printf("---------------------------------------------------------------"
		"------------------------\n");
	medicion_tiempos(ordenar,ascendente,1);
		
	printf("\nTabla tiempos - auxord - Descendente\n");
 	printf("---------------------------------------------------------------"
		"------------------------\n");
	printf("   	  n \t\t t(n) \t\t t(n)/n^1.8 \t t(n)/n^2 \t t(n)/n^2.2\n" );
	printf("---------------------------------------------------------------"
		"------------------------\n");
	medicion_tiempos(ordenar,descendente,2);
		
	printf("\nTabla tiempos - auxord - Aleatoria\n");
 	printf("---------------------------------------------------------------"
		"------------------------\n");
	printf("   	  n \t\t t(n) \t\t t(n)/0.8*log(n) \t t(n)/log(n) \t t(n)/1.2*log(n)\n" );
	printf("---------------------------------------------------------------"
		"------------------------\n");
	medicion_tiempos(ordenar,aleatorio,3);
	
}


int main(){
	void free(void* v);
	inicializar_semilla();
	mostrarTest();
	mostrarTablasOrdenar();
}

