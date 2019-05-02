#include <stdio.h>

int main() {

    int num=1;
    while(num > 0) {
        
        printf("Digite um número 'n' para que sejam calculados os 'n' primeiros primos: ");
        scanf("%d",&num);
        
        if(num > 0) {
            printf("1 ");
            int seq = 2;
            while(seq <= num) {
                int counter = 2, is_prime = 1;
                while(counter <= seq) {
                    if ((seq%counter==0) && (counter!=seq)) {
                            is_prime = 0; // nao eh primo
                            break; 
                    }
                    counter++;
                }
                if (is_prime)
                    printf("%d ", seq);
                seq++;
            }
            printf("\n");
        } else 
            printf("Bye!\n");
    }
    return 75;
}