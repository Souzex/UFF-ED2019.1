#include <stdio.h>
#include <stdlib.h>

int main() {

    while(1) {
        /*
        int sodoku[9][9] = { {5, 3, 4, 6, 7, 8, 9, 1, 2},
                             {6, 7, 2, 1, 9, 5, 3, 4, 8},
                             {1, 9, 8, 3, 4, 2, 5, 6, 7},
                             {8, 5, 9, 7, 6, 1, 4, 2, 3},
                             {4, 2, 6, 8, 5, 3, 7, 9, 1},
                             {7, 1, 3, 9, 2, 4, 8, 5, 6},
                             {9, 6, 1, 5, 3, 7, 2, 8, 4},
                             {2, 8, 7, 4, 1, 9, 6, 3, 5},
                             {3, 4, 5, 2, 8, 6, 1, 7, 9} };        
        */
        // int sodoku[9][9] = {5, 3, 4, 6, 7, 8, 9, 1, 2, 6, 7, 2, 1, 9, 5, 3, 4, 8, 1, 9, 8, 3, 4, 2, 5, 6, 7, 8, 5, 9, 7, 6, 1, 4, 2, 3, 4, 2, 6, 8, 5, 3, 7, 9, 1, 7, 1, 3, 9, 2, 4, 8, 5, 6, 9, 6, 1, 5, 3, 7, 2, 8, 4, 2, 8, 7, 4, 1, 9, 6, 3, 5, 3, 4, 5, 2, 8, 6, 1, 7, 9};
        // int sodoku[][9]  = {5, 3, 4, 6, 7, 8, 9, 1, 2, 6, 7, 2, 1, 9, 5, 3, 4, 8, 1, 9, 8, 3, 4, 2, 5, 6, 7, 8, 5, 9, 7, 6, 1, 4, 2, 3, 4, 2, 6, 8, 5, 3, 7, 9, 1, 7, 1, 3, 9, 2, 4, 8, 5, 6, 9, 6, 1, 5, 3, 7, 2, 8, 4, 2, 8, 7, 4, 1, 9, 6, 3, 5, 3, 4, 5, 2, 8, 6, 1, 7, 9};
        // int sodoku[9][9] = {0}; // int sodoku[9][9] = {{0}} ou int sodoku[9][9] = {{}}
        
        int i, j, k, not_valid = 0;
        // int **sodoku = (int **) malloc (sizeof(int *)*9);
        // for(i=0; i < 9; i++)
            //sodoku[i] = (int *) malloc (sizeof(int)*9);
            ////*sodoku++ = (int *) malloc (sizeof(int)*9);
        
        int sodoku[9][9] = { {5, 3, 4, 6, 7, 8, 9, 1, 2},
                             {6, 7, 2, 1, 9, 5, 3, 4, 8},
                             {1, 9, 8, 3, 4, 2, 5, 6, 7},
                             {8, 5, 9, 7, 6, 1, 4, 2, 3},
                             {4, 2, 6, 8, 5, 3, 7, 9, 1},
                             {7, 1, 3, 9, 2, 4, 8, 5, 6},
                             {9, 6, 1, 5, 3, 7, 2, 8, 4},
                             {2, 8, 7, 4, 1, 9, 6, 3, 5},
                             {3, 4, 5, 2, 8, 6, 1, 7, 9} };

        int count_sect[9][9] = {};
        for(i=0; i < 9; i++) {
            
            int count_lin[9] = {}; // desaloca e cria espaço de memória a cada iteracao?
            int count_col[9] = {};
            for(j=0; j < 9; j++) {
                count_lin[sodoku[i][j]-1]++; // check linhas 
                count_col[sodoku[j][i]-1]++; // check colunas

                int sector; // check setores (blocos)
                if ((i == 0 || i == 1 || i == 2) && (j == 0 || j == 1 || j == 2)) sector = 0;
                if ((i == 0 || i == 1 || i == 2) && (j == 3 || j == 4 || j == 5)) sector = 1;
                if ((i == 0 || i == 1 || i == 2) && (j == 6 || j == 7 || j == 8)) sector = 2;
                if ((i == 3 || i == 4 || i == 5) && (j == 0 || j == 1 || j == 2)) sector = 3;
                if ((i == 3 || i == 4 || i == 5) && (j == 3 || j == 4 || j == 5)) sector = 4;
                if ((i == 3 || i == 4 || i == 5) && (j == 6 || j == 7 || j == 8)) sector = 5;
                if ((i == 6 || i == 7 || i == 8) && (j == 0 || j == 1 || j == 2)) sector = 6;
                if ((i == 6 || i == 7 || i == 8) && (j == 3 || j == 4 || j == 5)) sector = 7;
                if ((i == 6 || i == 7 || i == 8) && (j == 6 || j == 7 || j == 8)) sector = 8;                                
                
                count_sect[sector][sodoku[j][i]-1]++; // check setores (blocos)                
            }
          
            for(k=0; k<9; count_lin[k++] == 0 ? not_valid = 1 : not_valid);
            if(not_valid) break; // check linhas
            for(k=0; k<9; count_col[k++] == 0 ? not_valid = 1 : not_valid);
            if(not_valid) break; // check colunas
           
        }

        if(not_valid);
        else
            for(i=0; i<9; i++) {
                for(j=0; j<9; count_sect[i][j++] == 0 ? not_valid = 1 : not_valid);
                if (not_valid) break; // check setores (blocos)
            }

        not_valid ? printf("Solução NÃO válida do Sodoku!\n") : printf("Solução VÁLIDA do Sodoku!\n");
/*
        for(i=0; i < 9; i++)
            for(j=0; j < 9; j++)
                printf("sect_%d e num_%d: %d\n", i+1, j+1, count_sect[i][j]);  
*/
        break;
    }
    return 75;
}

        /*
        5 3 4 6 7 8 9 1 2
        6 7 2 1 9 5 3 4 8
        1 9 8 3 4 2 5 6 7
        8 5 9 7 6 1 4 2 3
        4 2 6 8 5 3 7 9 1
        7 1 3 9 2 4 8 5 6
        9 6 1 5 3 7 2 8 4
        2 8 7 4 1 9 6 3 5
        3 4 5 2 8 6 1 7 9
        */
        /* int exemplo[2][3][4] = { 
                                    { {0,1,2,3},     {4,5,6,7},     {8,9,10,11}   },
                                    { {12,13,14,15}, {16,17,18,19}, {20,21,22,23} }
                                  };
        */