#include "func.h"


/*
 * Funçao principal para a parte 1
 */
int parte1(){

    //variaveis globais
    FILE *f1 = fopen("param1.txt", "r");//abre o ficheiro de com o nome do ficheiro com texto em modo leitura
    char ficheiroTexto[100]="", ficheiroBin[100]="";

    int i=0, c=0;
    char palavra[30]="";
    //estrutura para passar os pares(palavra e posiçao)
    Dados d;

    //verifica se o ficheiro esta vazio
    if (f1 == NULL){
        printf("Problemas na abertura do ficheiro param1.txt\n");
        return 0;
    }

    fgets(ficheiroTexto, sizeof(ficheiroTexto) - 1, f1);

    strcpy(ficheiroBin, "tab_");
    strcat(ficheiroBin, ficheiroTexto);
    printf("%s\n",ficheiroBin);

    fclose(f1);
    FILE *ftexto = fopen(strcat(ficheiroTexto, ".txt"), "r");//abre o ficheiro de texto com o texto
    FILE *f2 = fopen(strcat(ficheiroBin, ".bin"), "wb");//abre o ficheiro de escrita em modo escrita
    if (ftexto == NULL){
        printf("Problemas na abertura do ficheiro com o texto\n");
        return 0;
    }else {
        //lê o ficheiro caractere a caractere
        do {
            c = fgetc(ftexto);

            //so aceita os carateres do alfabeto latino e numeros
            if ((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') || (c>=128)){
                palavra[i] = (char) c;
                i++;
            }
            else{
                palavra[i] = '\0';
                i=0;
                //verifica se a palavra tem mais de TRES caracteres
                if(strlen(palavra)>3){
                    //copia para a estrututra a palavra
                    strcpy(d.word, palavra);
                    //ve a posiçao do 1º caractere de cada palavra
                    int posicao = ftell(ftexto)-strlen(palavra)-1;
                    //copia para a estrututra a posiçao
                    d.posi = posicao;
                    //passa a estrutura com os pares (palavra e posiçao) para o ficheiro binario
                    fwrite(&d, sizeof(Dados), 1, f2);
                }
            }
        }
        while (c != EOF);
    }
    printf("Ficheiro dos pares criado.\n");
    fclose(f2);
    fclose(ftexto);
    return 0;
}