/*Escreva uma função recebe uma árvore binária de busca r e o valor de um nó x
e retorna o valor do elemento que possui a menor chave (valor do elemento)
dentre os elementos que são maiores do que x em r.*/

#include <stdio.h>

typedef struct arvore{
    int chave;
    struct arvore * dir;
    struct arvore * esq;
} arvore;

int menor_maior(arvore * no, int x){
    int numdir, numesq;
    if (!no){
        return 1;
    } else {
        if (x > no->chave){ //se x for maior que o atual, vai para direita
            numdir = menor_maior(no->dir, x);
            numesq=0;
        } else { //se x for menor que o atual, vai para esquerda
            numesq = menor_maior(no->esq, x);
            numdir=0;
        }
        if (numdir){
            if (numdir > x && no->chave > numdir){ //se o retorno for maior que x e o NO atual for maior que o retorno
                return numdir; //retorna o antigo retorno
            } else if (no->chave > x){ //se o NO atual for maior que x (e, de maneira implícita, o retorno for menor que x)
                return no->chave;
            } else { //se o retorno não for maior que x e o NO atual também não, retorna o antigo retorno
                return numdir;
            }
        } else {
            if (numesq > x && no->chave > numesq){
                return numesq;
            } else if (no->chave > x){
                return no->chave;
            } else {
                return numesq;
            }
        }
    }
}

//se retorno final for 1, significa que não tem elemento
//coloquei 1 pois o menor número natural a ser buscado é o 1
//como precisa ser entre os maiores que x (1), o próprio 1 não é válido
//então retorná-lo significa que não tem um número entre os maiores de x

