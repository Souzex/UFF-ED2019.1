
#include <stdio.h>

int main() {

    int num=1;
    while(num > 0) {
        
        printf("Digite o tamanho da sequência (para terminar, digite 0 ou inteiros negativos): ");
        scanf("%d",&num);
        // scanf("%*c%d",&num);
       
        if(num > 0) {
            int seq_ant, crescente = 1, crescente_max = 1;
            int counter = 0;
            while(counter < num) {
                printf("Digite %do número da sequência: ", counter+1);
                int seq;
                scanf("%d",&seq);
                if (counter) {
                    if (seq > seq_ant) 
                        crescente++;
                    else 
                        if (crescente > crescente_max) {
                            crescente_max = crescente;
                            crescente = 1;
                        }
                }
                seq_ant = seq;
                counter++;
            }
            if (crescente > crescente_max)
                crescente_max = crescente;    
            printf("O comprimento de um segmento crescente máximo é: %d\n", crescente_max);
        } else 
            printf("Bye!\n");
    }
    return 75;
}