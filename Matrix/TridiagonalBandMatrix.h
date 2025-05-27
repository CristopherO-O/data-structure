#ifndef BAND_MATRIX_H
#define BAND_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int *diagonal;
    int *upper;
    int *lower;
    int size;
} BandMatrix;

void zeroMatrix(BandMatrix* bm) {
    for(int i = 0; i < bm->size; i++) {
        bm->diagonal[i] = 0;
        if(i < bm->size - 1) {
            bm->upper[i] = 0;
            bm->lower[i] = 0;
        }
    }
}

BandMatrix* createMatrix(int size) {
    if(size <= 1) {
        printf("Dimension must be > 1\n");
        return NULL;
    }

    BandMatrix* bm = (BandMatrix*) malloc(sizeof(BandMatrix));
    if(bm != NULL) {
        bm->size = size;
        bm->diagonal = (int*) malloc(size * sizeof(int));
        bm->upper = (int*) malloc((size - 1) * sizeof(int));
        bm->lower = (int*) malloc((size - 1) * sizeof(int));
        if(bm->diagonal == NULL || bm->upper == NULL || bm->lower == NULL)
            return NULL;
        zeroMatrix(bm);
    }
    return bm;
}

void destroyMatrix(BandMatrix* bm) {
    if(bm != NULL) {
        free(bm->diagonal);
        free(bm->upper);
        free(bm->lower);
        free(bm);
    }
}

int fillRandom(BandMatrix* bm, int min, int max) {
    if(bm == NULL) return 0;
    srand(time(NULL));
    for(int i = 0; i < bm->size; i++) {
        bm->diagonal[i] = min + rand() % (max - min + 1);
        if(i < bm->size - 1) {
            bm->upper[i] = min + rand() % (max - min + 1);
            bm->lower[i] = min + rand() % (max - min + 1);
        }
    }
    return 1;
}

int insertElement(BandMatrix* bm, int elem, int i, int j) {
    if(bm == NULL) return 0;
    if(i < 0 || j < 0 || i >= bm->size || j >= bm->size) {
        printf("Invalid values, element not inserted!\n");
        return 0;
    }
    if(i == j) bm->diagonal[i] = elem;
    else if(i + 1 == j) bm->upper[i] = elem;
    else if(i == j + 1) bm->lower[j] = elem;
    else {
        printf("Indices out of band\n");
        return 0;
    }
    return 1;
}

int getElement(BandMatrix* bm, int i, int j) {
    if(bm == NULL) return 0;
    if(i < 0 || j < 0 || i >= bm->size || j >= bm->size) {
        printf("Invalid values\n");
        return 0;
    }
    if(i == j) return bm->diagonal[i];
    else if(i + 1 == j) return bm->upper[i];
    else if(i == j + 1) return bm->lower[j];
    else return 0;
}

void printBandVectors(BandMatrix* bm) {
    if(bm == NULL) return;
    printf("Band Matrix, Size: %d x %d:\n", bm->size, bm->size);
    printf("Diagonal = [");
    for(int i = 0; i < bm->size; i++)
        printf("%d ", bm->diagonal[i]);
    printf("]\n");
    printf("Upper = [");
    for(int i = 0; i < bm->size - 1; i++)
        printf("%d ", bm->upper[i]);
    printf("]\n");
    printf("Lower = [");
    for(int i = 0; i < bm->size - 1; i++)
        printf("%d ", bm->lower[i]);
    printf("]\n\n");
}

void printBandMatrix(BandMatrix* bm) {
    if(bm == NULL) return;
    printBandVectors(bm);
    printf("Original Matrix:\n");
    for(int i = 0; i < bm->size; i++) {
        for(int j = 0; j < bm->size; j++)
            printf("%d\t", getElement(bm, i, j));
        printf("\n");
    }
}

#endif
