#include <stdio.h>

int main() {

    int num=1;
    while(num > 0) {
        
        printf("Digite um número 'n' para o cálculo dos 'n' primeiros primos depois dele: ");
        scanf("%d",&num);
        
        if(num > 0) {
            int counter_1 = 0;
            int seq = num + 1;
            while (counter_1 < num) {
                int counter_2 = 2, is_prime = 1;
                while (counter_2 <= seq) {
                    if ((seq%counter_2 == 0) && (counter_2 != seq)) {
                        is_prime = 0; // nao eh primo
                        break; 
                    }
                    counter_2++;
                }
                if (is_prime) {
                    printf("%d ", seq);
                    counter_1++;
                }
                seq++;
            }
            printf("\n");
        } else 
            printf("Bye!\n");
    }
    return 75;
}