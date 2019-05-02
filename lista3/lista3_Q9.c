#include <stdio.h>
#include <stdlib.h>

int igual (char *str1, char *str2);

int main() {

    while(1) {
        
        char string1[100], string2[100];
        
        printf("Informe a 1a string: ");
        scanf("%s",string1); 
        printf("Informe a 2a string: ");
        scanf("%s",string2); 

        igual (string1, string2) ? printf("As duas strings são iguais!\n") : printf("As duas strings NÃO são iguais!\n");
               
    }
    return 75;
}

int igual (char *str1, char *str2) {

    int i, j;
    for(i=0; str1[i]; i++);
    for(j=0; str2[j]; j++);

    if (i!=j)
        return 0;

    for(i=0; str1[i]; i++) {
        str1[i] >= 97 && str1[i] <= 122 ? str1[i] -=32 : str1[i]; // to upper case
        str2[i] >= 97 && str2[i] <= 122 ? str2[i] -=32 : str2[i]; // to upper case
        if (str1[i] != str2[i])
            return 0;
    }
    return 1;    

}

// YUYUY e YUY
// UYUY e YUY
// ACCTGAACTCCCCCC e ACCTAGGACCCCCC
// AYYYYYACTCCCCCCCCCCC e AYYYYYACCCCCCCCCCCCC
// AYYYYYACTCCCC e AYYYYYACCCC