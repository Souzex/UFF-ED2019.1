#include <stdio.h>
#include <stdlib.h>

#include "lista6_fila.h"

typedef struct fila {
	int first;
	int last;
	int* vet;
} TFila;

int QUEUE_SIZE = 100;

TFila* inicializa_fila (void) { 
/*
    TFila *f = (TFila *) malloc(sizeof(TFila));
    f->ini = f->fim = NULL;
*/
}

void insere (TFila *f, int elem) {
/*
    TNO *novo = (TNO *) malloc (sizeof(TNO));
    novo->info = elem;
    novo->prox = NULL;
    if (vazia_TFila(f))
        f->ini = f->fim = novo;
    else {
        f->fim->prox = novo;
        f->fim = novo;
    }
*/    
}

int retira (TFila *f) {
/*
    if (vazia_TFila(f)) exit(1);
    int resp = f->ini->info;
    TNO *q = f->ini;
    f->ini = f->ini->prox;
    if(!f->ini) f->fim = NULL;
    free (q);
    return resp;
*/    
}

void libera_fila (TFila *f) { 
/*
    TNO *q = f->ini, *t;
    while (q) {
        t = q;
        q = q->prox;
        free (t);
    }
    free (f);  
*/      
}

int vazia_fila (TFila *f) { 
/*
    return f->ini == NULL;
*/
}

void imprime_fila (TFila *f) {
/*
    TNO *no = f->ini;

    while (no) {
        printf("%d > ", no->info);
        no = no->prox;
    }
    printf("NULL");
*/
}