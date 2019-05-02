#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int mat;
    char nome[81];
    float cr;
    struct lista *prox;
} TLista;

TLista *insere_final (TLista* l, int x, char *y, float z);
void libera_lista (TLista* l);
void libera_lista_rec (TLista* l);
void imprime_lista (TLista* l);
void imprime_lista_rec (TLista* l);

int igual (TLista *l1, TLista *l2);

int main () {

    TLista *lista1 = NULL, *lista2  = NULL; 

    // printf("lista1: %p\n", lista1);
    // printf("lista2: %p\n", lista2);

    lista1 = insere_final (lista1, 2, "Carlos", 3.0);
    lista1 = insere_final (lista1, 4, "Suzy", 9.0);
    lista1 = insere_final (lista1, 5, "Beltrao", 7.0);
    lista1 = insere_final (lista1, 8, "Pipoco", 5.0);
    lista1 = insere_final (lista1, 1, "Chimbra", 10.0);

    lista2 = insere_final (lista2, 2, "Carlos", 3.0);
    lista2 = insere_final (lista2, 4, "Suzy", 9.0);
    lista2 = insere_final (lista2, 5, "Beltrao", 7.0);
    lista2 = insere_final (lista2, 8, "Pipoco", 5.0);
    lista2 = insere_final (lista2, 1, "Chimbra", 10.0);

    printf("Criada 'lista 1': ");
    imprime_lista (lista1);
    printf("\n");

    printf("Criada 'lista 2': ");
    imprime_lista (lista2);
    printf("\n");

    igual (lista1, lista2) ? printf("Listas IGUAIS!\n") : printf("Listas DIFERENTES!\n");
    
    printf("Liberada 'lista 1': ");
    libera_lista (lista1);
    imprime_lista (lista1);
    printf("\n");

    printf("Liberada 'lista 2': ");
    libera_lista (lista2);
    imprime_lista (lista2);
    printf("\n");    

    return 75;
}

int igual (TLista *l1, TLista *l2) {
   
   while (l1 && l2) {

        if (l1->mat != l2->mat) return 0;
        if (l1->cr  != l2->cr)  return 0;

        int i = 0;
        while (l1->nome[i] != '\0' && l2->nome[i] != '\0')
            if (l1->nome[i] != l2->nome[i++]) return 0;
        if (l1->nome[i] != '\0' || l2->nome[i] != '\0') return 0; // Uma string eh maior que a outra                

        l1 = l1->prox; 
        l2 = l2->prox; 
    }

    if (l1 || l2) return 0; // Uma lista eh maior que a outra
    
    return 1;

/*
    TLista *aux1 = l1, *aux2 = l2;

    while (aux1 && aux2) {

        if (aux1->mat != aux2->mat) return 0;
        if (aux1->cr  != aux2->cr)  return 0;

        int i = 0;
        while (aux1->nome[i] != '\0' && aux2->nome[i] != '\0')
            if (aux1->nome[i] != aux2->nome[i++]) return 0;
        if (aux1->nome[i] != '\0' || aux2->nome[i] != '\0') return 0; // Uma string eh maior que a outra                

        aux1 = aux1->prox; 
        aux2 = aux2->prox; 
    }

    if (aux1 || aux2) return 0; // Uma lista eh maior que a outra
    
    return 1;

*/    
}

TLista *insere_final (TLista* l, int x, char *y, float z) {

    int i;
    TLista *aux, *novo = (TLista *) malloc (sizeof(TLista));
        
    novo->mat = x;
    for (i=0; y[i] != '\0'; i++) novo->nome[i] = y[i];
    novo->cr = z;
    novo->prox = NULL;
    
    if (l) {
        aux = l; 
        for (; aux->prox; aux = aux->prox); 
        aux->prox = novo;
    } else 
        l = novo;
    
    return l;
}

void libera_lista (TLista* l) {
    
    TLista *aux1, *aux2;

    aux1 = l;

    while(aux1) {
        aux2 = aux1;
        aux1 = aux1->prox;
        //printf("Liberando '%d' End. %p - ANTES\n", aux2->info, aux2);
        free (aux2);
        //printf("Liberando '%d' End. %p - DEPOIS\n", aux2->info, aux2);
    }
}

void libera_lista_rec (TLista* l) {
    
    if (l) {
        libera_lista_rec (l->prox);
        // printf("Liberando '%d' End. %p - ANTES\n", l->info, l);
        free (l);
        // printf("Liberando '%d' End. %p - DEPOIS\n", l->info, l);
    }
}

void imprime_lista (TLista* l) {

    TLista *aux = l; 

    // do {printf("%d > ", minha_lista->info);} while (minha_lista = minha_lista->prox);

    while (aux) {
        printf("%d/%s/%.2f > ", aux->mat, aux->nome, aux->cr);
        aux = aux->prox;
    }
    printf("NULL");
}

void imprime_lista_rec (TLista* l) {

    if (l) {
        printf("%d/%s/%.2f > ", l->mat, l->nome, l->cr);
        imprime_lista_rec (l->prox);
    } else {
        printf("NULL");
    }
}