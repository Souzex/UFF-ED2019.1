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

TLSE* ordena (TLSE *l);

int main () {

    TLSE *minha_lista = NULL, *lista_ordenada;

    int i, max = 10;
    for (i=0; i<max; i++)
        minha_lista = insere_inicio (minha_lista, i-1); // rand() % 10

    printf("Criada 'minha_lista': ");
    imprime_lista (minha_lista);
    printf("\n");

    // printf("Ponteiro 'minha_lista' (1o elem '%d'): %p\n", minha_lista->info, minha_lista);
    minha_lista = ordena (minha_lista);
    // lista_ordenada = ordena (minha_lista);
    // printf("Ponteiro 'minha_lista' (1o elem '%d'): %p\n", minha_lista->info, minha_lista);
    
    printf("Nova lista ordenada: ");
    imprime_lista (minha_lista);
    // imprime_lista (lista_ordenada);
    printf("\n");

    printf("Liberada 'minha_lista': ");
    libera_lista (minha_lista);
    imprime_lista (minha_lista);
    printf("\n");

    printf("Liberada 'lista_ordenada': ");
    libera_lista (lista_ordenada);
    imprime_lista (lista_ordenada);
    printf("\n");    

    return 75;
}

TLSE* ordena (TLSE *l) {

    TLSE *tail = NULL, *head = NULL;

    if (l) {

        tail = (TLSE *) (malloc (sizeof(TLSE)));
        tail->info = l->info;
        tail->prox = NULL;
        head = tail;
        
        l = l->prox;
        while (l) { 
            TLSE *aux1, *aux2;
            if (l->info >= tail->info) {
                aux1 = tail;
                tail = (TLSE *) malloc (sizeof(TLSE));
                tail->info = l->info;
                tail->prox = NULL;
                aux1->prox = tail;
            } else {
                aux1 = head;
                aux2 = aux1;
                while (aux1) {
                    if (l->info < aux1->info) {
                        TLSE *novo = (TLSE *) malloc (sizeof(TLSE));
                        novo->info = l->info;
                        novo->prox = aux1;
                        if (aux1 == aux2) // aux1 == head
                            head = novo;
                        else 
                            aux2->prox = novo;
                        aux1 = NULL; // break;
                    } else {
                        aux2 = aux1;
                        aux1 = aux1->prox;
                    }
                }
            }
            l = l->prox;
        }
    }
    return head;
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