#include <stdio.h>

int main() {

    int num=1;
    while(num > 0) {
            
        int invalido=1;
        while(invalido) {
            printf("Digite o tamanho da sequência (para terminar, digite 0 ou inteiros negativos): ");
            char *valida_n;
            scanf("%s",valida_n);
            // retira espaços
            int i=1;
            if (valida_n[0] != '0' 
             && valida_n[0] != '1'
             && valida_n[0] != '2'
             && valida_n[0] != '3'
             && valida_n[0] != '4'
             && valida_n[0] != '5'
             && valida_n[0] != '6'
             && valida_n[0] != '7'
             && valida_n[0] != '8'
             && valida_n[0] != '9'
             && valida_n[0] != '+'
             && valida_n[0] != '-') 
                invalido = 1;
            else {
                invalido = 0;
                while(valida_n[i] != '\0') {
                    if (valida_n[i] != '0' 
                     && valida_n[i] != '1'
                     && valida_n[i] != '2'
                     && valida_n[i] != '3'
                     && valida_n[i] != '4'
                     && valida_n[i] != '5'
                     && valida_n[i] != '6'
                     && valida_n[i] != '7'
                     && valida_n[i] != '8'
                     && valida_n[i] != '9') {
                        invalido = 1;
                        break;
                    } 
                    i++;
                }
            }
            if (invalido)
                printf("Número inválido! Digite novamente.\n");
            else {
                num = 0;
                int expoente_10 = 0;
                if (valida_n[0] == '-')
                    num = -1;
                if (valida_n[0] == '+')
                    valida_n[0] = '0';
                while(i>0) {
                    i--;
                    int potencia_10 = 1;
                    for(int j=0; j<expoente_10; j++)
                        potencia_10 *= 10;
                    num += potencia_10*(valida_n[i] - '0');
                    expoente_10++;
                }
            }
        }
        
        if(num > 0) {
            int seq_ant, crescente = 1, crescente_max = 1;
            int counter = 0;
            while(counter < num) {
                int seq;
                printf("Digite %do número da sequência: ", counter+1);
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
