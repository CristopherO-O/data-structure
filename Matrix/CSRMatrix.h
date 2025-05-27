#ifndef SPARSE_MATRIX_CSR_H
#define SPARSE_MATRIX_CSR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "DynamicMatrix.h"

typedef struct {
    int *values;
    int *row_indices;
    int *col_indices;
    int rows, cols;
    int capacity; // QNN
    int count;    // QI
} SparseMatrixCSR;

SparseMatrixCSR* createSparseMatrix(int rows, int cols, int initialCapacity) {
    if (rows <= 0 || cols <= 0 || initialCapacity < 0) {
        printf("Invalid parameters\n");
        return NULL;
    }

    SparseMatrixCSR *mat = (SparseMatrixCSR*) malloc(sizeof(SparseMatrixCSR));
    if (!mat) return NULL;

    mat->rows = rows;
    mat->cols = cols;
    mat->count = 0;
    mat->capacity = initialCapacity;
    mat->values = mat->col_indices = mat->row_indices = NULL;

    if (initialCapacity > 0) {
        mat->values = (int*) malloc(initialCapacity * sizeof(int));
        mat->col_indices = (int*) malloc(initialCapacity * sizeof(int));
        if (!mat->values || !mat->col_indices) {
            free(mat->values);
            free(mat->col_indices);
            free(mat);
            return NULL;
        }
    }

    mat->row_indices = (int*) calloc(rows + 1, sizeof(int));
    if (!mat->row_indices) {
        free(mat->values);
        free(mat->col_indices);
        free(mat);
        return NULL;
    }

    return mat;
}

void printCSRStructure(SparseMatrixCSR* mat) {
    if (!mat) return;

    printf("Sparse Matrix (%d x %d) with %d non-zero elements:\n", 
           mat->rows, mat->cols, mat->count);

    printf("Values: [");
    for (int i = 0; i < mat->count; i++)
        printf("%d ", mat->values[i]);
    printf("]\n");

    printf("Row Indices (IA): [");
    for (int i = 0; i <= mat->rows; i++)
        printf("%d ", mat->row_indices[i]);
    printf("]\n");

    printf("Column Indices (JA): [");
    for (int i = 0; i < mat->count; i++)
        printf("%d ", mat->col_indices[i]);
    printf("]\n\n");
}

int insertElement(SparseMatrixCSR *mat, int value, int row, int col) {
    if (!mat) return 0;
    if (row < 0 || col < 0 || row >= mat->rows || col >= mat->cols) {
        printf("Invalid indices\n");
        return 0;
    }

    int start = mat->row_indices[row];
    int end = mat->row_indices[row + 1];
    int insertPos = -1;

    for (int k = start; k < end; k++) {
        if (mat->col_indices[k] == col) {
            mat->values[k] = value;
            return 1;
        } else if (mat->col_indices[k] > col) {
            insertPos = k;
            break;
        }
    }

    if (mat->count == mat->capacity) {
        int newCapacity = (mat->capacity == 0) ? 1 : mat->capacity * 2;
        int *newValues = realloc(mat->values, newCapacity * sizeof(int));
        int *newCols = realloc(mat->col_indices, newCapacity * sizeof(int));
        if (!newValues || !newCols) {
            printf("Memory allocation error\n");
            return 0;
        }
        mat->values = newValues;
        mat->col_indices = newCols;
        mat->capacity = newCapacity;
    }

    if (insertPos == -1) insertPos = end;

    for (int k = mat->count; k > insertPos; k--) {
        mat->values[k] = mat->values[k - 1];
        mat->col_indices[k] = mat->col_indices[k - 1];
    }

    mat->values[insertPos] = value;
    mat->col_indices[insertPos] = col;
    mat->count++;

    for (int k = row + 1; k <= mat->rows; k++)
        mat->row_indices[k]++;

    printCSRStructure(mat);
    return 1;
}

int removeElement(SparseMatrixCSR *mat, int row, int col) {
    if (!mat) return 0;
    if (row < 0 || col < 0 || row >= mat->rows || col >= mat->cols) {
        printf("Invalid indices\n");
        return 0;
    }

    int start = mat->row_indices[row];
    int end = mat->row_indices[row + 1];
    int removeIndex = -1;

    for (int k = start; k < end; k++) {
        if (mat->col_indices[k] == col) {
            removeIndex = k;
            break;
        }
    }

    if (removeIndex != -1) {
        for (int k = removeIndex; k < mat->count - 1; k++) {
            mat->values[k] = mat->values[k + 1];
            mat->col_indices[k] = mat->col_indices[k + 1];
        }
        mat->count--;
        for (int k = row + 1; k <= mat->rows; k++)
            mat->row_indices[k]--;
    } else {
        printf("Element not found.\n");
        return 0;
    }

    printCSRStructure(mat);
    return 1;
}

SparseMatrixCSR* convertToCSR(Matriz* mat) {
    if (!mat) {
        printf("Matrix not found!\n");
        return NULL;
    }

    SparseMatrixCSR *sparse = createSparseMatrix(mat->lin, mat->col, 4); // start with small capacity
    if (!sparse) return NULL;

    for (int i = 0; i < mat->lin; i++) {
        for (int j = 0; j < mat->col; j++) {
            if (mat->dados[i][j] != 0)
                insertElement(sparse, mat->dados[i][j], i, j);
        }
    }

    return sparse;
}

int getElement(SparseMatrixCSR* mat, int row, int col) {
    if (!mat) return 0;
    if (row < 0 || col < 0 || row >= mat->rows || col >= mat->cols) {
        printf("Invalid indices\n");
        return 0;
    }

    for (int k = mat->row_indices[row]; k < mat->row_indices[row + 1]; k++)
        if (mat->col_indices[k] == col)
            return mat->values[k];

    return 0;
}

void printSparseMatrix(SparseMatrixCSR* mat) {
    if (!mat) return;

    printCSRStructure(mat);
    printf("Full Matrix:\n");
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++)
            printf("%d\t", getElement(mat, i, j));
        printf("\n");
    }
}

void freeSparseMatrix(SparseMatrixCSR* mat) {
    if (mat) {
        free(mat->values);
        free(mat->row_indices);
        free(mat->col_indices);
        free(mat);
    }
}

#endif
