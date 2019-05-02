#include <stdio.h>
#include <stdlib.h>

int verifica_senha (char *str);

int main() {

    while(1) {
        
        // char *senha; // FUNCIONA uma única vez, pois logo em seguida retorna SEGMENTATION FAULT
        char senha[100]; 
        
        printf("Informe uma senha: ");
        scanf("%s",senha); 

        verifica_senha (senha) ? printf("Boa senha! :))\n") : printf("Senha ruim! :(\n");
        
        // free(senha); // "warning: attempt to free a non-heap object ‘cadeia’", com o uso de "char cadeia[100];""
    }
    return 75;
}

int verifica_senha (char *str) {
    
    int i, cond_num = 0, cond_lower = 0, cond_upper = 0, cond_others = 0;
   
    for(i=0; str[i]; i++)
        if (str[i] >= 48 && str[i] <= 57) // 0..9
            cond_num = 1;
        else if (str[i] >= 97 && str[i] <= 122) // minusculas
            cond_lower = 1;
        else if (str[i] >= 65 && str[i] <= 90) // maiusculas
            cond_upper = 1;
        else
            cond_others = 1;
    
    if (cond_num && cond_lower && cond_upper && cond_others)
        return 1;
    else
        return 0;
   
}