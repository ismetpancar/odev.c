# odev.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS1 2
#define COLS1 3
#define ROWS2 3
#define COLS2 2

void randomValueGenerator(int rows, int cols, int matrix[rows][cols]);
void printMatrix(int rows, int cols, int matrix[rows][cols]);
void sumMatrices(int rows, int cols, int mat1[rows][cols], int mat2[rows][cols], int result[rows][cols]);
void multiplyMatrices(int mat1[ROWS1][COLS1], int mat2[ROWS2][COLS2], int result[ROWS1][COLS2]);


int main() {
    srand(time(NULL));

    int array1[ROWS1][COLS1];
    int array2[ROWS2][COLS2];
    int sum[ROWS1][COLS1];
    int product[ROWS1][COLS2];

    
    printf("****** 1. MATRİS ******\n");
    randomValueGenerator(ROWS1, COLS1, array1);
    printMatrix(ROWS1, COLS1, array1);

    
    printf("\n****** 2. MATRİS ******\n");
    randomValueGenerator(ROWS2, COLS2, array2);
    printMatrix(ROWS2, COLS2, array2);

    
    printf("\n****** MATRİS TOPLAMİ ******\n");
    if (ROWS1 == ROWS2 && COLS1 == COLS2) {
        sumMatrices(ROWS1, COLS1, array1, array2, sum);
        printMatrix(ROWS1, COLS1, sum);
    } else {
        printf("Matris toplami mumkun olmaz .iki Matrisin satir sutun sayilari esit olmali.\n");
    }

    
    printf("\n****** MATRİS ÇARPİMİ ******\n");
    if (COLS1 == ROWS2) {
        printf("Matris Carpimi mumkun.\n");
        multiplyMatrices(array1, array2, product);
        printMatrix(ROWS1, COLS2, product);
    } else {
        printf("Matris carpimi mümkün degil. 1.Matrisin sutunu 2.Matrisin satiri esit olmali. \n");
    }

    return 0;
}



    



void randomValueGenerator(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100 + 1; // Values between 1 and 100
        }
    }
}


void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}


void sumMatrices(int rows, int cols, int mat1[rows][cols], int mat2[rows][cols], int result[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}


void multiplyMatrices(int mat1[ROWS1][COLS1], int mat2[ROWS2][COLS2], int result[ROWS1][COLS2]) {
    for (int i = 0; i < ROWS1; i++) {
        for (int j = 0; j < COLS2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < COLS1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

