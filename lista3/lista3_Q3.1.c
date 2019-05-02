#include <stdio.h>
#include <stdlib.h>

int* transf_i_p (int *vet, int n);

int main() {

    while(1) {
        
        int i, tam, num; 
        printf("Informe o tamanho do vetor: ");
        scanf("%d",&tam); 

        int vetor[tam], *vetor_transf;
        printf("Digite os inteiros: ");
        for(i=0; i<tam; scanf("%d",&vetor[i++]));

        printf("O vetor original é: \n");
        printf("[");
        for(i=0; i<tam; printf("%d ",vetor[i++]));
        printf("]\n");

        // vetor_transf = transf_i_p (&vetor[0], tam);
        vetor_transf = transf_i_p (vetor, tam);
        
        printf("O vetor com pares e ímpares separados é: \n");
        printf("[");
        for(i=0; i<tam; printf("%d ", vetor_transf[i++]));
        printf("]\n");
        free(vetor_transf);
    }
    return 75;
}

int* transf_i_p (int *vet, int n) {
    
    int i, par=0, impar=0;
    // int vet_transf[n]; // SEGMENTATION FAULT: Variavel local no "return".
    int *vet_transf = (int *) malloc(sizeof(int)*n);
    
    for(i=0; i<n; vet[i++]%2==0 ? par++ : par);
    impar = par;
    par = 0;
    for(i=0; i<n; vet[i]%2==0 ? (vet_transf[par++] = vet[i++]) : (vet_transf[impar++] = vet[i++]));

/*
    for(i=0; i<n; i++)
        if (vet[i]%2==0)
            par++;
    impar = par;
    par = 0;
    for(i=0; i<n; i++)
        if (vet[i]%2==0)
            vet_transf[par++] = vet[i];
        else
            vet_transf[impar++] = vet[i];
*/

    return vet_transf;
}

