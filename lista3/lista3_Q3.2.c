#include <stdio.h>
#include <stdlib.h>

void transf_i_p (int *vet, int n);

int main() {

    while(1) {
        
        int i, tam, num; 
        printf("Informe o tamanho do vetor: ");
        scanf("%d",&tam); 

        // int vetor[tam]; ERROR: CORE DUMPED
        int *vetor = (int *) malloc(sizeof(int)*tam);
        printf("Digite os inteiros: ");
        for(i=0; i<tam; scanf("%d",&vetor[i++]));

        printf("O vetor original é: \n");
        printf("[");
        for(i=0; i<tam; printf("%d ",vetor[i++]));
        printf("]\n");

        // printf("ANTES - End. de vetor: %p\n", vetor);
        transf_i_p (vetor, tam); // transf_i_p (&vetor[0], tam);
        // printf("DEPOIS - End. de vetor: %p\n", vetor);
        
        printf("O vetor com pares e ímpares separados é: \n");
        printf("[");
        for(i=0; i<tam; printf("%d ", vetor[i++]));
        printf("]\n");
        free(vetor);
    }
    return 75;
}

void transf_i_p (int *vet, int n) {
    
    int i, par=0, impar=0;
    // int *vet_transf = (int *) malloc(sizeof(int)*n); // FUNCIONA, mas eh desnecessario.
    int vet_transf[n];
    
    for(i=0; i<n; vet[i++]%2==0 ? par++ : par);
    impar = par;
    par = 0;
    for(i=0; i<n; vet[i]%2==0 ? (vet_transf[par++] = vet[i++]) : (vet_transf[impar++] = vet[i++]));
    
    // printf("antes - End. de vet: %p\n", vet);
    // vet = vet_transf; // ATE FUNCIONA!!! Porem so no escopo de "transf_i_p", mesmo com o malloc acima.
    // printf("depois - End. de vet: %p\n", vet);
    // printf("End. de vet_transf: %p\n", vet_transf);
    for(i=0; i<n; vet[i] = vet_transf[i++]);
}

/*
"vet = vet_transf;" nao atende porque...
1. "vet" possui um escopo acima, embora "vet" e "vet_transf" estejam alocadas no heap.
1.1 Quando sai de "transf_i_p", "vet" retoma seu endereco original ("vetor" em main).
1.2 Eh como se a lista de enderecos de "vet" estivesse em um local diferente da lista de "vet_transf".
1.3 Eh como se para "vet" (ou "vetor" no escopo do main) houvesse uma declaracao implicita default de que seu conteudo (um ponteiro ou endereco) nao pode ser mudado.

*/