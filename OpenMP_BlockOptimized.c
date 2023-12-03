#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define N 1024
#define BLOCK_SIZE 32
double firstMatrix[N][N], secondMatrix[N][N], matrixMultiResult[N][N];

void matrixInit() {
    for(int row = 0; row < N; row++ ) {
        for(int col = 0; col < N; col++) {
            firstMatrix[row][col] = (double)(rand() % 100);
            secondMatrix[row][col] = (double)(rand() % 100);
        }
    }
}

void blockMatrixMulti() {
    #pragma omp parallel for
    for(int row = 0; row < N; row += BLOCK_SIZE) {
        for(int col = 0; col < N; col += BLOCK_SIZE) {
            for(int innerRow = row; innerRow < row + BLOCK_SIZE && innerRow < N; innerRow++) {
                for(int innerCol = col; innerCol < col + BLOCK_SIZE && innerCol < N; innerCol++) {
                    double sum = 0;
                    for(int k = 0; k < N; k++) {
                        sum += firstMatrix[innerRow][k] * secondMatrix[k][innerCol];
                    }
                    matrixMultiResult[innerRow][innerCol] = sum;
                }
            }
        }
    }
}

int main() {
    double start, end;
    matrixInit();

    start = omp_get_wtime();
    blockMatrixMulti();
    end = omp_get_wtime();

    printf("elapsed time = %f seconds\n", end - start);
    return 0;
}