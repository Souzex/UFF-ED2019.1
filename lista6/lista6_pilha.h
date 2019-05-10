#ifndef LISTA6_PILHA_H
#define LISTA6_PILHA_H

typedef struct pilha TPilha;

TPilha * inicializa_pilha (void);
void push (TPilha *p, int elem);
int pop (TPilha *p);
void libera_pilha (TPilha *p);
int vazia_pilha (TPilha *p);

void imprime_pilha (TPilha *p);

#endif