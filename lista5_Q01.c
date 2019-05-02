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

void inverte_1a_tentativa (TLSE* l);
void inverte (TLSE* l);

int main () {

    TLSE *minha_lista;

    int i, max = 5;
    for (i=0; i<max; i++)
        minha_lista = insere_inicio (minha_lista, i+1); // rand() % 10

    printf("Criada: ");
    imprime_lista (minha_lista);
    printf("\n");
    
    inverte (minha_lista); // inverte_1a_tentativa (minha_lista);
    
    printf("Invertida: ");
    imprime_lista (minha_lista);
    printf("\n");

    libera_lista (minha_lista);

    printf("Liberada: ");
    imprime_lista (minha_lista);
    printf("\n");

    return 75;
}


void inverte (TLSE* l) {

    int i;
    TLSE *aux;

    aux = l;
    for(i=0; aux != NULL; aux = aux->prox) i++;

    int info[i];

    aux = l;
    for(i=0; aux != NULL; aux = aux->prox) info[i++] = aux->info;

    aux = l;
    for(; aux != NULL; aux = aux->prox) aux->info = info[--i];

/*  // WRONG! 'C' MANTÉM O PONTEIRO DE 'l' DO ESCOPO DE 'MAIN()'
    aux = l;

    for(i=0; l != NULL; l = l->prox) i++;

    int info[i];

    for(i=0; l != NULL; l = l->prox) info[i++] = l->info;

    for(; l != NULL; l = l->prox) l->info = info[--i];

    printf("Invertendo dentro de 'inverte()': ");
    imprime_lista (aux);
    printf("\n");
*/

}

// WRONG! 'C' MANTÉM O PONTEIRO DE 'l' DO ESCOPO DE 'MAIN()'
void inverte_1a_tentativa (TLSE* l) {

    TLSE *aux1, *aux2, *aux3 = NULL;
    
    aux1 = l;
    while (aux1) {
       
        aux2 = aux1;
        aux1 = aux1->prox;
        aux2->prox = aux3;
        aux3 = aux2;

        printf("Invertendo: ");
        imprime_lista (aux2);
        printf("\n");
    }
    printf("Ponteiro l-antes: %p\n", l);
    l = aux2;
    printf("Ponteiro l-depois: %p\n", l); // Ao voltar para "main()", l-depois volta a ter o valor de l-antes
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
        printf("Liberando '%d' End. %p - ANTES\n", aux2->info, aux2);
        free (aux2);
        printf("Liberando '%d' End. %p - DEPOIS\n", aux2->info, aux2);
    }
}

void libera_lista_rec (TLSE* l) {
    
    if (l) {
        libera_lista_rec (l->prox);
        printf("Liberando '%d' End. %p - ANTES\n", l->info, l);
        free (l);
        printf("Liberando '%d' End. %p - DEPOIS\n", l->info, l);
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