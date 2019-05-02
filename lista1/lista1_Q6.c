#include <stdio.h>

int main() {

    int x, y, z;
    int teste;
    x = 5;
    //printf("Antes - Valor de x: %d\n", x);
    //printf("Antes - Valor de y: %d\n", y);    
    y = x++;
    //printf("Depois - Valor de x: %d\n", x);
    //printf("Depois - Valor de y: %d\n", y);
    //printf("Antes - Valor de x: %d\n", x);
    //printf("Antes - Valor de z: %d\n", z);        
    z = x--;
    //printf("Depois - Valor de x: %d\n", x);
    //printf("Depois - Valor de z: %d\n", z);      

    printf("Proposição a): teste = !y == !x\n");
    printf("Antes - Valor de x: %d\n", x);
    printf("Antes - Valor de y: %d\n", y);
    printf("Antes - Valor de teste: %d\n", teste);
    teste = !y == !x; // 1o nega, 2o compara e 3o atribui.
    printf("Depois - Valor de x: %d\n", x);
    printf("Depois - Valor de y: %d\n", y);
    printf("Depois - Valor de teste: %d\n", teste);
    printf("**************\n\n");

    printf("Proposição b): teste = ((x++ > y) || (--z <= y))\n");
    printf("Antes - Valor de x: %d\n", x);
    printf("Antes - Valor de y: %d\n", y);
    printf("Antes - Valor de z: %d\n", z);
    printf("Antes - Valor de teste: %d\n", teste);
    teste = ((x++ > y) || (--z <= y));
    // teste = ++x > y; // 1o incrementa, depois compara.
    // teste = x++ > y; // 1o compara, depois incrementa.
    printf("Depois - Valor de x: %d\n", x);
    printf("Depois - Valor de y: %d\n", y);
    printf("Depois - Valor de z: %d\n", z);
    printf("Depois - Valor de teste: %d\n", teste);
    printf("**************\n\n");

    printf("Proposição c): teste = ((!x) || (!(!z)))\n");
    printf("Antes - Valor de x: %d\n", x);
    printf("Antes - Valor de z: %d\n", z);
    printf("Antes - Valor de teste: %d\n", teste);
    teste = ((!x) || (!(!z)));
    printf("Depois - Valor de x: %d\n", x);
    printf("Depois - Valor de z: %d\n", z);
    printf("Depois - Valor de teste: %d\n", teste);
    printf("**************\n\n");

    printf("Proposição d): teste = (((x + y) > z) && (x++))\n");
    printf("Antes - Valor de x: %d\n", x);
    printf("Antes - Valor de y: %d\n", y);
    printf("Antes - Valor de z: %d\n", z);
    printf("Antes - Valor de teste: %d\n", teste);
    teste = (((x + y) > z) && (x++));
    printf("Depois - Valor de x: %d\n", x);
    printf("Depois - Valor de y: %d\n", y);
    printf("Depois - Valor de z: %d\n", z);
    printf("Depois - Valor de teste: %d\n", teste);
    printf("**************\n\n");

    printf("Proposição e): teste = x && y + !3 || 4\n");
    printf("Antes - Valor de x: %d\n", x);
    printf("Antes - Valor de y: %d\n", y);
    printf("Antes - Valor de teste: %d\n", teste);
    teste = x && y + !3 || 4;
    printf("Depois - Valor de x: %d\n", x);
    printf("Depois - Valor de y: %d\n", y);
    printf("Depois - Valor de teste: %d\n", teste);
    printf("**************\n\n");

    return 75;

}