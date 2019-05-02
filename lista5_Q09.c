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

TLSE* junta_listas (TLSE *l1, TLSE *l2);

int main () {

    TLSE *lista1 = NULL, *lista2 = NULL, *minha_lista;

    printf("lista1: %p\n", lista1);
    printf("lista2: %p\n", lista2);

    int i, max = 5;
    for (i=0; i<max; i++) {
        lista1 = insere_inicio (lista1, rand() % 10); 
        lista2 = insere_inicio (lista2, (rand() % 10)+i); 
    }

    printf("Criada 'lista1': ");
    imprime_lista (lista1);
    printf("\n");

    printf("Criada 'lista2': ");
    imprime_lista (lista2);
    printf("\n");

    // Tem de usar 'libera_lista (l);' em 'TLSE* inverte (TLSE* l)'
    // printf("Ponteiro 'minha_lista' (1o elem '%d'): %p\n", minha_lista->info, minha_lista);
    minha_lista = junta_listas (lista1, lista2);
    // printf("Ponteiro 'minha_lista' (1o elem '%d'): %p\n", minha_lista->info, minha_lista);

    printf("Nova lista com lista1 e lista2: ");
    imprime_lista (minha_lista);
    printf("\n");

    printf("Liberada 'minha_lista': ");
    libera_lista (minha_lista);
    imprime_lista (minha_lista);
    printf("\n");

    return 75;
}

TLSE* junta_listas (TLSE *l1, TLSE *l2) {

    TLSE *temp = l1;
    
    while (l1->prox) l1 = l1->prox;
    l1->prox = l2;

    return temp; // l1 = temp; return l1;
    
/*
    TLSE *juncao = NULL, *temp = l1;

    while (l1->prox) l1 = l1->prox;
    l1->prox = l2;

    while (temp) {
        juncao = insere_final (juncao, temp->info);
        temp = temp->prox;
    }

    return juncao;
*/    
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