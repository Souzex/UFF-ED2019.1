#include <stdio.h>
#include <stdlib.h>

void retira_fim_n (char *str, int n);

int main() {

    while(1) {
        
        // char *cadeia; // FUNCIONA uma única vez, pois logo em seguida retorna SEGMENTATION FAULT
        char cadeia[100]; 
        int i, tam, num; 

        printf("Informe uma cadeia de caracteres: ");
        scanf("%s",cadeia); 
        printf("Agora informe um número 'n' de últimos caracteres a serem retirados da cadeia: ");
        scanf("%d",&num); 

        for(i=0; cadeia[i++]; tam=i); // for(i=0; cadeia[i]; tam=++i);
        
        retira_fim_n (cadeia, num); // retira_inicio_n (&cadeia[0], num);
        
        num > tam ? printf("erro\n") : printf("A nova cadeia de caracteres é: %s\n", cadeia);
/*      
        if (num > tam)
            printf("erro\n");
        else {
            printf("A nova cadeia de caracteres é: ");
            for(i=0; cadeia[i]; printf("%c", cadeia[i++]));
            printf("\n");
        }
*/
        // free(cadeia); // "warning: attempt to free a non-heap object ‘cadeia’", com o uso de "char cadeia[100];""
    }
    return 75;
}

void retira_fim_n (char *str, int n) {

    int i;
    // for(i=0; str[i+n]; i++); str[i] = '\0';
    for(i=0; str[i]; str[i+n] ? i++ : (str[i] = '\0'));
}