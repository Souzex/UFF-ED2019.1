#include <stdio.h>
#include <stdlib.h>

// char * codifica (char *str);
void codifica (char *str);

int main() {

    while(1) {
                
        char *palavra, *trocada; 
        printf("Escreva uma palavra para troca de letras: ");
        scanf("%s",palavra); // %s faz toda a diferença em relação a %c
        
        codifica (palavra);

        // trocada = codifica (palavra);
        // printf("A palavra trocada é: %s\n", trocada);
        // free(trocada);
    }
    return 75;
}

void codifica (char *str) {
// char * codifica (char *str) {
    
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

    printf("A palavra trocada é: %s\n", troca);
    // for(i=0; troca[i]; printf("%c", troca[i++])); printf("\n");
    free(troca);

    // return troca;
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

