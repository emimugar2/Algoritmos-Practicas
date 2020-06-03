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


// Ordenación por inserción
void ord_ins (int v [], int n) {
	int i, j, x;
	for (i=1; i<n; i++) {
		x = v[i];
		j = i-1;
		while (j>=0 && v[j]>x) {
			v[j+1] = v[j];;
			j--;
		}
		v[j+1] = x;
	}
}

// Ordenación por shell
void ord_shell(int v[],int n){
	int seguir,tmp,j,i,incremento;
	incremento = n;
	while(incremento!=1){
		incremento=incremento/2;
		for(i=incremento;i<n;i++){
			tmp=v[i];
			j=i;
			seguir=1;
			while(((j-incremento)>=0) && seguir==1){
				if(tmp<v[j-incremento]){
					v[j]=v[j-incremento];
					j=j-incremento;
				}
				else{
					seguir=0;
				}
			}
			v[j]=tmp;
		}
	}
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

	printf("\nTest - Insercion - Aleatorio\n");
	test(ord_ins,aleatorio,test_size);
	printf("\nTest - Insercion - Ascendente\n");
	test(ord_ins,ascendente,test_size);
	printf("\nTest - Insercion - Descendente\n");
	test(ord_ins,descendente,test_size);
	
	printf("\nTest - Shell - Aleatorio\n");
	test(ord_shell,aleatorio,test_size);
	printf("\nTest - Shell - Ascendente\n");
	test(ord_shell,ascendente,test_size);
	printf("\nTest - Shell - Descendente\n");
	test(ord_shell,descendente,test_size);
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
			n,t,t/pow(n,1.7),t/pow(n, 2),t/pow(n, 2.3));
      break;
    case 2: printf("%10d \t\t %0.5f \t %0.7f \t %0.7f \t %0.7f \n",
			n,t,t/pow(n,0.87),t/(n*1.85),t/pow(n, 1.35));
      break;
    case 3: printf("%10d \t\t %0.3f \t %0.7f \t %0.7f \t %0.7f \n",
			n,t,t/pow(n,1.8),t/pow(n, 2),t/pow(n, 2.3));
      break;
    case 4: printf("%10d \t\t %0.3f \t %0.7f \t %0.7f \t %0.7f \n",
			n,t,t/pow(n,1.05),t/pow(n,1.2),t/pow(n, 1.8));
      break;
    case 5: printf("%10d \t\t %0.3f \t %0.7f \t %0.7f \t %0.7f \n",
			n,t,t/pow(n,0.9),t/pow(n,1.131),t/pow(n,1.6));
      break;
    case 6: printf("%10d \t\t %0.3f \t %0.7f \t %0.7f \t %0.7f \n",
			n,t,t/pow(n,0.9),t/pow(n,1.12),t/pow(n, 1.7));
      break;
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

void mostrarTablasInser(){
				printf("\nCALENTANDO LA MÁQUINA\n");
 	printf("---------------------------------------------------------------"
		"------------------------\n");
	printf("   	  n \t\t t(n) \t\t t(n)/n^1.7 \t t(n)/n^2 \t t(n)/n^2.3\n" );
	printf("---------------------------------------------------------------"
		"------------------------\n");
		medicion_tiempos(ord_ins,aleatorio,1);
	
			printf("\nTabla tiempos - Inserción - Aleatoria\n");
 	printf("---------------------------------------------------------------"
		"------------------------\n");
	printf("   	  n \t\t t(n) \t\t t(n)/n^1.7 \t t(n)/n^2 \t t(n)/n^2.3\n" );
	printf("---------------------------------------------------------------"
		"------------------------\n");
		medicion_tiempos(ord_ins,aleatorio,1);
		
	printf("\nTabla tiempos - Inserción - Ascendente\n");
 	printf("---------------------------------------------------------------"
		"------------------------\n");
	printf("   	  n \t\t t(n) \t\t t(n)/n^0.87 \t t(n)/n*1.85 \t t(n)/n^1.35\n");
	printf("---------------------------------------------------------------"
		"------------------------\n");
		medicion_tiempos(ord_ins,ascendente,2);
		
	printf("\nTabla tiempos - Inserción - Descendente\n");
 	printf("---------------------------------------------------------------"
		"------------------------\n");
	printf("   	  n \t\t t(n) \t\t t(n)/n^1.8 \t t(n)/n^2 \t t(n)/n^2.3\n" );
	printf("---------------------------------------------------------------"
		"------------------------\n");
		medicion_tiempos(ord_ins,descendente,3);
	
}

void mostrarTablasShell(){
	printf("\nTabla tiempos - Shell - Aleatoria\n");
 	printf("---------------------------------------------------------------"
		"------------------------\n");
	printf("   	  n \t\t t(n) \t\t t(n)/n^1.05 \t t(n)/n^1.2 \t t(n)/n^1.8\n" );
	printf("---------------------------------------------------------------"
		"------------------------\n");
		medicion_tiempos(ord_shell,aleatorio,4);
		
	printf("\nTabla tiempos - Shell - Ascendente\n");
 	printf("---------------------------------------------------------------"
		"------------------------\n");
	printf("   	  n \t\t t(n) \t\t t(n)/n^0.9 \t t(n)/n^1.31 \t t(n)/n^1.6\n" );
	printf("---------------------------------------------------------------"
		"------------------------\n");
		medicion_tiempos(ord_shell,ascendente,5);
		
	printf("\nTabla tiempos - Shell - Descendente\n");
 	printf("---------------------------------------------------------------"
		"------------------------\n");
	printf("   	  n \t\t t(n) \t\t t(n)/n^0.9 \t t(n)/n^1.2 \t t(n)/n^1.7\n" );
	printf("---------------------------------------------------------------"
		"------------------------\n");
		medicion_tiempos(ord_shell,descendente,6);
	
}


void mostrarTablas(){
	mostrarTablasInser();
	mostrarTablasShell();
}

	
void testfuncional(){
	mostrarTest();
}

int main(){
	void free(void* v);
	inicializar_semilla();
	testfuncional();
	mostrarTablas();
}
