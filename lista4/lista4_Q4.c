#include <stdio.h>
#include <stdlib.h>

int **matriz_hadamard(int n);
void free_matrix(int **matrix, int n);

int main() {

    int dim = 1;

    while(dim > 0) {
        
        printf("Informe a dimensão da matriz de Hadamard H(N): ");
        scanf("%d",&dim); 

        if(dim > 0) {
            
            int i, j, pot2 = dim;

            while (!(pot2%2)) pot2 /= 2;
            
            if (pot2 == 1) {
                
                // int hadamard[dim][dim];
                int **hadamard;

                hadamard = matriz_hadamard(dim);

                for(i=0; i < dim; i++) {
                    for(j=0; j < dim; j++) 
                        printf(" %d", hadamard[i][j]);
                    printf("\n");
                }

                free_matrix(hadamard, dim);

            } else {
                printf("Apenas potências de 2, por favor!\n");
            }

        } else
            printf("Bye!\n");
    }
    return 75;
}

int **matriz_hadamard(int n) {

    int i, j;
    int **hadamard_new;
    int **hadamard = (int **) malloc(sizeof(int*)*n);

    for(i=0; i<n; i++)
        hadamard[i] = (int *) malloc(sizeof(int)*n);

    if(n==1)
        hadamard[0][0] = 1;
    else {

        hadamard_new = matriz_hadamard(n/2);
        for(i=0; i < n/2; i++) 
            for(j=0; j < n/2; j++) 
                hadamard[i][j] = hadamard_new[i][j];
        for(i=0; i < n/2; i++) 
            for(j=n/2; j < n; j++) 
                hadamard[i][j] = hadamard_new[i][j-n/2];
        for(i=n/2; i < n; i++) 
            for(j=0; j < n/2; j++) 
                hadamard[i][j] = hadamard_new[i-n/2][j];
        for(i=n/2; i < n; i++) 
            for(j=n/2; j < n; j++) 
                hadamard[i][j] = !hadamard_new[i-n/2][j-n/2];
               
        free_matrix(hadamard_new, n/2);
    }
    return hadamard;
}


void free_matrix(int **matrix, int n) {

    int i;
    for(i=0; i<n; free(matrix[i++]));
    free(matrix);
}