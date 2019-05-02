#include <stdio.h>

int main() {

    int num=1;
    while(num > 0) {
        
        printf("Digite um número 'n' para que sejam calculados os 'n' primeiros primos: ");
        scanf("%d",&num);
        
        if(num > 0) {

            int eratosthenes[num];
            int i,j;
            
            printf("%d ", 1);
            
            for (i=1; i<num; i++)
                eratosthenes[i] = 1;             
            
            for(i=1; i<num; i++) { // Para comecar do num. 2
                for(j=i+1; j<num; j++)
                    if (eratosthenes[j] == 1)  // Evita multiplos em comum
                        if ((j+1)%(i+1)==0)
                            eratosthenes[j] = 0;
                if (eratosthenes[i] == 1)
                    printf("%d ", i+1);
            }        
                
            printf("\n");
        
        } else 
            printf("Bye!\n");
    }
    return 75;
}