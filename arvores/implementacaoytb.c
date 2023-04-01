#include <stdio.h>
#include <stdlib.h>

typedef struct arvore{
  int chave;
  struct arvore * esq;
  struct arvore * dir;
} arvore;

arvore * insere_recursivo(arvore * raiz, int num){
  if (!raiz){
    arvore * novo = (arvore *) malloc(sizeof(arvore));
    novo->chave = num;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
  } else {
    if (num < raiz->chave)
      raiz->esq = insere_recursivo(raiz->esq, num);
    else 
      raiz->dir = insere_recursivo(raiz->dir, num);
    return raiz;
  }
}

void imprimir_ordenado(arvore * raiz){
  if (raiz){
    imprimir_ordenado(raiz->dir);
    printf("%d ", raiz->chave);
    imprimir_ordenado(raiz->esq);
  }
}  

arvore * buscar(arvore * raiz, int num){
  if (raiz){
    if (num == raiz->chave)
      return raiz;
    else if (num < raiz->chave)
      return buscar(raiz->esq, num);
    else
      return buscar(raiz->dir, num);
  }
  return NULL;
}
  
int altura(arvore * raiz){
  if (raiz == NULL){
    return -1;
  } else {
    int esq = altura(raiz->esq);
    int dir = altura(raiz->dir);
    if (esq > dir)
      return esq + 1;
    else
      return dir + 1;
  }
}

int qntd_nos(arvore * raiz){
  if (raiz == NULL){
    return 0;
  } else {
    int somaesq = qntd_nos(raiz->esq);
    int somadir = qntd_nos(raiz->dir);
    return somaesq + somadir + 1;
  }
}

int qntd_folhas(arvore * raiz){
  if (raiz == NULL){
    return 0;
  } else {
    if (!(raiz->esq) && !(raiz->dir)){
      return 1;
    }
    int folhasesq = qntd_folhas(raiz->esq);
    int folhasdir = qntd_folhas(raiz->dir);
    return folhasesq + folhasdir;
  }
}

void main(){
  arvore * raiz = NULL;
  raiz = insere_recursivo(raiz, 50);
  raiz = insere_recursivo(raiz, 45);
  raiz = insere_recursivo(raiz, 68);
  raiz = insere_recursivo(raiz, 71);
  imprimir_ordenado(raiz);
  printf("\na busca do numero 68 retornou: %d", (buscar(raiz, 68))->chave);
  printf("\na busca do numero 100 retornou: %d", (buscar(raiz, 100))->chave);
  printf("\na altura da arvore eh: %d", altura(raiz));
  printf("\na arvore tem %d nos.", qntd_nos(raiz));
  printf("\na arvore tem %d folhas.", qntd_folhas(raiz));
}