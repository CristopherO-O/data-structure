#ifndef DEQUESE_H
#define DEQUESE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct dequeSE
{
    int qtd, init, end;
    int valor[MAX];   
}Deque;

Deque* criaDeck(){
    Deque* d = (Deque*) malloc(sizeof(Deque));
    if(d != NULL){
        d->end = d->init = d->qtd = 0;
    }
    return d;
}

void destroiDeck(Deque *d){
    if(d != NULL){
        free(d);
    }
}

int isItFull(Deque *d){
    if(d == NULL) return -1;
    return (d->qtd == MAX);
}

int isItEmpty(Deque *d){
    if(d == NULL) return -1;
    return (d->qtd == 0);
}

int seeInit(Deque *d, int *x){
    if(d == NULL  || isItEmpty(d)) return 0;
    *x = d->valor[d->init];
    return 1;
}

int seeEnd(Deque *d, int *x){
    if(d == NULL  || isItEmpty(d)) return 0;
    *x = d->valor[(d->end - 1 + MAX) % MAX];
    return 1;
}

int insertInit(Deque *d,int x){
    if(d == NULL || isItFull(d)) return 0;
    d->init = (d->init - 1 + MAX) % MAX;
    d->valor[d->init] = x;
    d->qtd ++;
    return 1;
}

int insertEnd(Deque *d, int x){
    if(d == NULL || isItFull(d)) return 0;
    d->valor[d->end] = x;
    d->end = (d->end + 1) % MAX;
    d->qtd ++;
    return 1;
}

int removeInit(Deque *d){
    if(d == NULL || isItEmpty(d)) return 0;
    d->init = (d->init + 1) % MAX;
    d->qtd--;
    return 1;
}

int removeEnd(Deque *d){
    if(d == NULL || isItEmpty(d)) return 0;
    d->end = (d->end - 1 + MAX) % MAX;
    d->qtd--;
    return 1;
}

void imprimeDeque(Deque *d){
    if(d == NULL || isItEmpty(d)){
        printf("deque vazio\n");
        return;
    }
    int i = d->init;
    printf("{");
    do{
        printf("%d ", d->valor[i]);
        i = (i+1) % MAX;
    }while(i != d->end);
    printf("}\n");
}

#endif