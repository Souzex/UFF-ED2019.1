#include <stdio.h>
#include <stdlib.h>


char** s2ss (char *str);

int main() {

    while(1) {
        
        int i, j;
        char *string = "/Fla/Flu/Bota/";

        char **decomposta = s2ss (string);

        printf("String decomposta: \n");
        for(i=0; decomposta[i]; printf("%s\n",decomposta[i++]));

        for(i=0; decomposta[i]; i++)
            for(j=0; decomposta[i][j]; j++)
                printf("%da palavra e seu %do caracter: %c\n", i+1, j+1, decomposta[i][j]);

        break;
    }
    return 75;
}

char** s2ss (char *str) {

    int i, j, k, l, placeholder;
    
    j = 0;
    for(i=0; str[i]; (str[i++] == '/') ? j++ : j);

    char **new_str = (char **) malloc (sizeof(char *)*j);

    i=0; j=0;
    while(str[i]){
        if(str[i++] == '/')
            if (str[i]) {

                placeholder = i; // 1a letra apos '/'
                for(k=0; str[i++] != '/'; k++); // k = tamanho da palavra
                new_str[j] = (char *) malloc (sizeof(char)*(k+1));
                l=0;
                for(i=placeholder; i<placeholder+k; new_str[j][l++] = str[i++]);
                new_str[j++][l] = '\0';
            } 
    }
    return new_str;
}