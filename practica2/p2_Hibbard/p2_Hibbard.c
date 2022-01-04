#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

void inicializar_semilla(){
    srand(time(NULL));
}

void aleatorio(int v[], int n){
    int i, m=2*n+1;
    for (i=0;i<n;i++){
        v[i] = (rand() % m) - n;
    }
}

double microsegundos() {  /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 ){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void ord_sel(int v[],int n){
    int minj=0,minx=0;
    int i,j;
    for(i=0;i<n;i++){
        minj = i;
        minx=v[i];
        for(j=i+1;j<n;j++){
            if(v[j]<minx){
    	    minj=j;
            minx=v[j];
            }
        }
        v[minj]=v[i];
        v[i]=minx;
    }
}

void ord_shell_hibbard(int v[], int n){
    int tmp,j,i,seguir;
    int k = 0;
    int incremento = 0;

    while(n > pow(2, k+1) - 1){
        k++;
    }

    incremento = pow(2, k) - 1;

    while(incremento != 0){
        for(i = incremento;i<n;i++){
            tmp=v[i];
            j=i;
            seguir=1;
            while ((j-incremento>=0) && (seguir)){
                if (tmp<v[j-incremento]){
                    v[j]=v[j-incremento];
                    j-=incremento;
                }else seguir=0;
            }
            v[j]=tmp;
        }
        incremento /= 2;
    }
}

double testAlgoritmo(int vector[], int n, void (*func)(int[], int),
                     void (*funGen)(int[], int)){
    double ta=0,tb=0,t=0,t1=0,t2=0;
    int k=1000;
    int count;

    funGen(vector,n);

    ta=microsegundos();
    func(vector, n);
    tb=microsegundos();
    t=tb-ta;

    if(t<500){
        ta=microsegundos();
        for(count=0;count<k;count++){
            funGen(vector,n);
            func(vector, n);
        }
        tb=microsegundos();
        t1=tb-ta;

        ta=microsegundos();
        for(count=0;count<k;count++){
            funGen(vector,n);
        }
        tb=microsegundos();
        t2=tb-ta;
        t=(t1-t2)/k;
        printf("(*)");
    }else printf("   ");
    return t;
}

void printChart(void (*func)(int[], int),void (*funGen)(int[], int),
                float cotaSub,float cotaAj,float cotaSob ){
    double t =0;
    double tsub, taj, tsob;
    int vector[32000];
    int n;

    printf("\n");
	printf("%7s%16s%18s%.2f%15s%.2f%15s%.2f \n",
            "n", "t(n)", "t(n)/n^", cotaSub, "t(n)/n^", cotaAj, "t(n)/n^", cotaSob);

    for(n = 500; n <= 32000; n*=2){
        t = testAlgoritmo(vector, n, func, funGen);

        tsub=t/pow(n,cotaSub);
        taj=t/pow(n,cotaAj);
        tsob=t/pow(n,cotaSob);
        printf("%6d%16.3f%18.6f%20.6f%18.6f\n", n, t, tsub, taj, tsob);
    }
}

void printVector(int v[], int n){
    int i;
    printf("[");
    for (i=0; i<n;i++){
        printf("%3d", v[i]);
    }
    printf(" ]\n");
}

void descendente(int v[], int n){
    int i,j=0;
    for(i=n;i>0;i--) {
        j++;
        v[i-1]=j;
    }
}

void ascendente(int v[], int n){
    int i;
    for(i=0;i<n;i++) {
        v[i]=i;
    }
}

void testWithVector(void (*func)(int[], int),void (*funGen)(int[], int)
                    ,int vector[],int  n){
    funGen(vector, n);
    printf("Input: ");
    printVector(vector, n);
    printf("Output:");
    func(vector, n);
    printVector(vector, n);
}

void printearTestAleatorios(void (*func)(int[],int),int vector[],int n){
    int i;
    for(i=0;i<4;i++){
        testWithVector(func, aleatorio, vector, n);
        printf("\n");
    }
}

void printearAscenDescen(void (*func)(int[],int),int vector[],int n){
    testWithVector(ord_sel, descendente, vector, n);
    printf("\n");
    testWithVector(ord_sel,ascendente,vector,n);
    printf("\n");

}

int main(){
    int n=10;
    int v[n];
    inicializar_semilla();

    printf("\n%8s ORDENACION POR SELECCION \n","");
    printearTestAleatorios(ord_sel,v,n);
    printearAscenDescen(ord_sel,v,n);
    printf("%8s***---------------***\n","");
    printf("%10s ORDENACION HIBBARD \n","");
    printearTestAleatorios(ord_shell_hibbard,v,n);
    printearAscenDescen(ord_shell_hibbard,v,n);

    printf("\nOrdenacion por selecion de vector ascendente:");
    printChart(ord_sel,ascendente, 1.8, 2, 2.2);
    printf("\nOrdenacion por selecion de vector descendente:");
    printChart(ord_sel,descendente, 1.8, 2, 2.2);
    printf("\nOrdenacion por selecion de vector aleatorio:");
    printChart(ord_sel,aleatorio, 1.8, 1.98, 2.2);

    printf("\nOrdenacion por Hibbard de vector ascendente:");
    printChart(ord_shell_hibbard,ascendente, 1,1.14,1.3);
    printf("\nOrdenacion por Hibbard de vector descendente:");
    printChart(ord_shell_hibbard,descendente, 1, 1.14, 1.3);
    printf("\nOrdenacion por Hibbard de vector aleatorio:");
    printChart(ord_shell_hibbard,aleatorio, 1, 1.19, 1.3);

    return 0;
}
