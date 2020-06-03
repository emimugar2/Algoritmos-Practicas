#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"
#define TAM_MAX 1000
//Operaciones sobre matrices
matriz crear_matriz(int n) {
	int i;
	matriz aux;
	if ((aux = malloc(n * sizeof(int *))) == NULL)
		return NULL;
	for (i = 0; i < n; i++)
		if ((aux[i] = malloc(n * sizeof(int))) == NULL)
			return NULL;
	return aux;
}

void inicializar_matriz(matriz m, int n) {
	/* Crea un grafo completo no dirigido con valores aleatorios entre 1 y n */
	int i, j;
	for (i = 0; i < n; i++)
		for (j = i+1; j < n; j++)
			m[i][j] = rand() % TAM_MAX + 1;
	for (i = 0; i < n; i++)
		for (j = 0; j <= i; j++)
			if (i == j)
				m[i][j] = 0;
			else
				m[i][j] = m[j][i];
}

void liberar_matriz(matriz m, int n) {
	int i;
	for (i = 0; i < n; i++)
		free(m[i]);
	free(m);
}

