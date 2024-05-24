#include <stdio.h>
#include "func.h"

int main(){
    int i;

    while (1){
        printf("ESCOLHA UMA OPÇAO:\n");
        printf("[1] PARTE 1\n");
        printf("[2] PARTE 2\n");
        printf("[3] SAIR\n");
        scanf("%d",&i);

        if(i==1)
            parte1();
        else if (i==2)
            parte2();
        else if (i==3)
            break;
        else
            printf("Opçao invalida!\n");
    }
    return 0;
}