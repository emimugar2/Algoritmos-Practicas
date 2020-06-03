//Emilio Martínez Varela
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "matriz.h"
#define TAM_MAX 1000
#define K 1000


typedef int ** matriz;

void mostrarMatriz(matriz m,int n){
	int i,j; 
	for(i=0;i<n;i++){ 
		for(j=0;j<n;j++){ 
			printf("%3d ", m[i][j]); 
		} printf("\n"); 
	} 
}


void dijkstra(matriz grafo, matriz distancias, int tam) {
	int m, i, w, n,v,min,j;
	int *noVisitados = malloc(tam*sizeof(int));

	for (m=0; m<tam; m++) {
		for (i=0; i<tam; i++) {
			noVisitados[i] = 1;
			distancias[m][i] = grafo[m][i];
		} 
		j=0;
		noVisitados[m] = 0;
		while (j < tam-2) {
			v =0;
			min = TAM_MAX;
			for (n=0; n<tam; n++){
				if (noVisitados[n] == 1){
					if (distancias[m][n] < min){
						min = distancias[m][n];
						v = n;
					}	
				}
			}
			noVisitados[v]=0;
			for (w=0; w<tam ; w++){
				if (noVisitados[w] ==1){
					if (distancias [m][w] > (distancias [m][v]+ grafo [v][w]))
						distancias [m][w] = distancias [m][v] + grafo[v][w];
				}
			}
			j++;
		}
	}
	free(noVisitados);
}

void ejemplo1(matriz m) {
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = m[4][4] = 0;
	m[0][1] = m[1][0] = 1;
	m[1][2] = m[2][1] = 2;
	m[3][4] = m[4][3] = 3;
	m[0][3] = m[3][0] = 4;
	m[1][4] = m[2][4] = m[4][1] = m[4][2] = 5;
	m[1][3] = m[3][1] = 6;
	m[0][4] = m[4][0] = 7;
	m[0][2] = m[2][0] = 8;
	m[2][3] = m[3][2] = 9;
}

void ejemplo2(matriz m) {
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 0;
	m[0][1] = m[1][0] = 1;
	m[0][2] = m[2][0] = 4;
	m[0][3] = m[3][0] = 7;
	m[1][2] = m[2][1] = 2;
	m[1][3] = m[3][1] = 8;
	m[2][3] = m[3][2] = 3;
}

//Tiempos

double microseconds() {         //Obtains the current time in microseconds
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0)
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla() {
//Inicializa la semilla para no obtener los mismos resultados "aleatorios"
	srand(time(NULL));
}

void cabecera(){
	printf("Tabla tiempos-Dijkstra\n");
	printf("---------------------------------------------------------------"
		"-----------------------------\n");
	printf("	n		t(n)		t(n)/n^2.45"		
					"	t(n)/n^2.9		t(n)/n^3.54\n" );
	printf("---------------------------------------------------------------"
		"-----------------------------\n");
}
	

void tiempos() {
	int i,count = 0;
	double t1, t2, ta, tb, t, x, y, z;
	matriz m,d;
	cabecera();
	for(i = 20; i<=640; i*=2){
		d = crear_matriz(i);
		m = crear_matriz(i);
		inicializar_matriz(m,i);
		ta = microseconds();
		dijkstra(m,d,i);
		tb = microseconds();
		t = tb - ta;
		if (t < 500) { //Umbral de confianza
			count=0;
			ta = microseconds();
			do{
				inicializar_matriz(m,i);			
				dijkstra(m, d, i);
				count++;
			}while(count < K);
				tb = microseconds();
				t1 = (tb - ta);
				ta = microseconds();
				count=0;
			do{ inicializar_matriz(m,i); count++;
			}while(count < K);
			tb = microseconds();
			t2 = (tb - ta);
			ta = microseconds();
			t = (t1 - t2) / K;
			x = t / (pow(i, 2.45)); //Cota subestimada
			y = t / (pow(i, 2.9)); //Cota ajustada
			z = t / (pow(i, 3.54));	//Cota sobreestimada
			printf("%9d*%20.2f%19f%17f%23f\n", i, t, x, y, z);
		} else{
			x = t / (pow(i, 2.45)); //Cota subestimada
			y = t / (pow(i, 2.9)); //Cota ajustada
			z = t / (pow(i, 3.54));	//Cota sobreestimada
			printf("%9d%21.2f%19f%17f%23f\n", i, t, x, y, z);
		}
		liberar_matriz(m,i); liberar_matriz(d,i);	
	} printf("\n");
}



void prueba1(){
	printf("Figura 2\n\n");
	matriz matriz1 = crear_matriz(5);
	matriz  distancias = crear_matriz(5);
	inicializar_matriz(matriz1, 5);
	inicializar_matriz(distancias, 5);
	ejemplo1(matriz1);
	printf("Matriz de adyacencia del grafo\n"); 
	mostrarMatriz(matriz1, 5);
	dijkstra(matriz1, distancias, 5);
	printf("\nDistancias\n");
	mostrarMatriz(distancias, 5);
	liberar_matriz(matriz1,5);
	liberar_matriz(distancias,5);
	printf("\n");
}

void prueba2(){
	printf("Figura 3\n\n");
	matriz matriz2 = crear_matriz(4);
	matriz  distancias = crear_matriz(4);
	inicializar_matriz(matriz2, 4);
	inicializar_matriz(distancias, 4);
	ejemplo2(matriz2);
	printf("Matriz de adyacencia del grafo\n"); 
	mostrarMatriz(matriz2, 4);
	dijkstra(matriz2, distancias, 4);
	printf("\nDistancias\n");
	mostrarMatriz(distancias, 4);
	liberar_matriz(matriz2,4);
	liberar_matriz(distancias,4);
	printf("\n");
}


int main() {
	inicializar_semilla();
	prueba1();
	prueba2();
	tiempos();
	tiempos();
	tiempos();
	
}
