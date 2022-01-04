// TITLE: Algoritmos Práctica 4
// AUTHOR:                           LOGIN:         
// DATE: 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <sys/time.h>

#define TAM_MAX 8000
typedef int ** matriz;
typedef struct {
    int x, y, peso;
} arista;

typedef arista tipo_elemento;
typedef struct {
    int cabeza, final, tamano;
    tipo_elemento vector[TAM_MAX];
} cola;

void inicializar_semilla(){
    srand(time(NULL));
}

double microsegundos() {  /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 ){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void mostrar_peso(int peso){
    printf("\n --RESULTADO--\n");
    printf("Peso: %d\n",peso);
}

matriz crear_matriz(int n) {
    int i;
    matriz aux;
    if ((aux = malloc(n*sizeof(int *))) == NULL)
        return NULL;
    for (i=0; i<n; i++)
        if ((aux[i] = malloc(n*sizeof(int))) == NULL)
            return NULL;
    return aux;
}

void print_matriz(matriz m,int n) {
    int i,j;
    printf("\n --MATRIZ--\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
          printf(" %2d ",m[i][j]);
        }
      printf("\n");
    }
  }

void inicializar_matriz(matriz m, int n) {
/* Crea un grafo completo no dirigido con valores aleatorios entre 1 y n */
    int i, j;
    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            m[i][j] = rand() % n + 1;

    for (i=0; i<n; i++)
        for (j=0; j<=i; j++)
            if (i==j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}

void liberar_matriz(matriz m, int n) {
    int i;
    for (i=0; i<n; i++)
        free(m[i]);
    free(m);
}

int prim(matriz m, int nodos) {
    int min, i, j, k=0;
    int *masProximo = (int *) malloc(nodos*sizeof(int));
    int *distanciaMinima = (int *) malloc(nodos*sizeof(int));
    int peso=0;
    distanciaMinima[0] = -1;
    for(i = 1; i < nodos; i++) {
        masProximo[i] = 0;
        distanciaMinima[i] = m[i][0];
    }
    for(i=1;i<nodos;i++){
        min=INT_MAX;
        for(j=1;j<nodos;j++){
            if(0<=distanciaMinima[j] && distanciaMinima[j]<min){
                min=distanciaMinima[j];
                k=j;
            }
        }
        peso += m[k][masProximo[k]];
        distanciaMinima[k]=-1;
        for(j=1;j<nodos;j++){
            if(m[j][k]<distanciaMinima[j]){
                distanciaMinima[j]=m[j][k];
                masProximo[j]=k;
            }
        }
    }
    free(masProximo);
    free(distanciaMinima);
    return peso;
}

double tiemposAlgoritmo(int (*func)(matriz, int),void (*funGen)(matriz,int),
                        matriz matriz, int n){
    double ta=0,tb=0,t=0,t1=0,t2=0;
    int k=1000;
    int count;

    funGen(matriz,n);

    ta=microsegundos();
    func(matriz, n);
    tb=microsegundos();
    t=tb-ta;

    if(t<500){

        ta=microsegundos();
        for(count=0;count<k;count++){
            funGen(matriz,n);
            func(matriz, n);
        }
        tb=microsegundos();
        t1=tb-ta;

        ta=microsegundos();
        for(count=0;count<k;count++){
            funGen(matriz,n);
        }
        tb=microsegundos();
        t2=tb-ta;
        t=(t1-t2)/k;
        printf("(*)");
    }else printf("   ");
    return t;
}

void printChart(int (*func)(matriz, int),void (*funGen)(matriz,int),
                float cotaSub,float cotaAj,float cotaSob ){
    double t=0;
    double tsub, taj, tsob;
    int n;
    matriz m= crear_matriz(320);

    printf("\n");
    printf("%7s%16s%18s%.2f%15s%.2f%15s%.2f\n",
           "V", "t(V)", "t(V)/V^", cotaSub, "t(V)/V^", cotaAj, "t(V)/V^",
           cotaSob);

    for(n = 10; n <= 320 && t<500000; n*=2){
        t = tiemposAlgoritmo(func, funGen, m, n);

        tsub=t/pow(n,cotaSub);
        taj=t/pow(n,cotaAj);
        tsob=t/pow(n,cotaSob);
        printf("%6d%16.3f%18.6f%20.6f%18.6f\n", n, t, tsub, taj, tsob);
    }
    liberar_matriz(m,320);
}

void testMatriz1(){
    int n=5,i,j;
    matriz m=crear_matriz(n);
    int a[5][5]={
        {0,1,8,4,7},
        {1,0,2,6,5},
        {8,2,0,9,5},
        {4,6,9,0,3},
        {7,5,5,3,0},
    };
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            m[i][j]=a[i][j];
    }

    print_matriz(m,n);
    mostrar_peso(prim(m,n));
    liberar_matriz(m,n);
}

void testMatriz2(){
    int n=4,i,j;
    matriz m=crear_matriz(n);
    int a2[4][4]= {
        {0,1,4,7},
        {1,0,2,8},
        {4,2,0,3},
        {7,8,3,0},
    };
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            m[i][j]=a2[i][j];
    }

    print_matriz(m,n);
    mostrar_peso(prim(m,n));
    liberar_matriz(m,n);
}
void testMatriz3(){
    int n=7,i,j;
    matriz m=crear_matriz(n);
    int a3[7][7]= {
        { 0, 7,99, 5,99,99,99},
        { 7, 0, 8, 9, 7,99,99},
        {99, 8, 0,99, 5,99,99},
        { 5, 9,99, 0,15, 6,99},
        {99, 7, 5,15, 0, 8, 9},
        {99,99,99, 6, 8, 0,11},
        {99,99,99,99, 9,11, 0}
    };
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            m[i][j]=a3[i][j];
    }

    print_matriz(m,n);
    mostrar_peso(prim(m,n));
    liberar_matriz(m,n);
}

int main(){
    inicializar_semilla();
    testMatriz1();
    testMatriz2();
    testMatriz3();
    printChart(prim,inicializar_matriz,1.5,1.8,2);
}
