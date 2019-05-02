#include <stdio.h>

int converte_numero(char *numero, int tamanho);

int main() {

    int num=1;
    while(num > 0) {
        
        char *input;
        printf("Digite o tamanho da sequência (para terminar, digite 0 ou inteiros negativos): ");
        scanf("%[0-9]",input);

        int i = 0;
        while (input[i] != '\0') {
            printf ("%c",input[i]);
            i++;
        }            
        
        num = converte_numero(input,i);
        // input[0] = '\0';
        // fflush(stdin);
        
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

int converte_numero(char *numero, int tamanho) {

    int n = 0;
    int expoente_10 = 0;
    int is_negative = 0;
    
    if (numero[0] == '+')
        numero[0] = '0';
    if (numero[0] == '-') {
        numero[0] = '0';
        is_negative = 1;
    }
    
    while(tamanho>0) {
        printf("tô aqui\n");
        tamanho--;
        int potencia_10 = 1;
        int j;
        for(j=0; j<expoente_10; j++)
            potencia_10 *= 10;
        n += potencia_10*(numero[tamanho] - '0');
        expoente_10++;
    }
    if (is_negative)
        n = (-1)*n;
    printf("tô aqui de novo:%d\n", n);
    return n;
}