#include <stdio.h>
#include <stdlib.h>

int cic (char *str1, char *str2);

int main() {

    while(1) {
        
        char string1[100], string2[100];
        
        printf("Informe a 1a string: ");
        scanf("%s",string1); 
        printf("Informe a 2a string: ");
        scanf("%s",string2); 

        cic (string1, string2) ? printf("A 1a string contém a 2a string!\n") : printf("A 1a string NÃO contém a 2a string!\n");
               
    }
    return 75;
}

int cic (char *str1, char *str2) {

    int i, j, atual, cursor, tam_str2;
    for(i=0; str1[i]; i++);
    for(j=0; str2[j]; j++);

    if (i<j)
        return 0;

    tam_str2 = j;
    cursor = 0, atual = 0; i = 0; j = 0;
    while(str1[i]) {
        /*
        for(j=0; str2[j]; (str1[i++] == str2[j++]) ? atual++ : atual) {
            str1[i] >= 97 && str1[i] <= 122 ? str1[i] -=32 : str1[i]; // to upper case
            str2[j] >= 97 && str2[j] <= 122 ? str2[j] -=32 : str2[j]; // to upper case            
        } // OKAY! No entanto, vai ate o final de str2 pois nao executa "break;".
        */ 
        for(j=0; str2[j];) {
            str1[i] >= 97 && str1[i] <= 122 ? str1[i] -=32 : str1[i]; // to upper case
            str2[j] >= 97 && str2[j] <= 122 ? str2[j] -=32 : str2[j]; // to upper case                        
            if (str1[i++] == str2[j++])
                atual++;
            else
                break;
        }
              
        if (tam_str2 == atual)
            return 1;
        i = ++cursor;
        atual = 0;
    }
    return 0;
}

// YUYUY e YUY
// UYUY e YUY
// ACCTGAACTCCCCCC e ACCTAGGACCCCCC
// AYYYYYACTCCCCCCCCCCC e AYYYYYACCCCCCCCCCCCC
// AYYYYYACTCCCC e AYYYYYACCCC