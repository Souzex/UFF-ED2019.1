#include <stdio.h>
#include <stdlib.h>

int valida_numero(char *numero, int *tamanho);
int converte_numero(char *numero, int tamanho);

int main() {
    
    int num=1;
    while(num > 0) {
            
        int invalido=1;
        while(invalido) {
            printf("Digite o tamanho da sequência (para terminar, digite 0 ou inteiros negativos): ");
            char *numero;
            scanf("%s",numero);
            // retira espaços
            printf("estou aqui\n");
            // int tamanho; // ERROR_1
            // int *tamanho = malloc(sizeof(int)); // WORKS!
            int *tamanho = (int*) malloc(sizeof(int));
            // invalido = valida_numero(numero, &tamanho); // ERROR_1
            invalido = valida_numero(numero, tamanho);
            printf("invalido:%d\n", invalido);
            if (invalido)
                printf("Número inválido! Digite novamente.\n");
            else 
                num = converte_numero(numero, *tamanho);
            
            free(tamanho);
        }
        
        if(num>0) {
            int seq_ant, crescente = 1, crescente_max = 1;
            int counter = 0;
            while(counter < num) {
                int seq;
                invalido = 1;
                while(invalido){    
                    printf("Digite %do número da sequência: ", counter+1);
                    char *numero;
                    scanf("%s",numero);
                    int tamanho;
                    invalido = valida_numero(numero, &tamanho);
                    // int *tamanho = (int*) malloc(sizeof(int)); // ERROR_2
                    // invalido = valida_numero(numero, tamanho); // ERROR_2
                    if (invalido)
                        printf("Número inválido! Digite novamente.\n");
                    else 
                        seq = converte_numero(numero, tamanho);
                        // seq = converte_numero(numero, *tamanho); // ERROR_2
                }
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

int valida_numero(char *numero, int *p_tamanho) {
printf("estou aqui2\n");
   
    *p_tamanho=1;
    int invalido;
    if (numero[0] != '0' 
     && numero[0] != '1'
     && numero[0] != '2'
     && numero[0] != '3'
     && numero[0] != '4'
     && numero[0] != '5'
     && numero[0] != '6'
     && numero[0] != '7'
     && numero[0] != '8'
     && numero[0] != '9'
     && numero[0] != '+'
     && numero[0] != '-') 
        invalido = 1;
    else {
        invalido = 0;
        while(numero[*p_tamanho] != '\0') {
            if (numero[*p_tamanho] != '0' 
             && numero[*p_tamanho] != '1'
             && numero[*p_tamanho] != '2'
             && numero[*p_tamanho] != '3'
             && numero[*p_tamanho] != '4'
             && numero[*p_tamanho] != '5'
             && numero[*p_tamanho] != '6'
             && numero[*p_tamanho] != '7'
             && numero[*p_tamanho] != '8'
             && numero[*p_tamanho] != '9') {
                invalido = 1;
                break;
            } 
            (*p_tamanho)++;
        }
    }
     
    return invalido;
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
        for(int j=0; j<expoente_10; j++)
            potencia_10 *= 10;
        n += potencia_10*(numero[tamanho] - '0');
        expoente_10++;
    }
    if (is_negative)
        n = (-1)*n;
    printf("tô aqui de novo:%d\n", n);
    return n;
}