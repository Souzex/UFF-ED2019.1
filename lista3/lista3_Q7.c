#include <stdio.h>
#include <stdlib.h>

char * string_match (char *str1, char *str2);

int main() {

    while(1) {
        
        char string1[100], string2[100], *substring; 
        
        printf("Informe a 1a string: ");
        scanf("%s",string1); 
        printf("Informe a 2a string: ");
        scanf("%s",string2); 

        // printf("ANT - End. de 'substring': %p\n", substring);
        substring = string_match (string1, string2);
        // printf("DEP - End. de 'substring': %p\n", substring);

        !substring[0] ? printf("Nenhuma substring em comum!\n") : printf("A maior substring existente entre as duas strings eh: %s\n", substring);
        
        free(substring);
    }
    return 75;
}

char * string_match (char *str1, char *str2) {

    int i, j, cursor, atual, maxim;
    
    for(i=0; str1[i]; i++);
    for(j=0; str2[j]; j++);
    i <= j ? i : (i = j);
    
    char *substr_maxim = (char *) malloc (sizeof(char)*(i+1));
    // char *substr_atual = (char *) malloc (sizeof(char)*(i+1)); // OKAY!
    // char substr_maxim[i+1]; // SEGMENTATION FAULT
    char substr_atual[i+1];
    
    substr_maxim[0] = '\0';
    substr_atual[0] = '\0';
    atual = 0; maxim = 0;
    cursor = 0; i = 0; j = 0;
    while(str1[i]) {

        while(str2[j]) {

            if (str1[i] == str2[j]) {
                substr_atual[atual] = str2[j]; 
                atual++; 
                i++; 
                j++;
                /* 
                printf("STRING ATUAL: %s\n", substr_atual);
                printf("ATUAL: %d\n", atual);
                printf("I: %d ", i);
                printf("J: %d ", j);
                printf("CURSOR: %d\n", cursor);
                */
            } else {
                if (maxim < atual) {
                    int k;
                    for(k=0; k<atual; substr_maxim[k] = substr_atual[k++]);
                    substr_maxim[k] = '\0';
                    maxim = atual;
                }
                if (i == cursor)
                    j++;
                i = cursor;
                substr_atual[0] = '\0';
                atual = 0;
                /*
                printf("STRING ATUAL: %s\n", substr_atual);
                printf("ATUAL: %d\n", atual);
                printf("STRING MAXIM: %s\n", substr_maxim);
                printf("MAXIM: %d\n", maxim);
                printf("I: %d ", i);
                printf("J: %d ", j);
                printf("CURSOR: %d\n", cursor);
                */
            }            
        }
        if (maxim < atual) {
            int k;
            for(k=0; k<atual; substr_maxim[k] = substr_atual[k++]);
            substr_maxim[k] = '\0';
            maxim = atual;
        }
        substr_atual[0] = '\0';
        atual = 0;
        i = ++cursor;
        j = 0;
        /*
        printf("STRING ATUAL: %s\n", substr_atual);
        printf("ATUAL: %d\n", atual);
        printf("STRING MAXIM: %s\n", substr_maxim);
        printf("MAXIM: %d\n", maxim);
        printf("I: %d ", i);
        printf("J: %d ", j);
        printf("CURSOR: %d\n", cursor);
        */        
    }
    return substr_maxim;
}

// YUYUY e YUY
// UYUY e YUY
// ACCTGAACTCCCCCC e ACCTAGGACCCCCC
// AYYYYYACTCCCCCCCCCCC e AYYYYYACCCCCCCCCCCCC
// AYYYYYACTCCCC e AYYYYYACCCC
/*
1. Sem "free(substring);", o S.O. aloca memoria em regioes diferentes, porem contiguas.
2. Com "free(substring);", o S.O. aloca memoria sempre no mesmo endereco.
2.1 Curiosamente a partir da 2a execucao, o endereco ja eh atribuido logo apos "char *substring;", sem "malloc" algum.
2.1.1 Na 1a execucao, antes de passar pelo "malloc" de "string_match (string1, string2);", o endereco eh NULL.
*/