/*Escreva uma função recebe uma árvore binária de busca e remove o menor
elemento da árvore e o devolve.*/

#include <stdio.h>

typedef struct arvore{
    int chave;
    struct arvore * dir;
    struct arvore * esq;
}arvore;

int remover_menor(arvore ** no){
    int valor = -1;
    if (!(*no)){ //se não tiver nó
        return valor;
    } else if ((*no)->esq){ //se o nó da esquerda existir
        if (!((*no)->esq->esq)){
            valor = (*no)->esq->chave;
            (*no)->esq = (*no)->esq->dir;
            return valor;
        } else {
            valor = remover_menor(&((*no)->esq));
        }
    } else { //se a raíz for o menor elemento
        valor = (*no)->chave;
        (*no) = (*no)->dir;
        return valor;
    }
}