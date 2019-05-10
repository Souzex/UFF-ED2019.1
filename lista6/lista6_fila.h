#ifndef LISTA6_FILA_H
#define LISTA6_FILA_H

typedef struct fila TFila;

TFila* inicializa_fila (void);
void insere (TFila *f, int elem);
int retira (TFila *f);
void libera_fila (TFila *f);
int vazia_fila (TFila *f);

void imprime_fila (TFila *f);

#endif