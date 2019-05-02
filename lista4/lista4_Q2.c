#include <stdio.h>
#include <stdlib.h>

// "int **mult", "int** mult", "int ** mult" ou "int * * mult": tanto faz!
int ** mult (int m1, int n1, int **mat1, int m2, int n2, int **mat2);
void free_matrix(int **matrix, int n);

int main() {

    while(1) {
        
        int i, j;
        int lin1 = 2, col1 = 2;
        int lin2 = 2, col2 = 3;
/*      // SEGMENTATION FAULT
        // "note: expected ‘int **’ but argument is of type ‘int (*)[2]’"
        int fator1[2][2] = { {2, 5},
                             {1, 7} };
        // "note: expected ‘int **’ but argument is of type ‘int (*)[3]’"
        int fator2[2][3] = { {2, 5, 3},
                             {1, 2, 3} };                                   
*/
///*
        int **fator1 = (int **) malloc (sizeof(int *)*lin1);
        int **fator2 = (int **) malloc (sizeof(int *)*lin2);

        for(i=0; i < lin1; i++)
            fator1[i] = (int *) malloc (sizeof(int)*col1);
        for(i=0; i < lin2; i++)
            fator2[i] = (int *) malloc (sizeof(int)*col2);
        
        fator1[0][0] = 2; fator1[0][1] = 5;
        fator1[1][0] = 1; fator1[1][1] = 7;

        fator2[0][0] = 2; fator2[0][1] = 5; fator2[0][2] = 3;
        fator2[1][0] = 1; fator2[1][1] = 2; fator2[1][2] = 3;
//*/                
        int **produto = mult (lin1, col1, fator1, lin2, col2, fator2);

        for(i=0; i < lin1; i++) {
            for(j=0; j < col2; j++) {
                if (produto[i][j] > 99 || produto[i][j] < -99)
                    printf(" ");
                else if (produto[i][j] > 9 || produto[i][j] < -9)     
                    printf("  ");
                else 
                    printf("   ");
                printf("%d", produto[i][j]);
            }
            printf("\n");
        }

        free_matrix(fator1, lin1);
        free_matrix(fator2, lin2);
        free_matrix(produto, lin1);

        break;
    }
    return 75;
}

int** mult (int m1, int n1, int **mat1, int m2, int n2, int **mat2) {

    int i, j, k, l;
    int **multiplica = (int **) malloc (sizeof(int *)*m1);
    for(i=0; i < m1; i++)
        multiplica[i] = (int *) malloc (sizeof(int)*n2);
        // *multiplica++ = (int *) malloc (sizeof(int)*n2); // SEGMENTATION FAULT

    for(i=0; i < m1; i++)
        for(k=0; k < n2; k++)
            for(j=0; j < n1; j++)
                for(l=0; l < m2; l++)
                    if (j==l)
                        multiplica[i][k] += mat1[i][j]*mat2[l][k];

    return multiplica;
}

void free_matrix(int **matrix, int n) {

    int i;
    for(i=0; i<n; free(matrix[i++]));
    free(matrix);
}