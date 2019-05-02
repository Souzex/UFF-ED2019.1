#include <stdio.h>

int main() {

    int n=1, m=2;
    while((n > 0) && ((m != 0) && (m != 1) && (m != -1))) {
        
        printf("Digite um número 'm' para o cálculo de suas potências: ");
        scanf("%d",&m);

        printf("Digite um número 'n' para delimitar o num. de potências de 'm': ");
        scanf("%d",&n);        

        if (n > 0)
            if ((m != 0) && (m != 1) && (m != -1))    

                if (m<-1) 
                    printf("Valor de 'm' inválido! Digite novamente.\n");
                else {
                    int pot = 1;
                    while (pot < n) {
                        printf ("%d ", pot);
                        pot *= m;
                    }
                    printf("\n");
                }
            else 
                printf("Bye!\n");    

        else 
            printf("Bye!\n");
    }
    return 75;
}