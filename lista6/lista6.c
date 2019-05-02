// #include <pilha.h>
// #include <fila.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int info;
    struct node *prox;
} TNO;

// <pilha.h>
typedef struct pilha {
    TNO *prim;
} TPilha;

TPilha * inicializa_TPilha (void); // TPilha * inicializa (void);
void push (TPilha *p, int elem);
int pop (TPilha *p);
void libera_TPilha (TPilha *p); // void libera (TPilha *p);
int vazia_TPilha (TPilha *p); // int vazia (TPilha *p);

TPilha * inicializa_TPilha (void) { // TPilha * inicializa (void) {
    
    TPilha *p = (TPilha *) malloc (sizeof(TPilha));
    p->prim = NULL;
    return p;
}

void push (TPilha *p, int elem) {

    TNO *novo = (TNO *) malloc (sizeof(TNO));
    novo->info = elem;
    novo->prox = p->prim;
    p->prim = novo;
}

int pop (TPilha *p) {

    if (vazia_TPilha(p)) exit(1);
    int resp = p->prim->info;
    TNO *q = p->prim;
    p->prim = q->prox;
    free (q);
    return resp;
}

void libera_TPilha (TPilha *p) { // void libera (TPilha *p) { 
    
    TNO *q = p->prim, *t;
    while (q) {
        t = q;
        q = q->prox;
        free (t);
    }
    free (p);
}

int vazia_TPilha (TPilha *p) { // int vazia (TPilha *p) {
    
    return p->prim == NULL;
}

// <fila.h>
typedef struct fila {
    TNO *ini, *fim;
} TFila;

TFila* inicializa_TFila (void); // TFila* inicializa (void);
void insere (TFila *f, int elem);
int retira (TFila *f);
void libera_TFila (TFila *f); // void libera (TFila *f);
int vazia_TFila (TFila *f); // int vazia (TFila *f);

TFila* inicializa_TFila (void) { // TFila* inicializa (void) {

    TFila *f = (TFila *) malloc(sizeof(TFila));
    f->ini = f->fim = NULL;
}

void insere (TFila *f, int elem) {

    TNO *novo = (TNO *) malloc (sizeof(TNO));
    novo->info = elem;
    novo->prox = NULL;
    if (vazia_TFila(f))
        f->ini = f->fim = novo;
    else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

int retira (TFila *f) {

    if (vazia_TFila(f)) exit(1);
    int resp = f->ini->info;
    TNO *q = f->ini;
    f->ini = f->ini->prox;
    if(!f->ini) f->fim = NULL;
    free (q);
    return resp;
}

void libera_TFila (TFila *f) { // void libera (TFila *f) {

    TNO *q = f->ini, *t;
    while (q) {
        t = q;
        q = q->prox;
        free (t);
    }
    free (f);    
}

int vazia_TFila (TFila *f) { /// int vazia (TFila *f) {

    return f->ini == NULL;
}

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

void imprime_lista (TNO* l);

TPilha* f2p (TFila *f);
TFila* inv_fila (TFila *f);
TFila* sep_fila (TFila *f);
TFila* junta_filas (TFila *f1, TFila *f2);
void retira_pares (TPilha *p);
TFila* p2f (TPilha *p);
void separa_filas (TFila * f, TFila *par, TFila * impar);

int main() {

    int i, max = 7;
    TPilha *minha_pilha;
    TFila *minha_fila, *minha_fila1, *minha_fila2;

// QUESTAO (A)
    printf("************************\n");
    printf("***** QUESTÃO (A) ******\n");
    printf("************************\n");
    
    minha_fila = inicializa_TFila();
    for (i=0; i++ < max; insere(minha_fila, rand()%10));
    // for (i=0; i++ < max; push(minha_pilha, rand()%10));
    
    printf("Fila (INPUT) da questão (a): ");
    imprime_lista (minha_fila->ini);
    printf("\n");    

    minha_pilha = f2p (minha_fila);

    printf("Pilha (OUTPUT) da questão (a): ");
    imprime_lista (minha_pilha->prim);
    printf("\n");

    libera_TFila (minha_fila);
    libera_TPilha (minha_pilha);

// QUESTAO (B)
    printf("************************\n");
    printf("***** QUESTÃO (B) ******\n");
    printf("************************\n");
    
    minha_fila1 = inicializa_TFila();
    minha_fila2 = inicializa_TFila();
    for (i=0; i++ < max; insere(minha_fila1, rand()%10));
    // for (i=0; i++ < max; push(minha_pilha, rand()%10));
    
    printf("Fila (INPUT) da questão (b): ");
    imprime_lista (minha_fila1->ini);
    printf("\n");    

    minha_fila2 = inv_fila (minha_fila1);

    printf("Fila (OUTPUT) da questão (b): ");
    imprime_lista (minha_fila2->ini);
    printf("\n");

    libera_TFila (minha_fila1);
    libera_TFila (minha_fila2);
    
// QUESTAO (C)
    printf("************************\n");
    printf("***** QUESTÃO (C) ******\n");
    printf("************************\n");

    minha_fila1 = inicializa_TFila();
    minha_fila2 = inicializa_TFila();
    for (i=0; i++ < max; insere(minha_fila1, rand()%10));
    // for (i=0; i++ < max; push(minha_pilha, rand()%10));
    
    printf("Fila (INPUT) da questão (c): ");
    imprime_lista (minha_fila1->ini);
    printf("\n");    

    minha_fila2 = sep_fila (minha_fila1);

    printf("Fila dos PARES (OUTPUT) da questão (c): ");
    imprime_lista (minha_fila2->ini);
    printf("\n");

    printf("Fila dos IMPARES (OUTPUT) da questão (c): ");
    imprime_lista (minha_fila1->ini);
    printf("\n");    

    libera_TFila (minha_fila1);
    libera_TFila (minha_fila2);

// QUESTAO (D)
    printf("************************\n");
    printf("***** QUESTÃO (D) ******\n");
    printf("************************\n");

    minha_fila1 = inicializa_TFila();
    minha_fila2 = inicializa_TFila();
    for (i=0; i++ < max; insere(minha_fila1, rand()%10));
    for (i=0; i++ < max; insere(minha_fila2, rand()%100));
    // for (i=0; i++ < max; push(minha_pilha, rand()%10));
    
    printf("Fila 1 (INPUT) da questão (d): ");
    imprime_lista (minha_fila1->ini);
    printf("\n");    

    printf("Fila 2 (INPUT) da questão (d): ");
    imprime_lista (minha_fila2->ini);
    printf("\n");    

    minha_fila = junta_filas (minha_fila1, minha_fila2);

    printf("Fila com as duas filas (OUTPUT) da questão (d): ");
    imprime_lista (minha_fila->ini);
    printf("\n");

    libera_TFila (minha_fila);
    libera_TFila (minha_fila1);
    libera_TFila (minha_fila2);          
 
// QUESTAO (E)
    printf("************************\n");
    printf("***** QUESTÃO (E) ******\n");
    printf("************************\n");

    minha_pilha = inicializa_TPilha();
    
    for (i=0; i++ < max; push(minha_pilha, rand()%100));
        
    printf("Pilha (INPUT) da questão (e): ");
    imprime_lista (minha_pilha->prim);
    printf("\n");    

    retira_pares (minha_pilha);

    printf("Pilha sem os nums pares (OUTPUT) da questão (e): ");
    imprime_lista (minha_pilha->prim);
    printf("\n");

    libera_TPilha (minha_pilha);

// QUESTAO (F)
    printf("************************\n");
    printf("***** QUESTÃO (F) ******\n");
    printf("************************\n");

    minha_pilha = inicializa_TPilha();
    
    for (i=0; i++ < max; push(minha_pilha, rand()%100));
        
    printf("Pilha (INPUT) da questão (f): ");
    imprime_lista (minha_pilha->prim);
    printf("\n");    

    minha_fila = p2f (minha_pilha);

    printf("Fila (OUTPUT) da questão (f): ");
    imprime_lista (minha_fila->ini);
    printf("\n");

    libera_TFila (minha_fila);
    libera_TPilha (minha_pilha);    

// QUESTAO (G)
    printf("************************\n");
    printf("***** QUESTÃO (G) ******\n");
    printf("************************\n");

    minha_fila = inicializa_TFila();
    for (i=0; i++ < max; insere(minha_fila, rand()%100));

    minha_fila1 = inicializa_TFila();
    minha_fila2 = inicializa_TFila();

    printf("Fila maior (INPUT) da questão (g): ");
    imprime_lista (minha_fila->ini);
    printf("\n");

    printf("Fila dos nums pares (INPUT) da questão (g): ");
    imprime_lista (minha_fila1->ini);
    printf("\n"); 

    printf("Fila dos nums impares (INPUT) da questão (g): ");
    imprime_lista (minha_fila2->ini);
    printf("\n");             

    separa_filas (minha_fila, minha_fila1, minha_fila2);

    printf("Fila maior (OUTPUT) da questão (g): ");
    imprime_lista (minha_fila->ini);
    printf("\n");

    printf("Fila dos nums pares (OUTPUT) da questão (g): ");
    imprime_lista (minha_fila1->ini);
    printf("\n"); 

    printf("Fila dos nums impares (OUTPUT) da questão (g): ");
    imprime_lista (minha_fila2->ini);
    printf("\n");

    libera_TFila (minha_fila);
    libera_TFila (minha_fila1);
    libera_TFila (minha_fila2); 

    return 75;
}

TPilha* f2p (TFila *f) {

    TPilha *p = inicializa_TPilha();
    TPilha *p_aux = inicializa_TPilha();
    
    while (f->ini) {
        push(p_aux, f->ini->info);
        f->ini = f->ini->prox;
    }

    while (!vazia_TPilha(p_aux))        
        push(p, pop(p_aux));

    libera_TPilha (p_aux);

    return p;
}

TFila* inv_fila (TFila *f) {

    TPilha *p = inicializa_TPilha();
    TFila *f_aux = inicializa_TFila();

    while (f->ini) {
        push(p, f->ini->info);
        f->ini = f->ini->prox;
    }

    while (!vazia_TPilha(p))        
        insere(f_aux, pop(p));

    libera_TPilha (p);

    return f_aux;    
}

TFila* sep_fila (TFila *f) {

    TFila *f_pares = inicializa_TFila();
    TFila *f_impares = inicializa_TFila();

    while (!vazia_TFila(f)) {
        int info = retira(f);
        info%2 ? insere(f_impares, info) : (insere(f_pares, info));
    }

    while (!vazia_TFila(f_impares))
        insere(f, retira(f_impares));

    libera_TFila (f_impares);

    return f_pares;
}

TFila* junta_filas (TFila *f1, TFila *f2) {

    TFila *f = inicializa_TFila();
    
    while (f1->ini) {
        insere(f, f1->ini->info);
        f1->ini = f1->ini->prox;
    }

    while (f2->ini) {
        insere(f, f2->ini->info);
        f2->ini = f2->ini->prox;
    }    

    return f;
}

void retira_pares (TPilha *p) {

    TPilha *p_aux = inicializa_TPilha();

    while (!vazia_TPilha(p)) {
        int info = pop(p);
        info%2 ? push(p_aux, info) : info;
    }

    while (!vazia_TPilha(p_aux))
        push(p, pop(p_aux));

    libera_TPilha (p_aux);
}

TFila* p2f (TPilha *p) {

    TFila *f = inicializa_TFila();
    
    while (p->prim) {
        insere(f, p->prim->info);
        p->prim = p->prim->prox;
    }

    return f;
}

void separa_filas (TFila * f, TFila *par, TFila * impar) {

/* // Está errado! Acaba por apontar o início da fila para NULL.
    TFila *f_aux = f;
    
    while(f_aux->ini) {
        f_aux->ini->info % 2 ? insere(impar, f_aux->ini->info) : (insere(par, f_aux->ini->info));
        f_aux->ini = f_aux->ini->prox;
    }
*/
    TNO *no = f->ini;

    while(no) {
        no->info % 2 ? insere(impar, no->info) : (insere(par, no->info));
        no = no->prox;
    }
}

void imprime_lista (TNO* l) {

    while (l) {
        printf("%d > ", l->info);
        l = l->prox;
    }
    printf("NULL");
}