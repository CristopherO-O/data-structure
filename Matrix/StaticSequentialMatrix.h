#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

typedef struct {
    int data[MAX][MAX];
    int rows, cols;
} Matrix;

void zeroMatrix(Matrix* mat) {
    int i, j;
    for(i = 0; i < mat->rows; i++)
        for(j = 0; j < mat->cols; j++)
            mat->data[i][j] = 0; 
}

Matrix* createMatrix(int r, int c) {
    Matrix* mat;
    mat = (Matrix*) malloc(sizeof(Matrix));
    if(mat != NULL) {
        if(r <= 0 || c <= 0 || r > MAX || c > MAX) {
            printf("Invalid values\n");
            return NULL;
        }
        mat->rows = r;
        mat->cols = c;
        zeroMatrix(mat);
    }
    return mat;
}

void destroyMatrix(Matrix* mat) {
    if(mat != NULL)
        free(mat);
}

int fillRandom(Matrix* mat, int start, int end) {
    if(mat == NULL) return 0;
    srand(time(NULL));
    for(int i = 0; i < mat->rows; i++)
        for(int j = 0; j < mat->cols; j++)
            mat->data[i][j] = start + rand() % (end - start + 1);
    return 1;
}

int insertValue(Matrix* mat, int value, int r, int c) {
    if(mat == NULL) return 0;
    if(r < 0 || c < 0 || r >= mat->rows || c >= mat->cols) {
        printf("Invalid index!\n");
        return 0;
    }
    mat->data[r][c] = value;
    return 1;
}

int getValue(Matrix* mat, int* p, int r, int c) {
    if(mat == NULL) return 0;
    if(r < 0 || c < 0 || r >= mat->rows || c >= mat->cols) {
        printf("Invalid index\n");
        return 0;
    }
    *p = mat->data[r][c];
    return 1;
}

void printMatrix(Matrix* mat) {
    if(mat == NULL) return;
    printf("Matrix %d x %d:\n", mat->rows, mat->cols);
    for(int i = 0; i < mat->rows; i++) {
        for(int j = 0; j < mat->cols; j++)
            printf("\t%d", mat->data[i][j]);
        printf("\n");
    }
    printf("\n");
}

int isSquare(Matrix* mat) {
    if(mat == NULL) return 0;
    return (mat->rows == mat->cols);
}

int isSymmetric(Matrix* mat) {
    if(mat == NULL) return 0;
    if(!isSquare(mat)) {
        printf("Matrix is not square!\n");
        return 0;
    }
    for(int i = 0; i < mat->rows; i++)
        for(int j = i + 1; j < mat->cols; j++)
            if(mat->data[i][j] != mat->data[j][i])
                return 0;
    return 1;
}

Matrix* createTranspose(Matrix* mat) {
    if(mat == NULL) return NULL;
    Matrix* t = createMatrix(mat->cols, mat->rows);
    for(int i = 0; i < mat->rows; i++)
        for(int j = 0; j < mat->cols; j++)
            t->data[j][i] = mat->data[i][j];
    return t;
}

#endif
