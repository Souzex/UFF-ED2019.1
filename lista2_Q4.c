#include <stdio.h>

int main() {

    int num=1;
    while(num > 0) {
        
        printf("Digite um número para saber se ele é palíndromo: ");
        scanf("%d",&num);
        
        if(num > 0) {

            int tamanho = 0;
            int denominador = num;
            do tamanho++; while ((denominador /= 10) != 0);
            
            if (tamanho%2 != 0)
                printf("FALSO!");
            else {
                char palindromo[tamanho+1];
                int i = tamanho;
                denominador = num;
                palindromo[i] = '\0';
                do palindromo[--i] = denominador%10; while ((denominador /= 10) != 0);
                
                for(i=0; palindromo[i] == palindromo[tamanho-i-1] && i<tamanho/2; i++);
                if (i==tamanho/2)
                    printf("VERDADEIRO!");
                else
                    printf("FALSO!");
            }
            printf("\n");
        
        } else 
            printf("Bye!\n");
    }
    return 75;
}
