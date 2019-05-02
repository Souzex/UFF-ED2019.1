#include <stdio.h>

int main() {

    while(1) {
        
        int num1, num2;
        printf("Digite dois números para saber se são permutação um do outro: ");
        scanf("%d",&num1);
        scanf("%d",&num2);
        
        if (num1 > 0 && num2 > 0) {

            int cont1[10], cont2[10], denominador;
            int i;
            for (i=0; i<10; i++) {
                cont1[i]=0;
                cont2[i]=0;
            }

            if (num1 == num2)
                printf("Números são exatamente iguais!\n");
            else {
                denominador = num1;
                do cont1[(denominador%10)-1]++; while ((denominador /= 10) != 0);
                denominador = num2;
                do cont2[(denominador%10)-1]++; while ((denominador /= 10) != 0);

                for(i=0; cont1[i] == cont2[i] && i < 10; i++);
                if (i==10)
                    printf("Os números %d e %d são permutações um do outro.\n", num1, num2);
                else
                    printf("Os números %d e %d NÃO são permutações um do outro.\n", num1, num2);
            }                   

        } else 
            printf("Digite apenas inteiros maiores que 0!\n");
    }
    return 75;
}