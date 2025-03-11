#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define N 8477
#define realN 8477


int main(void){

    float *x = (float*)malloc(N * N * sizeof(float));

    float *y = (float*)malloc(N * N * sizeof(float));

    float *z = (float*)malloc(N * N * sizeof(float));
    
    #pragma omp parallel for collapse(2) schedule(static, 12)
    for(int i = 0; i < realN; i++){
        for(int j = 0; j < realN; j++){
            int ij = i * N + j;
            x[ij] = i * j;
            y[ij] = i * j;
        }
    }

    double start = omp_get_wtime();

    #pragma omp parallel for collapse(2) schedule(static, 5)
    for(int i = 0; i < realN; i++){
        for(int j = 0; j < realN; j++){
            int ij = i * N + j;
            z[ij] = x[ij] + y[ij];
        }
    }

    double end = omp_get_wtime();

    printf("Time taken to compute = %f seconds\n", (end - start));

    free(x);
    free(y);
    free(z);

    return 0;
    
}