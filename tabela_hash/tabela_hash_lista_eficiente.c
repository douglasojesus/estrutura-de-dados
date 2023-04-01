//Lista encadeada
#include <stdio.h>
#include <stdlib.h>

#define TAM 19

typedef struct No{
	int conteudo;
	struct No * proximo;
} No;

typedef struct Lista{
	int tam;
	No * inicio;
} Lista;

int funcao_hash(int);
void inicializar(Lista *);
void inserir(Lista *, int num);
int buscar(Lista *, int num);
void imprimir(Lista *);

void main(){
	Lista vetor[TAM];
	int opcao=1, num, busca;
	inicializar(vetor);
	do {
		printf("\n(1) inserir\n(2) buscar\n(3) imprimir\n>>> ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				printf("num: ");
				scanf("%d", &num);
				inserir(vetor, num);
				break;
			case 2:
				printf("num: ");
				scanf("%d", &num);
				busca = buscar(vetor, num);
				if (busca)
					printf("\níndice: %d\n", busca);
				else
					printf("\nelemento não é encontrado\n");
				break;
			case 3:
				imprimir(vetor);
				break;
		}
	}while (opcao != 0);
}

int funcao_hash(int num){
	return num % TAM;
}

void inicializar(Lista vetor[]){
	for (int i=0; i<TAM; i++){
		vetor[i].inicio=NULL;
		vetor[i].tam=0;
	}
}

void inserir(Lista vetor[], int num){
	int index = funcao_hash(num);
	No * novo = (No *) malloc(sizeof(No));
	novo->conteudo = num;
	novo->proximo = vetor[index].inicio;
	vetor[index].inicio = novo;
	vetor[index].tam++;
}

int buscar(Lista vetor[], int num){
	int index = funcao_hash(num);
	No * aux = vetor[index].inicio;
	while (aux && aux->conteudo != num){
		aux=aux->proximo;
	}
	if (aux){
		return index;
	}
	return 0;
}

void imprimir(Lista vetor[]){
	No * aux;
	for (int i=0; i<TAM; i++){
		aux = vetor[i].inicio;
		printf("\n%d: ", i);
		while (aux){
			printf("%d ", aux->conteudo);
			aux=aux->proximo;
		}
	}
	printf("\n");
}