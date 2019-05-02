#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    int mat;
    float cr;
    struct aluno *prox;
} TAluno;

TAluno *insere_final (TAluno* l, int x, float y);
void libera_lista (TAluno* l);
void libera_lista_rec (TAluno* l);
void imprime_lista (TAluno* l);
void imprime_lista_rec (TAluno* l);

TAluno *copia (TAluno *l);

int main () {

    TAluno *minha_lista; 

    int i, max = 5;
    for (i=0; i<max; i++)
        minha_lista = insere_final (minha_lista, i+1, (i+1)*(i+1));

    printf("Criada 'minha_lista': ");
    imprime_lista (minha_lista);
    printf("\n");

    // Tem de usar 'libera_lista (l);' em 'TAluno *copia (TAluno *l)'
    // printf("Ponteiro 'minha_lista' (1o elem '%d'): %p\n", minha_lista->mat, minha_lista);
    minha_lista = copia (minha_lista);
    // printf("Ponteiro 'minha_lista' (1o elem '%d'): %p\n", minha_lista->mat, minha_lista);

    printf("Copiada 'minha_lista': ");
    imprime_lista (minha_lista);
    printf("\n");

    printf("Liberada 'minha_lista': ");
    libera_lista (minha_lista);
    imprime_lista (minha_lista);
    printf("\n");

    return 75;

/*
    // TAluno *copia_lista = (TAluno *) malloc (sizeof(TAluno));
    TAluno *copia_lista;
    TAluno *minha_lista; 

    int i, max = 5;
    for (i=0; i<max; i++)
        minha_lista = insere_final (minha_lista, i+1, (i+1)*(i+1));

    printf("Criada 'minha_lista': ");
    imprime_lista (minha_lista);
    printf("\n");

    // NAO precisa usar 'libera_lista (l);' em 'TAluno *copia (TAluno *l)'
    printf("Ponteiro 'minha_lista' (1o elem '%d'): %p\n", minha_lista->mat, minha_lista);
    copia_lista = copia (minha_lista);
    printf("Ponteiro 'minha_lista' (1o elem '%d'): %p\n", minha_lista->mat, minha_lista);

    printf("Copiada 'minha_lista' em 'copia_lista': ");
    imprime_lista (copia_lista);
    printf("\n");

    printf("Liberada 'minha_lista': ");
    libera_lista (minha_lista);
    imprime_lista (minha_lista);
    printf("\n");

    printf("Liberada 'copia_lista': ");
    libera_lista (copia_lista);
    imprime_lista (copia_lista);
    printf("\n");   

    return 75;
*/
}

TAluno *copia (TAluno *l) {

    TAluno *copia = NULL; 

    for(; l; l = l->prox) copia = insere_final (copia, l->mat, l->cr);

    return copia;
/*
    TAluno *aux = l, *copia = NULL;

    for(; aux; aux = aux->prox) copia = insere_final (copia, aux->mat, aux->cr);
    
    return copia;
*/
}

TAluno *insere_final (TAluno* l, int x, float y) {

    TAluno *aux, *novo = (TAluno *) malloc (sizeof(TAluno));
    novo->mat = x;
    novo->cr = y;
    novo->prox = NULL;
    
    if (l) {
        aux = l; 
        for (; aux->prox; aux = aux->prox); 
        aux->prox = novo;
    } else 
        l = novo;
    
    return l;
}

void libera_lista (TAluno* l) {
    
    TAluno *aux1, *aux2;

    aux1 = l;

    while(aux1) {
        aux2 = aux1;
        aux1 = aux1->prox;
        //printf("Liberando '%d' End. %p - ANTES\n", aux2->info, aux2);
        free (aux2);
        //printf("Liberando '%d' End. %p - DEPOIS\n", aux2->info, aux2);
    }
}

void libera_lista_rec (TAluno* l) {
    
    if (l) {
        libera_lista_rec (l->prox);
        // printf("Liberando '%d' End. %p - ANTES\n", l->info, l);
        free (l);
        // printf("Liberando '%d' End. %p - DEPOIS\n", l->info, l);
    }
}

void imprime_lista (TAluno* l) {

    TAluno *aux = l; 

    // do {printf("%d > ", minha_lista->info);} while (minha_lista = minha_lista->prox);

    while (aux) {
        printf("%d/%.2f > ", aux->mat, aux->cr);
        aux = aux->prox;
    }
    printf("NULL");
}

void imprime_lista_rec (TAluno* l) {

    if (l) {
        printf("%d/%.2f > ", l->mat, l->cr);
        imprime_lista_rec (l->prox);
    } else {
        printf("NULL");
    }
}