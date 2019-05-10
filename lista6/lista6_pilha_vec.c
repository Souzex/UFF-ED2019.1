#include <stdio.h>
#include <stdlib.h>

#include "lista6_pilha.h"

typedef struct pilha {
	int pos;
	int* vet;
} TPilha;

TPilha * inicializa_pilha (void) { 
/*    
    TPilha *p = (TPilha *) malloc (sizeof(TPilha));
    p->prim = NULL;
    return p;
*/    
}

void push (TPilha *p, int elem) {
/*
    TNO *novo = (TNO *) malloc (sizeof(TNO));
    novo->info = elem;
    novo->prox = p->prim;
    p->prim = novo;
*/    
}

int pop (TPilha *p) {
/*
    if (vazia_TPilha(p)) exit(1);
    int resp = p->prim->info;
    TNO *q = p->prim;
    p->prim = q->prox;
    free (q);
    return resp;
*/    
}

void libera_pilha (TPilha *p) {
/*    
    TNO *q = p->prim, *t;
    while (q) {
        t = q;
        q = q->prox;
        free (t);
    }
    free (p);
*/    
}

int vazia_pilha (TPilha *p) { 
/*    
    return p->prim == NULL;
*/    
}

void imprime_pilha (TPilha *f) {
/*
    TNO *no = f->ini;

    while (no) {
        printf("%d > ", no->info);
        no = no->prox;
    }
    printf("NULL");
*/
}