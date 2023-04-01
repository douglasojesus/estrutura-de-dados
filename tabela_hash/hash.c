#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct no {
    char chave[10];
    char valor[10];
    struct no *proximo;
};

typedef struct no No;

struct tabelaHash {
    int quant, tamanho;
    No **itens;
};

typedef struct tabelaHash TabelaHash;

TabelaHash* criarTabelaHash(int tamanho){
    TabelaHash* th = (TabelaHash*) malloc(sizeof(TabelaHash));
    if(th != NULL) {
        int i;
        th->tamanho = tamanho;
        th->itens = (No**) malloc(tamanho * sizeof(No*));
        if(th->itens == NULL) {
            free(th);
            return NULL;
        }
        th->quant = 0;
        for(i=0; i < th->tamanho; i++) {
          th->itens[i] = NULL;
        }       
    }
    return th;
}

int valorString(char *str){
    int i, valor = 7;
    int tam = strlen(str);
    for(i=0; i < tam; i++)
        valor = 31 * valor + (int) str[i];
    return (valor & 0x7FFFFFFF);
}

int chaveDivisao(int chave, int TABLE_SIZE){
    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

int insereTabelaHash(char *chave, char *valor, TabelaHash *th) {
  int pos = chaveDivisao(valorString(chave), th->tamanho);

  No *novo = (No*) malloc(sizeof(No));
  strcpy(novo->chave, chave);
  strcpy(novo->valor, valor);
  novo->proximo = NULL;
    
  if (th->itens[pos] == NULL) {
    th->itens[pos] = novo;
    return 0;
  }

  No *anterior;
  No *aux = th->itens[pos];
  while (aux != NULL) {
    if (strcmp(aux->chave, chave) == 0) {
      strcpy(th->itens[pos]->valor, valor);
      return 0;
    }
    anterior = aux;
    aux = aux->proximo;
  }
  anterior->proximo = novo;
  return 0;
}

void mostrarTabelaHash(TabelaHash *th) {
  int pos;
  for (pos=0;pos<th->tamanho;pos++) {
    printf("%d: ", pos);
    No *aux = th->itens[pos];
    while (aux != NULL) {
      printf("(%s, %s) -> ", aux->chave, aux->valor);
      aux = aux->proximo;
    }
    printf("NULL\n");
  }
}

int main(void) {
  TabelaHash *th = criarTabelaHash(31);
  insereTabelaHash("159", "Frango", th);
  insereTabelaHash("753", "Banana", th);
  insereTabelaHash("654", "Abacate", th);
  insereTabelaHash("852", "Carne", th);
  insereTabelaHash("123", "Bolacha", th);
  insereTabelaHash("789", "Arroz", th);
  insereTabelaHash("963", "Feijão", th);
  mostrarTabelaHash(th);

  
  int v1 = valorString("159");
  int v2 = valorString("789");
  printf("\nValor de 159: %d\nValor de 789: %d\n", v1, v2);
  int c1 = chaveDivisao(v1, 31);
  int c2 = chaveDivisao(v2, 31);

  printf("\nPos de 159: %d\nPos de 789: %d", c1, c2);
  
  return 0;
}