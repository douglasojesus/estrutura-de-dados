// Endereçamento aberto
#include <stdio.h>
// qntd. de elementos (10) * 2 -> pega o primo mais prox
#define TAM 19

int funcao_esp(int);
void inicializar(int *);
void inserir(int *, int);
int buscar(int *, int);
void imprimir(int *);

void main(){
	int opcao=1, num, busca;
	int vetor[TAM];
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
	} while (opcao != 0);
}

int funcao_esp(int num){
	return num % TAM;
}

void inicializar(int vetor[]){
	for (int i=0; i<TAM; i++){
		vetor[i] = 0;
	}
}

void inserir(int vetor[], int num){
	int index = funcao_esp(num);
	while (vetor[index] != 0){
		index = funcao_esp(index+1);
	}
	vetor[index] = num;
}

int buscar(int vetor[], int num){
	int index = funcao_esp(num);
	while (vetor[index] != num && vetor[index]){
		index = funcao_esp(index+1);
	}
	if (vetor[index])
		return index;
	return 0;
}

void imprimir(int vetor[]){
	for (int i=0; i<TAM; i++){
		printf("\n%d: %d", i, vetor[i]);
	}
	printf("\n");
}