#include <stdio.h>

void shift_troca_string (char *str);

int main() {

    while(1) {
        
        char *palavra;
        printf("Escreva uma palavra para troca de letras: ");
        scanf("%s",palavra); // %s faz toda a diferença em relação a %c
        
        shift_troca_string (palavra);
        
        printf("A palavra trocada é: ");
        int i=0;
        // while (palavra[i]) printf("%c", palavra[i++]);
        for(; palavra[i]; printf("%c", palavra[i++]));
        printf("\n");

    }
    return 75;
}

void shift_troca_string (char *str) {
    
    int i=0;
    while (str[i]) 
        if (str[i] == 'a')
            str[i++] = 'Z';
        else if (str[i] == 'A')
            str[i++] = 'z';
        else if (str[i] >= 66 && str[i] <= 90) // maiusculas
            str[i++] += 31;
        else if (str[i] >= 98 && str[i] <= 122) // minusculas
            str[i++] -= 33;
        else 
            str[i++] = '!';
}