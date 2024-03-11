#include<stdio.h>
#include<omp.h>

int main(void){
    int N = 31924;
    int realN = 31924;

    int *cahceLineBalancer = (int*)malloc(14*sizeof(int)); //N and realN take up 8 bytes (4 each). We need to add 14 * 4 = 56 bytes to the cache line to ensure that x starts on the boundary

    float **x = (float**)malloc(N * sizeof(float*));

    #pragma omp parallel for schedule(static, 16)
    for(int i = 0; i < N; i++){
        x[i] = (float*)malloc(N * sizeof(float));
    }

    float **y = (float**)malloc(N * sizeof(float*));

    #pragma omp parallel for schedule(static, 16)
    for(int i = 0; i < N; i++){
        y[i] = (float*)malloc(N * sizeof(float));
    }

    float **z = (float**)malloc(N * sizeof(float*));

    #pragma omp parallel for schedule(static, 16)
    for(int i = 0; i < N; i++){
        z[i] = (float*)malloc(N * sizeof(float));
    }
    
    #pragma omp parallel for schedule(static, 16) collapse(2)
    for(int i = 0; i < realN; i++){
        for(int j = 0; j < realN; j++){
            x[i][j] = i * j;
            y[i][j] = i * j;
        }
    }

    double start = omp_get_wtime();

    #pragma omp parallel for schedule(static, 16) collapse(2)
    for(int i = 0; i < realN; i++){
        for(int j = 0; j < realN; j++){
            z[i][j] = x[i][j] + y[i][j];
        }
    }

    double end = omp_get_wtime();

    printf("Time taken to compute = %f seconds\n", (end - start));

    free(x);
    free(y);
    free(z);

    return 0;
    
}