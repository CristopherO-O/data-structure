#ifndef DDE_H
#define DDE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NO
{
    int info;
    struct NO* prox;
    struct NO* ant;
}NO;

typedef struct Deque
{
    int qtd;
    struct NO* init;
    struct NO* end;
    
}Deque;

Deque *criarDeque(){
    Deque* d;
    d = (Deque *) malloc(sizeof(Deque));
    if(d != NULL){
        d->qtd=0;
        d->init = NULL;
        d->end = NULL;
    }
    return d;
}

void destroiDeque(Deque *d){
    if(d != NULL){
        NO* aux;
        while (d->init != NULL){
            aux = d->init;
            d->init = d->init->prox;
            free(aux);
        }
        free(d);
    }
}

int inserirInicio(Deque *d,int x){
    if(d == NULL ) return 0;
    NO* novo = (NO*) malloc(sizeof(NO));
    if(novo == NULL) return 0;
    novo->info = x;
    novo->ant = NULL;
    if(d->qtd==  0){
        novo->prox = NULL;
        d->end = novo;
    }else{
        d->init->ant = novo;
        novo->prox = d->init;
    }
    d->init = novo;
    d->qtd++;
    return 1;
}

int inserirFim(Deque *d,int x){
    if(d == NULL) return 0;
    NO* novo = (NO*) malloc(sizeof(NO));
    if(novo == NULL) return 0;
    novo->info = x;
    novo->prox = NULL;
    if(d->qtd==0){
        novo->ant = NULL;
        d->init = novo;
    }else{
        d->end->prox = novo;
        novo->ant = d->end;
    }
    d->end = novo;
    d->qtd ++;
    return 1;

}  

int removeInit(Deque *d){
    if(d == NULL) return 0;
    if(d->qtd==0) return 0;
    NO* aux = d->init;
    if(d->init == d->end){
        d->init = d->end = NULL;
    }else{
        d->init = d->init->prox;
        d->init->ant = NULL;
    }
    free(aux);
    d->qtd--;
    return 1;
}

int removeEnd(Deque *d){
    if(d == NULL) return 0;
    if(d->qtd==0) return 0;
    NO *aux = d->end;
    if(d->init==d->end){
        d->init = d->end = NULL;
    }else{
        d->end = d->end->ant;
        d->end->prox = NULL;
    }
    free(aux);
    d->qtd--;
    return 1;
}

int verInicio(Deque *d,int *x){
    if(d == NULL) return 0;
    if(d->qtd == 0) return 0;
    *x = d->init->info;
    return 1;
}

int verFim(Deque *d,int *x){
    if(d == NULL) return 0;
    if(d->qtd == 0) return 0;
    *x = d->end->info;
    return 1;
}

void imprimirDeque(Deque *d){
    if(d==NULL || d->qtd == 0){
        printf("deque Vazio\n");
        return;
    }
    NO* aux = d->init;
    printf("{");
    while(aux!=NULL){
        printf("%d ",aux->info);
        aux = aux->prox;
    }
    printf("}\n");
}
#endif