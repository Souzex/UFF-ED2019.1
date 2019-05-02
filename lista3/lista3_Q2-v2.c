#include <stdio.h>
#include <stdlib.h>

char * codifica (char *str);

int main() {

    while(1) {
        
        // char *palavra, *trocada; // Por causa de *palavra ocorre segmentation fault
        char palavra[100], *trocada; 
        printf("Escreva uma palavra para troca de letras: ");
        scanf("%s",palavra); // %s faz toda a diferença em relação a %c
        // printf("TESTE: A palavra digitada é: %s\n", palavra);

        trocada = codifica (palavra);
        printf("A palavra trocada é: %s\n", trocada);
        // for(i=0; trocada[i]; printf("%c", trocada[i++]));
        free(trocada);
    }
    return 75;
}

char * codifica (char *str) {
    
    int i;
    for(i=0; str[i]; i++);
    char *troca = (char *) malloc(sizeof(char)*i); // 1a entrada: a partir de tamanho 4 fica ruim

    i=0;
    do {
        if (str[i] >= 97 && str[i] <= 122) // Versao do enunciado: minusculas
            troca[i] = '?';
        else
            troca[i] = str[i];        
    } while (str[i++]);
    troca[i] = '\0';

    return troca;
}

/*
// Versao do exemplo: vogais minusculas
    i=0;
    do {
        if (str[i] == 'a'
         || str[i] == 'e'
         || str[i] == 'i'
         || str[i] == 'o'
         || str[i] == 'u')
            troca[i] = '?';
        else
            troca[i] = str[i];
    } while (str[i++]);
    troca[i] = '\0';            
*/