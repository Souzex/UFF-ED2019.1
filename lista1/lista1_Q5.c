#include <stdio.h>

int main() {

    int num=1;
    while(num >= 0) {
        
        printf("Digite um número 'n' para o retorno de sua expressão binária: ");
        scanf("%d",&num);
        
        if(num >= 0) {
            int i = 0;
            char *bin;
            if (num == 0) {
                bin[i] = 0;
                i++;
            } else {
                while (num > 0) {
                    bin[i] = num%2;
                    num /= 2;
                    i++;
                }
            }
            // bin[i] = '\0'; // Segmentation fault (core dumped)
            printf("Em binário: ");
            while(i>0) {
                i--;
                printf("%d", bin[i]);
            }
            printf("\n");
        } else 
            printf("Bye!\n");
    }
    return 75;
}