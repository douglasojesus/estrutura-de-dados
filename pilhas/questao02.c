/*Escrever um programa que leia um número indeterminado
de valores inteiros. O valor 0 (zero) finaliza a entrada de
dados. Para cada valor lido, determinar se ele é um número
par ou ímpar. Se o número for par, então incluí-lo na
PILHA PAR; caso contrário, incluí-lo na PILHA ÍMPAR.
Após o término da entrada de dados, retirar cada elemento
de cada PILHA e imprimi-lo.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int conteudo;
	struct No *proximo;
} No;

void push(No**, int);
int pop(No**);
void see(No*);

int main(){
	No *pilha_par=NULL, *pilha_impar=NULL;
	int num, removido, qntd_pares=0, qntd_impares=0;
	
	printf("adicione um num: "); scanf("%d", &num);
	do{
		if (num%2==0){
			push(&pilha_par, num);
			qntd_pares++;
		} else {
			push(&pilha_impar, num);
			qntd_impares++;
		}
		printf("adicione um num: "); scanf("%d", &num);
	} while (num!=0);
	
	printf("\npilha par:"); see(pilha_par);
	printf("\npilha impar:"); see(pilha_impar);

	//removendo e imprimindo os elementos da pilha par
	while (qntd_pares){
		removido=pop(&pilha_par);
		printf("\nremovido par: %d", removido);
		qntd_pares--;
	}

	//removendo e imprimindo os elementos da pilha impar
	while (qntd_impares){
		removido=pop(&pilha_impar);
		printf("\nremovido impar: %d", removido);
		qntd_impares--;
	}

	printf("\n\npilha par:"); see(pilha_par);
	printf("\npilha impar:"); see(pilha_impar);
	
	return 0;
}

void push(No**lista, int num){
	No *aux=*lista;
	No *novo=(No *)malloc(sizeof(No));
	novo->conteudo=num;
	
	if (!(*lista)){
		(*lista)=novo;
		novo->proximo=NULL;
	} else {
		while (aux->proximo){
			aux=aux->proximo;
		}
		aux->proximo=novo;
		novo->proximo=NULL;
	}
}

int pop(No**lista){
	No *aux=*lista, *aux2;
	int removido;
	
	if (!(*lista)){
		//nao ha elemento na lista
		removido=-1;
	} else if (!((*lista)->proximo)){
		*lista=NULL;
		removido=aux->conteudo;
		free(aux);
	} else {
		while (aux->proximo->proximo){
			aux=aux->proximo;
		}
		aux2=aux->proximo;
		removido=aux2->conteudo;
		aux->proximo=NULL;
		free(aux2);
	}
	return removido;
}

void see(No *lista){
	No *aux=lista;
	printf("\n");
	while (aux){
		printf("%d ", aux->conteudo);
		aux=aux->proximo;
	}
	printf("\n");
}