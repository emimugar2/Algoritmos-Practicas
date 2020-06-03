//Emilio Martínez Varela
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define TAM 256000
#define K 10000 //interacciones del algoritmo
#define L 128000 //maximo valor de n
#define N 500	//minimo valor de n
#define M 10    //Tamaño monticulo

typedef struct {
	int vector[TAM];
	int ultimo;
} monticulo;

/////////////////////////////////////////////////////////
void inicializar_semilla() {
	srand(time(NULL));
}

/////////////////////////////////////////////////////////                       

double microsegundos(){
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0)
		return 0.0;
	return(t.tv_usec + t.tv_sec * 1000000.0);
}

////////////////// Generacion vectores ////////////////

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

// Se generan números en orden descendente
void descendente(int v [], int n) {
	int i;
	for (i=0; i < n; i++)
		v[i] = n-i;
}

/////////////// Operaciones auxiliares monticulo /////////////
void intercambiar (int v[],int a, int b){
	int c;
	c = v[a];
	v[a] = v[b];
	v[b]=c;
}

void mostrar_mont(monticulo *m) {
	for (int i = 0; i <= m->ultimo; i++)
		printf("%d%c",m->vector[i],(i!=m->ultimo)?',':'\n');
}

bool es_monticulo_vacio(const monticulo *m){
	return (m->ultimo == -1);
}

/////////////////// Operaciones monticulo ///////////////////
void ini_monticulo(monticulo *m){
	m->ultimo = -1;
}



void hundir(monticulo *m, int i){
	int j,izq,der;
	j=m->ultimo;
	while(i!=j){
		izq = 2*i+1;
		der = 2*i+2;
		j = i;
		if(der<=m->ultimo && m->vector[der] < m->vector[i]){
			i=der;
		}
		if(izq<=m->ultimo && m->vector[izq] < m->vector[i]){
			i=izq;
		}
		intercambiar (m->vector,i,j);	
	}
}

void crearMonticulo(int v[], int n, monticulo *m){
	int i;
	
	if(n < TAM){
		for(i = 0; i < n; i++){
			m->vector[i]=v[i];
		}
		m->ultimo = n-1;
		
		for(i=(m->ultimo/2);i>=0;i--){
			hundir(m,i);
		}
	}	
}


int consultarMenor(const monticulo *m){	
	if(!es_monticulo_vacio(m))
		return m->vector[0];
	else 
		return printf("Error: Montículo Vacio");
};


void quitarMenor(monticulo *m){
	if(es_monticulo_vacio(m)){
		printf("Error: Montículo Vacío");
	}else{
		m->vector[0] = m->vector[m->ultimo];
		if(m->ultimo > -1){
			hundir(m, 0);
		}
	}
}


void ord_mont(int v[],int n){	
	monticulo m;
	int i;
	
	crearMonticulo(v,n,&m);
	for(i = 0; i < n ;i++){
		v[i]=consultarMenor(&m);
		quitarMenor(&m);
	}
}

////////////////// Test Monticulos ////////////////
void test_ordenar(void generacion(int v[], int n)){
	int i;
	int v[M];
	generacion(v,M);
	for(i=0;i<M;i++){
		if(i == M-1 ){
			printf("%d",v[i]);
		}else{
			printf("%d,",v[i]);	
		}
	}
	printf("\n");
	printf("\nMonticulo ordenado:\n");
	ord_mont(v,M);
	for(i=0;i<M;i++){
		if(i == M-1 ){
			printf("%d",v[i]);
		}else{
			printf("%d,",v[i]);	
		}
	}
	printf("\n");

}

void test_inicializar_monticulo(monticulo *m){
	ini_monticulo(m);
	if(m->ultimo==-1)
		printf("Se ha inicializado correctamente\n");
	else printf("Se ha inicializado erroneamente\n");
	
}

void test_crear_monticulo(monticulo *m){
	int v[M];
	int i;
	for(i=0;i<M;i++){
		v[i]=i;
	}
	crearMonticulo(v,M,m);
	mostrar_mont(m);
	printf("\n");
}



void test_quitar_menor(monticulo *m){	
	test_crear_monticulo(m);
	quitarMenor(m);
	printf("\n");
	printf("El nuevo monticulo es: \n");
	mostrar_mont(m);
	printf("\n");
}

void tests(){
	monticulo m;
	printf("\nTest de inicialización:\n");
	test_inicializar_monticulo(&m);
	printf("\n=====================================================\n");
	printf("\nTest de creación\n");
	test_crear_monticulo(&m);
	printf("\n=====================================================\n");
	printf("\nTest de eliminación\n");
	test_quitar_menor(&m);
	printf("\n=====================================================\n");
	printf("\nTest de ordenación con generación ascendente\n");
	test_ordenar(ascendente);
	printf("\n=====================================================\n");
	printf("\nTest de ordenación con generación descendente\n");
	test_ordenar(descendente);
	printf("\n=====================================================\n");
	printf("\nTest de ordenación con generación aleatoria\n");
	test_ordenar(aleatorio);
	printf("\n=====================================================\n");
	printf("\n");
}

////////////////////// Calculo tiempos /////////////////////
void complejidad(int n, double t,int comple){
		
	switch (comple){
    case 1: printf("%10d%16.3f%23.7f%22.7f%18.7f\n",
			n,t,t/pow(n,0.98),t/(pow(n,0.98)*log(n)),t/pow(n,1.6));
		break;
    case 2: printf("%10d%16.3f%23.7f%22.7f%18.7f\n",
			n,t,t/pow(n,0.93),t/(pow(n,0.98)*log(n)),t/pow(n, 1.6));
		break;
    case 3: printf("%10d%16.3f%23.7f%13.7f%13.7f\n",
			n,t,t/pow(n,0.8),t/n,t/(n*log(n)));
		break;
    default:break;

	}
}

void tiempos (int n,void ordenacion (int v[], int n),void generacion
                                          (int v[], int n), int comple){
	int v[n];			
	double ta,tb,t;
	int i;
	generacion(v,n);
	ta = microsegundos();
	ordenacion(v,n);
	tb = microsegundos();
	t=tb-ta;
	if (t<N){
		ta = microsegundos();	
		for(i = 0;i<K;i++){
			generacion(v,n);
			ordenacion(v,n);
		}
		tb = microsegundos();                                            
		t=tb-ta;
		ta = microsegundos();
		for(i = 0;i<K;i++){												
			generacion(v,n);
		}
		tb = microsegundos();
		t= (t-(tb-ta))/K;	
		printf("*");
	}else printf(" ");
	complejidad(n,t,comple);

}

void tiempos2 (int n,void generacion(int v[], int n), int comple){
	int v[n];			
	double ta,tb,t;
	int i,k;
	monticulo m;
	ini_monticulo(&m);
	k = 1000;
	generacion(v,n);
	ta = microsegundos();
	crearMonticulo(v,n,&m);
	tb = microsegundos();
	t=tb-ta;
	if (t<500){
		ta = microsegundos();	
		for(i = 0;i<k;i++){
			generacion(v,n);
		crearMonticulo(v,n,&m);
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
	for (i=N;i<=L;i=i*2){
		tiempos(i,ordenacion,generacion, comple);
	}
}
void mostrarTablasMonticulos(){
	int i;
	printf("\nCALENTANDO LA MÁQUINA\n");
 	printf("---------------------------------------------------------------"
		"----------------------------\n");
	printf("	n		t(n)		t(n)/n	 	t(n)/n	 	t(n)/n\n");
	printf("---------------------------------------------------------------"
		"----------------------------\n");
		medicion_tiempos(ord_mont,aleatorio,1);
		
	printf("\nTabla tiempos - Crear Montículo - Descendente\n");
 	printf("---------------------------------------------------------------"
		"----------------------------\n");
	printf("	n		t(n)		t(n)/sqrt(n)	t(n)	t(n)/n*log(n)\n");
	printf("---------------------------------------------------------------"
		"----------------------------\n");
	for (i=N;i<=L;i=i*2){
		tiempos2(i,descendente,3);
	}
	printf("\nTabla tiempos - Montículos - Ascendente\n");
 	printf("---------------------------------------------------------------"
		"----------------------------\n");
	printf("	n		t(n)		t(n)/n^0.93	t(n)/n^0.98*log(n)	t(n)/n^1.6\n");
	printf("---------------------------------------------------------------"
		"----------------------------\n");
		medicion_tiempos(ord_mont,ascendente,2);
		
	printf("\nTabla tiempos - Montículos - Descendente\n");
 	printf("---------------------------------------------------------------"
		"----------------------------\n");
	printf("	n 		t(n)		t(n)/n^0.93	t(n)/n^0.98*log(n)	t(n)/n^1.6\n");
	printf("---------------------------------------------------------------"
		"----------------------------\n");
		medicion_tiempos(ord_mont,descendente,2);

			printf("\nTabla tiempos - Montículos - Aleatoria\n");
 	printf("---------------------------------------------------------------"
		"----------------------------\n");
	printf("	n		t(n)		t(n)/n^0.98	t(n)/n^0.98*log(n)	t(n)/n^1.6\n");
	printf("---------------------------------------------------------------"
		"----------------------------\n");
		medicion_tiempos(ord_mont,aleatorio,1);
	
}


int main(){
	inicializar_semilla();
	tests();
	mostrarTablasMonticulos();
}


