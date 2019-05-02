#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int info;
    struct lista *prox;
} TLSE;

TLSE *insere_inicio (TLSE* l, int x);
void libera_lista (TLSE* l);
void libera_lista_rec (TLSE* l);
void imprime_lista (TLSE* l);
void imprime_lista_rec (TLSE* l);

TLSE* desloca (TLSE* l, int n);

int main () {

    TLSE *minha_lista;

    int i, max = 5;
    for (i=0; i<max; i++)
        minha_lista = insere_inicio (minha_lista, i+1); // rand() % 10

    printf("Criada 'minha_lista': ");
    imprime_lista (minha_lista);
    printf("\n");

    // Tem de usar 'libera_lista (l);' em 'TLSE* inverte (TLSE* l)'
    // printf("Ponteiro 'minha_lista' (1o elem '%d'): %p\n", minha_lista->info, minha_lista);
    minha_lista = desloca (minha_lista, 2);
    // printf("Ponteiro 'minha_lista' (1o elem '%d'): %p\n", minha_lista->info, minha_lista);

    printf("Deslocada 'minha_lista': ");
    imprime_lista (minha_lista);
    printf("\n");

    libera_lista (minha_lista);

    printf("Liberada 'minha_lista': ");
    imprime_lista (minha_lista);
    printf("\n");

    return 75;
}

TLSE* desloca (TLSE* l, int n) {

    int i, max, temp;
    TLSE *aux;

    aux = l;
    for(i=0; aux != NULL; aux = aux->prox) i++;

    int info[i], info_aux[i];

    aux = l;
    for(i=0; aux != NULL; aux = aux->prox) info[i++] = aux->info;

    max = i;
    for(i=0; i < max; i++)
        if (n%2)  // impar
            i == 0 ? info_aux[i] = info[max-1] : (info_aux[i] = info[i-1]);
        else // par
            i == max-1 ? info_aux[i] = info[0] : (info_aux[i] = info[i+1]);

    for(i=max; i > 0; aux = insere_inicio (aux, info_aux[--i]));

    libera_lista (l);
    
    return aux;
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