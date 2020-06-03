#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#define MAX 5
#define k 10000	

// algoritmo 1 

int sumaSubMax1(int v[], int n) {
	int i, j;
	int estaSuma, sumaMax = 0;
	for (i = 0; i < n; i++) {
		estaSuma = 0;
	for (j = i; j < n; j++) {
		estaSuma += v[j];
		if (estaSuma > sumaMax) {
			sumaMax = estaSuma;
			}
	}
}
return sumaMax;
}

// algoritmo 2

int sumaSubMax2(int v[], int n) {
	int j;
	int estaSuma = 0, sumaMax = 0;
	for (j = 0; j < n; j++) {
		estaSuma += v[j];
		if (estaSuma > sumaMax) {
			sumaMax = estaSuma;
			}
		else if(estaSuma < 0){
			estaSuma = 0;	
			}
}
return sumaMax;
}

// 	Se establece la semilla de una nueva serie de enteros pseudo-aleatorios */

void inicializar_semilla() {
	srand(time(NULL));

}

// 	Se generan números pseudoaleatorio entre -n y +n 

void aleatorio(int v [], int n) {
	int i, m=2*n+1;
	for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;


}

// Obtiene la hora del sistema en microsegundos

double microsegundos() { 
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

// Lista el vector

void listar_vector(int v[], int n){
	int i;
	printf("%s","[");
	for (i=0; i < n; i++)
			printf("%3d",v[i]);
	printf("%s","]");
}

//Mostrar secuencia

void mostrarSec(int listado[]){
	int sec[MAX];
	int j = 0, count = 0;
	
	printf("%19s%15s%15s\n","", "sumaSubMax1", "sumaSubMax2");
	for(int i = 0; i < 30; i++){
		sec[j] = listado[i];
		if (j == 4) {
			count += 1;
			listar_vector(sec, MAX);
			printf("%15d%15d\n", sumaSubMax1(sec,MAX), sumaSubMax2(sec,MAX));
			j = 0;
		} else{
			j += 1;
		}
	}
	printf("\n");
	
}


// Test 1 

void test1(){
	int sec[30]={-9,2,-5,-4,6,4,0,9,2,5,-2,-1,-9,-7,-1,
				9,-2,1,-7,-8,15,-2,-5,-4,16,7,-5,6,7,-7};
	printf("\nValidación de los algoritmos\n\n");
	mostrarSec(sec);

}

// Test 2

void test2() {
	int i, a, b,v[9];
	printf("%33s%15s%15s\n", "", "sumaSubMax1","sumaSubMax2");
	for (i=0; i<10; i++) {
		aleatorio(v, 9);
		listar_vector(v, 9);
		a = sumaSubMax1(v, 9);
		b = sumaSubMax2(v, 9);
		printf("%15d%15d\n", a, b);
	}
	printf("\n");
}


// Función tiempos de ejecución alg1

double tiempos1(int w){
	double ta,tb,tiempo,t3,t4;
	int vector[w];
	
	aleatorio(vector,w);
	ta = microsegundos();
	sumaSubMax1(vector,w);
	tb = microsegundos();
	tiempo = tb-ta;
	
	if(tiempo < 500){
		printf("(*)");
		ta = microsegundos();
		for(int j = 0; j < k; j++){
			aleatorio(vector, w);
			sumaSubMax1(vector, w);
		}
		tb = microsegundos();
		t3 = tb - ta;
		ta = microsegundos();
		for(int j = 0; j < k; j++){
			aleatorio(vector,w);
		}
		tb = microsegundos();
		t4 = tb - ta;
		tiempo = (t3 - t4) / k;
	}
	return tiempo;
}

// Función tiempos de ejecución alg2

double tiempos2(int w){
	double ta,tb,tiempo,t3,t4;
	int vector[w];
	
	aleatorio(vector,w);
	ta = microsegundos();
	sumaSubMax2(vector,w);
	tb = microsegundos();
	tiempo = tb-ta;
	
	if(tiempo < 500){
		printf("(*)");
		ta = microsegundos();
		for(int j = 0; j < k; j++){
			aleatorio(vector, w);
			sumaSubMax2(vector, w);
		}
		tb = microsegundos();
		t3 = tb - ta;
		ta = microsegundos();
		for(int j = 0; j < k; j++){
			aleatorio(vector,w);
		}
		tb = microsegundos();
		t4 = tb - ta;
		tiempo = (t3 - t4) / k;
	}
	return tiempo;
}


void tiemposaux1(int n){
	double t;
	t = tiempos1(n);	
	printf("%10d%15.3f%15.6f%15.6f%15.6f\n",
	n,t,t/pow(n,1.8),t/pow(n,2),t/pow(n,2.2));
	}


//Complejidad algo1

void tabla1(){
	int i,n=500,l=32000;
	printf("%s","================================================="
	"=======================\n");
	printf("%9s%15.4s%20.13s%15.9s%19.12s\n","n","t(n)","t(n)/n¹·⁸",
	"t(n)/n²","t(n)/n²·²");
	printf("%s","================================================="
	"=======================\n");
	
	for(i = n; i <= l; i=i*2){	
		tiemposaux1(i);
	}
}


void tiemposaux2(int n){
	double t;
	t = tiempos2(n);
	printf("%10d%15.3f%15.6f%15.6f%15.6f\n",
	n,t,t/pow(n,0.7),t/n,t/pow(n,1.1));
	}
	
//Complejidad algo2

void tabla2(){
	int i,n=500,l=32000;
	printf("%s","================================================="
	"=======================\n");
	printf("%12s%16.4s%20.13s%15.9s%15.12s\n","n","t(n)","t(n)/n⁰·⁷",
	"t(n)/n","t(n)/n¹·¹");
	printf("%s","================================================="
	"=======================\n");
		
	for(i = n; i <= l; i=i*2){	
		tiemposaux2(i); 
	}
}


int main() {
	inicializar_semilla();
	test1();
	test2();
	tabla1();
	tabla2();
}
