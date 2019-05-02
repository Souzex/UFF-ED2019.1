#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int info;
    struct lista *prox;
} TLSE;

TLSE *insere_final (TLSE* l, int x);
TLSE *insere_inicio (TLSE* l, int x);
void libera_lista (TLSE* l);
void libera_lista_rec (TLSE* l);
void imprime_lista (TLSE* l);
void imprime_lista_rec (TLSE* l);

void i_p (TLSE *l); // void* i_p (TLSE *l);

int main () {

    TLSE *minha_lista;

    int elemento = 1;

    int i, max = 10;
    for (i=0; i<max; i++)
        minha_lista = insere_inicio (minha_lista, rand() % 10); // rand() % 10

    printf("Criada 'minha_lista': ");
    imprime_lista (minha_lista);
    printf("\n");

    // Tem de usar 'libera_lista (l);' em 'TLSE* inverte (TLSE* l)'
    // printf("Ponteiro 'minha_lista' (1o elem '%d'): %p\n", minha_lista->info, minha_lista);
    i_p (minha_lista);
    // printf("Ponteiro 'minha_lista' (1o elem '%d'): %p\n", minha_lista->info, minha_lista);

    printf("Nova lista com ímpares e pares: ");
    imprime_lista (minha_lista);
    printf("\n");

    printf("Liberada 'minha_lista': ");
    libera_lista (minha_lista);
    imprime_lista (minha_lista);
    printf("\n");

    return 75;
}

void i_p (TLSE *l) { // void* i_p (TLSE *l)

    TLSE *pares = NULL, *impares = NULL , *aux;

    aux = l;
    while (aux) {
        aux->info % 2 ? impares = insere_final (impares,aux->info) : (pares = insere_final (pares,aux->info));
        aux = aux->prox;
    }
    aux = impares;
    while (aux->prox) aux = aux->prox;
    aux->prox = pares;

    aux = l;
    while (aux) {
        aux->info = impares->info;
        aux = aux->prox;
        impares = impares->prox;
    }

    free (impares);
    free (pares);
}

TLSE *insere_final (TLSE* l, int x) {

    TLSE *aux, *novo = (TLSE *) malloc (sizeof(TLSE));
    novo->info = x;
    novo->prox = NULL;
    
    if (l) {
        aux = l; 
        for (; aux->prox; aux = aux->prox); 
        aux->prox = novo;
    } else 
        l = novo;
    
    return l;
}

TLSE *insere_inicio (TLSE* l, int x) {

    TLSE *novo = (TLSE *) malloc (sizeof(TLSE));
    novo->info = x;
    novo->prox = l;
    return novo;
}

void libera_lista (TLSE* l) {
    
    TLSE *aux1, *aux2;

    aux1 = l;

    while(aux1) {
        aux2 = aux1;
        aux1 = aux1->prox;
        //printf("Liberando '%d' End. %p - ANTES\n", aux2->info, aux2);
        free (aux2);
        //printf("Liberando '%d' End. %p - DEPOIS\n", aux2->info, aux2);
    }
}

void libera_lista_rec (TLSE* l) {
    
    if (l) {
        libera_lista_rec (l->prox);
        // printf("Liberando '%d' End. %p - ANTES\n", l->info, l);
        free (l);
        // printf("Liberando '%d' End. %p - DEPOIS\n", l->info, l);
    }
}

void imprime_lista (TLSE* l) {

    TLSE *aux = l; 

    // do {printf("%d > ", minha_lista->info);} while (minha_lista = minha_lista->prox);

    while (aux) {
        printf("%d > ", aux->info);
        aux = aux->prox;
    }
    printf("NULL");
}

void imprime_lista_rec (TLSE* l) {

    if (l) {
        printf("%d > ", l->info);
        imprime_lista_rec (l->prox);
    } else {
        printf("NULL");
    }
}