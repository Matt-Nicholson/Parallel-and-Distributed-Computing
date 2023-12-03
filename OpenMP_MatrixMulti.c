#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define N 1024

double firstMatrix[N][N], secondMatrix[N][N], matrixMultiResult[N][N];

void matrixInit() {
    for(int row = 0; row < N; row++ ) {
        for(int col = 0; col < N; col++) {
            firstMatrix[row][col] = (double)(rand() % 100);
            secondMatrix[row][col] = (double)(rand() % 100);
        }
    }
}

void matrixMulti() {
    #pragma omp parallel for
    for(int row = 0; row < N; row++ ) {
        for(int col = 0; col < N; col++) {
            matrixMultiResult[row][col] = 0;
            for(int k = 0; k < N; k++) {
                matrixMultiResult[row][col] += firstMatrix[row][k] * secondMatrix[k][col];
            }
        }
    }
}

int main() {
    double start, end;
    matrixInit();

    start = omp_get_wtime();
    matrixMulti();
    end = omp_get_wtime();

    printf("elapsed time = %f seconds\n", end - start);
    return 0;
}