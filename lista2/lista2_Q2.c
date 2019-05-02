#include <stdio.h>

int main() {

    int grau=1;
    while(grau > 0) {
        
        int grau;
        printf("Digite o grau do polinômio: ");
        scanf("%d",&grau);
        
        if (grau > 0) {
        
            printf("Agora digite seus coeficientes: ");
            int i, coef[grau+1];
            for(i=grau; i>=0; i--)
                scanf("%d",&coef[i]);
          
            printf("\n");
            printf("Polinômio: ");
            for(i=grau; i>=0; i--) {
                if (i>1) {
                    if (coef[i] < 0)
                        printf("- %dx^%d ",-1*coef[i],i);
                    if (coef[i] > 0)
                        printf("+ %dx^%d ",coef[i],i);
                } else {
                    if (i==1) {
                        if (coef[i] < 0)
                            printf("- %dx ",-1*coef[i]);
                        if (coef[i] > 0)
                            printf("+ %dx ",coef[i]);
                    }
                    if (i==0) {
                        if (coef[i] < 0)
                            printf("- %d ",-1*coef[i]);
                        if (coef[i] > 0)
                            printf("+ %d ",coef[i]);
                    }
                }
            }
            printf("\n");
            
            printf("Derivada: ");
            for(i=grau; i>0; i--) {
                if (i>2) {
                    if (coef[i] < 0)
                        printf("- %dx^%d ",-1*coef[i]*i,i-1);
                    if (coef[i] > 0)
                        printf("+ %dx^%d ",coef[i]*i,i-1);
                } else {
                    if (i==2) {
                        if (coef[i] < 0)
                            printf("- %dx ",-1*coef[i]*i);
                        if (coef[i] > 0)
                            printf("+ %dx ",coef[i]*i);
                    }
                    if (i==1) {
                        if (coef[i] < 0)
                            printf("- %d ",-1*coef[i]);
                        if (coef[i] > 0)
                            printf("+ %d ",coef[i]);
                    }
                }
            }
            printf("\n");
            
            printf("Integral: ");
            for(i=grau; i>=0; i--) {
                if (i>0) {
                    int is_fracao = 1;
                    if (coef[i]%(i+1) == 0)
                        is_fracao = 0;
                    if (coef[i] < 0) 
                        if (is_fracao)
                            printf("- (%d/%d)x^%d ",-1*coef[i],i+1,i+1);
                        else
                            printf("- %dx^%d ",-1*coef[i]/(i+1),i+1);
                    if (coef[i] > 0) 
                        if (is_fracao)
                            printf("+ (%d/%d)x^%d ",coef[i],i+1,i+1);
                        else
                            printf("+ %dx^%d ",coef[i]/(i+1),i+1);
                } else { // i = 0
                    if (coef[i] < 0)
                        printf("- %dx ",-1*coef[i]);
                    if (coef[i] > 0)
                        printf("+ %dx ",coef[i]);
                }
            }
            printf("\n");            
       
        } else 
            printf("Bye!\n");
    }
    return 75;
}
