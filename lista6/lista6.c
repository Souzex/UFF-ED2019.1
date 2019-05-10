#include <stdio.h>
#include <stdlib.h>

#include "lista6_pilha.h"
#include "lista6_fila.h"

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
    
    minha_fila = inicializa_fila();
    for (i=0; i++ < max; insere(minha_fila, rand()%10));
    // for (i=0; i++ < max; push(minha_pilha, rand()%10));
    
    printf("Fila (INPUT) da questão (a): ");
    imprime_fila (minha_fila);
    printf("\n");    

    minha_pilha = f2p (minha_fila);

    printf("Fila (INPUT) da questão (a): ");
    imprime_fila (minha_fila);
    printf("\n");     

    printf("Pilha (OUTPUT) da questão (a): ");
    imprime_pilha (minha_pilha);
    printf("\n");

    libera_fila  (minha_fila);
    libera_pilha (minha_pilha);

// QUESTAO (B)
    printf("************************\n");
    printf("***** QUESTÃO (B) ******\n");
    printf("************************\n");
    
    minha_fila1 = inicializa_fila();
    minha_fila2 = inicializa_fila();
    for (i=0; i++ < max; insere(minha_fila1, rand()%10));
    // for (i=0; i++ < max; push(minha_pilha, rand()%10));
    
    printf("Fila (INPUT) da questão (b): ");
    imprime_fila (minha_fila1);
    printf("\n");    

    minha_fila2 = inv_fila (minha_fila1);

    printf("Fila (INPUT) da questão (b): ");
    imprime_fila (minha_fila1);
    printf("\n");    

    printf("Fila (OUTPUT) da questão (b): ");
    imprime_fila (minha_fila2);
    printf("\n");

    libera_fila (minha_fila1);
    libera_fila (minha_fila2);
    
// QUESTAO (C)
    printf("************************\n");
    printf("***** QUESTÃO (C) ******\n");
    printf("************************\n");

    minha_fila1 = inicializa_fila();
    minha_fila2 = inicializa_fila();
    for (i=0; i++ < max; insere(minha_fila1, rand()%10));
    // for (i=0; i++ < max; push(minha_pilha, rand()%10));
    
    printf("Fila (INPUT) da questão (c): ");
    imprime_fila (minha_fila1);
    printf("\n");    

    minha_fila2 = sep_fila (minha_fila1);

    printf("Fila (INPUT) da questão (c): ");
    imprime_fila (minha_fila1);
    printf("\n"); 

    printf("Fila dos PARES (OUTPUT) da questão (c): ");
    imprime_fila (minha_fila2);
    printf("\n");

    printf("Fila dos IMPARES (OUTPUT) da questão (c): ");
    imprime_fila (minha_fila1);
    printf("\n");    

    libera_fila (minha_fila1);
    libera_fila (minha_fila2);

// QUESTAO (D)
    printf("************************\n");
    printf("***** QUESTÃO (D) ******\n");
    printf("************************\n");

    minha_fila1 = inicializa_fila();
    minha_fila2 = inicializa_fila();
    for (i=0; i++ < max; insere(minha_fila1, rand()%10));
    for (i=0; i++ < max; insere(minha_fila2, rand()%100));
    // for (i=0; i++ < max; push(minha_pilha, rand()%10));
    
    printf("Fila 1 (INPUT) da questão (d): ");
    imprime_fila (minha_fila1);
    printf("\n");    

    printf("Fila 2 (INPUT) da questão (d): ");
    imprime_fila (minha_fila2);
    printf("\n");    

    minha_fila = junta_filas (minha_fila1, minha_fila2);

    printf("Fila 1 (INPUT) da questão (d): ");
    imprime_fila (minha_fila1);
    printf("\n");    

    printf("Fila 2 (INPUT) da questão (d): ");
    imprime_fila (minha_fila2);
    printf("\n");     

    printf("Fila com as duas filas (OUTPUT) da questão (d): ");
    imprime_fila (minha_fila);
    printf("\n");

    libera_fila (minha_fila);
    libera_fila (minha_fila1);
    libera_fila (minha_fila2);          
 
// QUESTAO (E)
    printf("************************\n");
    printf("***** QUESTÃO (E) ******\n");
    printf("************************\n");

    minha_pilha = inicializa_pilha();
    
    for (i=0; i++ < max; push(minha_pilha, rand()%100));
        
    printf("Pilha (INPUT) da questão (e): ");
    imprime_pilha (minha_pilha);
    printf("\n");    

    retira_pares (minha_pilha);

    printf("Pilha sem os nums pares (OUTPUT) da questão (e): ");
    imprime_pilha (minha_pilha);
    printf("\n");

    libera_pilha (minha_pilha);

// QUESTAO (F)
    printf("************************\n");
    printf("***** QUESTÃO (F) ******\n");
    printf("************************\n");

    minha_pilha = inicializa_pilha();
    
    for (i=0; i++ < max; push(minha_pilha, rand()%100));
        
    printf("Pilha (INPUT) da questão (f): ");
    imprime_pilha (minha_pilha);
    printf("\n");    

    minha_fila = p2f (minha_pilha);

    printf("Pilha (INPUT) da questão (f): ");
    imprime_pilha (minha_pilha);
    printf("\n");    

    printf("Fila (OUTPUT) da questão (f): ");
    imprime_fila (minha_fila);
    printf("\n");

    libera_fila  (minha_fila);
    libera_pilha (minha_pilha);    

// QUESTAO (G)
    printf("************************\n");
    printf("***** QUESTÃO (G) ******\n");
    printf("************************\n");

    minha_fila = inicializa_fila();
    for (i=0; i++ < max; insere(minha_fila, rand()%100));

    minha_fila1 = inicializa_fila();
    minha_fila2 = inicializa_fila();

    printf("Fila maior (INPUT) da questão (g): ");
    imprime_fila (minha_fila);
    printf("\n");

    printf("Fila dos nums pares (INPUT) da questão (g): ");
    imprime_fila (minha_fila1);
    printf("\n"); 

    printf("Fila dos nums impares (INPUT) da questão (g): ");
    imprime_fila (minha_fila2);
    printf("\n");             

    separa_filas (minha_fila, minha_fila1, minha_fila2);

    printf("Fila maior (OUTPUT) da questão (g): ");
    imprime_fila (minha_fila);
    printf("\n");

    printf("Fila dos nums pares (OUTPUT) da questão (g): ");
    imprime_fila (minha_fila1);
    printf("\n"); 

    printf("Fila dos nums impares (OUTPUT) da questão (g): ");
    imprime_fila (minha_fila2);
    printf("\n");

    libera_fila (minha_fila);
    libera_fila (minha_fila1);
    libera_fila (minha_fila2); 

    return 75;
}

TPilha* f2p (TFila *f) {

    TPilha *p     = inicializa_pilha();
    TPilha *p_aux = inicializa_pilha();
    TFila  *f_aux = inicializa_fila(); 

    while (!vazia_fila(f)) {
        int info = retira(f);
        push(p_aux, info);
        insere(f_aux, info);
    }

    while (!vazia_fila(f_aux))
        insere(f, retira(f_aux)); 

    while (!vazia_pilha(p_aux))        
        push(p, pop(p_aux));

    libera_pilha (p_aux);
    libera_fila  (f_aux);

    return p;
}

TFila* inv_fila (TFila *f) {

    TPilha *p     = inicializa_pilha();
    TFila  *f_aux = inicializa_fila();

    while (!vazia_fila(f)) {
        int info = retira(f);
        push(p, info);
        insere(f_aux, info);
    }

    while (!vazia_fila(f_aux))
        insere(f, retira(f_aux));     

    while (!vazia_pilha(p))        
        insere(f_aux, pop(p));

    libera_pilha (p);

    return f_aux;  
}

TFila* sep_fila (TFila *f) {

    TFila *f_pares = inicializa_fila();
    TFila *f_impares = inicializa_fila();

    while (!vazia_fila(f)) {
        int info = retira(f);
        info%2 ? insere(f_impares, info) : (insere(f_pares, info));
    }

    while (!vazia_fila(f_impares))
        insere(f, retira(f_impares));

    libera_fila (f_impares);

    return f_pares;
}

TFila* junta_filas (TFila *f1, TFila *f2) {

    TFila *f     = inicializa_fila();
    TFila *f_aux = inicializa_fila();

    while (!vazia_fila(f1)) {
        int info = retira(f1);
        insere(f, info);
        insere(f_aux, info);
    }

    while (!vazia_fila(f_aux))
        insere(f1, retira(f_aux));

    while (!vazia_fila(f2)) {
        int info = retira(f2);
        insere(f, info);
        insere(f_aux, info);
    }        

    while (!vazia_fila(f_aux))
        insere(f2, retira(f_aux));    
    
    libera_fila (f_aux);

    return f;
}

void retira_pares (TPilha *p) {

    TPilha *p_aux = inicializa_pilha();

    while (!vazia_pilha(p)) {
        int info = pop(p);
        info%2 ? push(p_aux, info) : info;
    }

    while (!vazia_pilha(p_aux))
        push(p, pop(p_aux));

    libera_pilha (p_aux);
}

TFila* p2f (TPilha *p) {

    TFila  *f     = inicializa_fila();
    TPilha *p_aux = inicializa_pilha();

    while (!vazia_pilha(p)) {
        int info = pop(p);
        insere(f, info);
        push(p_aux, info);
    }

    while (!vazia_pilha(p_aux))
        push(p, pop(p_aux));

    libera_pilha (p_aux);

    return f;
}

void separa_filas (TFila * f, TFila *par, TFila * impar) {

    TFila *f_aux = inicializa_fila();

    while (!vazia_fila(f)) {
        int info = retira(f);
        info % 2 ? insere(impar, info) : (insere(par, info));
        insere(f_aux, info);
    }

    while (!vazia_fila(f_aux))
        insere(f, retira(f_aux));

    libera_fila (f_aux);
}
