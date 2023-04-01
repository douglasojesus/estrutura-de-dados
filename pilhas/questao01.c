//Implemente uma pilha utilizando listas encadeadas. Você
//deve implementar as funções Vazia, Push e Pop.

#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int conteudo;
	struct No *proximo;
} No;

void empty(No*);
void push(No**, int);
void pop(No**);
void see(No*);

int main(void) {
	int opcao, num;
	No *base=NULL;
	do{
	  	printf("\n(1) vazia\n(2) push\n(3) pop\n(4) see\n>>> ");
		scanf("%d", &opcao);
		if (opcao == 1){
			empty(base);
		} else if (opcao == 2){
			printf("num: "); scanf("%d", &num);
			push(&base, num);
		} else if (opcao == 3){
			pop(&base);
		} else if (opcao == 4){
			see(base);
		}
	} while (opcao!=0);
  return 0;
}

void empty(No *lista){
	if (!(lista)){
		printf("\nlista vazia!\n");
	} else {
		printf("\nlista não está vazia!\n");
	}
}

void push(No **lista, int num){
	No *aux=*lista;
	No *novo=(No *)malloc(sizeof(No));
	novo->conteudo=num;
	if (!(*lista)){
		novo->proximo=NULL;
		(*lista)=novo;
	} else {
		while (aux->proximo){
			aux=aux->proximo;
		}
		aux->proximo=novo;
		novo->proximo=NULL;
	}
}

void pop(No **lista){
	No *aux=*lista, *aux2;
	if (!(*lista)){
		printf("\nlista vazia\n");
	} else if(!(aux->proximo)){
		(*lista)=NULL;
		free(aux);
	} else {		
		while (aux->proximo->proximo){
			aux=aux->proximo;
		}
		aux2=aux->proximo;
		aux->proximo=NULL;
		free(aux2);
	}
}

void see(No *lista){
	No *aux=lista;
	while (aux){
		printf("%d ", aux->conteudo);
		aux=aux->proximo;
	}
}