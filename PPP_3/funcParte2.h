

#ifndef PPP_FUNCPARTE2_H
#define PPP_FUNCPARTE2_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "lib-utf8.h"

#define TAM 100

//estrutura da lista ligada
typedef struct lnode{
    int pos;
    struct lnode *next;
}List;

//estrutura da arvore
typedef struct tree{
    char palavra[TAM];
    List *head;
    struct tree* dir;
    struct tree* esq;
} Tree;

Tree* createTree(){
    return NULL;
}

//insere as posiÃ§oes na lista ligada
void insertList(List** l, int posicao) {
    //cria um novo nÃ³ na lista
    List* new_node = (List*)malloc(sizeof(List));
    List* last = *l;//ultimo nÃ³

    new_node->pos = posicao;//passa a posiÃ§ao para a estrutura da lista ligada
    new_node->next = NULL;//cria o no seguinte a nulo

    if (*l == NULL) { //se o ultimo no nao existir
        *l = new_node; //o *l guarda o novo no criado
        return;// acabe
    }

    while (last->next != NULL)//se o ultimo no existir percorre os nos anteriores ate ser nulo
        last = last->next; //faz com que avanÃ§e para o proximo nÃ³

    last->next = new_node; // o no last guarda o novo no criado na posiÃ§ao seguinte(next)
    return;
}

//imprime a lista ligada
void printList(List* l) {
    while (l != NULL) {
        printf(" %d ", l->pos);
        l = l->next;
    }
}

//imprime a arvore com a lista ligada
void showTree(Tree* t){

    if (t!=NULL) {
        showTree(t->esq);
        printf("%20s ", t->palavra);
        printList(t->head);
        printf("\n");
        showTree(t->dir);
    }
}

//insere a palavras na arvore
void insertTree(Tree** t, char *pal, int pos ){
    //vÃª se o no esta vazio
    if(*t == NULL){
        //cria o um nÃ³ na arvore
        *t = (Tree*)malloc(sizeof(Tree));
        (*t)->esq = NULL;//cria nÃ³ esquerdo nulo
        (*t)->dir = NULL;//cria nÃ³ direito nulo
        (*t)->head = NULL;//cria nÃ³ nulo para a lista ligada
        strcpy((*t)->palavra, pal);//copia a palavra para a estrutura da arvore

        insertList(&(*t)->head, pos);//inserir no fim da lista ligada

    } else {
        if(strcmp(pal, (*t)->palavra)<0){
            insertTree(&(*t)->esq, pal, pos);//vai para o no esquerdo
        }
        else if(strcmp(pal, (*t)->palavra)>0){
            insertTree(&(*t)->dir, pal, pos);//vai para o no direito
        }
        else if(strcmp(pal, (*t)->palavra)==0){
            insertList(&(*t)->head, pos);//inserir no fim da lista ligada
        }
    }
}

void contextBack(int posicao) {
    int contador = 0, c = 0, i=0;
    char cad[posicao+1], ord[posicao+1];//cad sring para inserir os caracteres //ord string cad mas ordernada
    FILE *fich = fopen("texto.txt", "r");
    if (fich == NULL) {
        printf("Problemas na abertura do ficheiro de texto\n");
    }
    fseek(fich, posicao, SEEK_CUR);//le o ficheiro apartir de uma posiÃ§ao especifica
    long lim = ftell(fich);//numero maximo de posiÃ§oes que pode andar para traz ate ao inicio do ficheiro

    //procura as palavras para tras
    while(lim >= 0){
        fseek(fich, lim, SEEK_SET); //reposicionar de acordo com a posicao
        c = fgetc(fich);
        if (c == ' ' || c !='\n')
            contador++;
        if (contador == 11){
            cad[i] = '\0';
            break;
        }

        cad[i] = (char)c;
        i++;
        lim--; //andar uma posiÃ§Ã£o para trÃ¡s
    }

    for (int n=0; n<strlen(cad);n++){//ordena a palavra
        ord[n]=cad[strlen(cad)-n];
        printf("%c", ord[n]);
    }
}
void contextFront(int posicao) {
    int c = 0, contador=0;
    FILE *fich = fopen("texto.txt", "r");
    if (fich == NULL) {
        printf("Problemas na abertura do ficheiro texto\n");
    }
    fseek(fich, posicao, SEEK_CUR);
    //procura as palavras para a frente

    while ((c = fgetc(fich)) != EOF)  {
        printf("%c",c);
        if (c == ' ' || c =='\n'){
            contador++;
            if (contador==6){
                break;
            }
        }
    }
    printf("\n");
}

void printContext(List* l) {//funciona com o printList
    while (l != NULL) {
        contextBack(l->pos);
        contextFront(l->pos);
        printf("\n\n");
        l = l->next;
    }
}

int context(Tree* t, char* ini){//funciona como o showTree e o search

    if(t!=NULL) {
        context(t->esq, ini);

        if (strcmp(ini, t->palavra)==0){
            printContext(t->head);
        }
        context(t->dir, ini);
    }
    return 0;
}
#endif //PPP_FUNCPARTE2_H
