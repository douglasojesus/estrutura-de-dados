/*Dada uma tabela de espalhamento (Hashing Table), resultante da inserção de
registros com as chaves A, N, L, U, C, I, R, S, T, M, E, O (com cada letra
correspondendo a sua posição no alfabeto, ex: A = 1, B = 2, C = 3, ...) nesta
ordem, numa tabela inicialmente vazia de tamanho 7 e, sabendo-se que a função
de espalhamento é h(k) = (k2 + k –1) mod 7 (mod é o resto da divisão), para a 
k-ésima letra do alfabeto e que as colisões foram tratadas com listas encadeadas,
indique quantas comparações seriam necessárias para encontrar os elementos
E, T, I e M numa busca nesta tabela. Explique como você chegou a esses
valores, mostrando a tabela construída.*/

//***************EXPLICAÇÃO*****************

/*
Para chegar nos valores obtidos inicialmente, fiz um teste de mesa imaginando
as funções já prontas. Apenas realizando a inserção direta na tabela. Na lógica de inserção,
os elementos foram colocados no início da lista. Para efetuar a busca, comparei o conteudo
atual do nó com o elemento da lista, seguindo esse ritmo entre os ponteiros até encontrar
o conteúdo ou até a lista ser chegar a NULL.
Sendo assim, consegui os valores: 1, 2, 1 e 1 de comparações para as letras E, T, I e M, 
respectivamente.
Para reafirmar o resultado, fiz o código e apliquei o exemplo, obtendo o mesmo resultado.
Para garantir a sequencia das letras (A=1, B=2, C=3, ...), utilizei os valores da tabela ASCII.
Como A=65 na tabela ASCII, fiz: (int) letra - 64 para todas as letras.
*/

/*
OBS: considerei como comparação cada uso da condicional para verificar
se a letra buscada é igual ao conteúdo da struct nó em questão. Por isso,
se o elemento buscado for o primeiro da lista, considerei como 1 comparação.
*/

//Código
#include <stdio.h>
#include <stdlib.h>

#define TAM 7

typedef struct No{
	char conteudo;
	struct No * proximo;
} No;

typedef struct Lista{
	int tam;
	No * inicio;
} Lista;

int funcao_hash(int);
void inicializar(Lista *);
void inserir(Lista *, char letra);
int buscar(Lista *, char letra);
void imprimir(Lista *);

void main(){
	Lista vetor[TAM];
	int opcao=1, busca;
    char letra;
	inicializar(vetor);
	do {
		printf("\n(1) inserir\n(2) buscar\n(3) imprimir\n>>> ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				printf("letra: ");
				scanf(" %c", &letra);
				inserir(vetor, letra);
				break;
			case 2:
				printf("letra: ");
				scanf(" %c", &letra);
				busca = buscar(vetor, letra);
				if (busca != -1)
					printf("\nÍndice: %d.\n", busca);
				else
					printf("\nElemento não encontrado.\n");
				break;
			case 3:
				imprimir(vetor);
				break;
		}
	}while (opcao != 0);
}

int funcao_hash(int num){
	return ((num*num) + num - 1) % TAM;
}

void inicializar(Lista vetor[]){
	for (int i=0; i<TAM; i++){
		vetor[i].inicio=NULL;
		vetor[i].tam=0;
	}
}

void inserir(Lista vetor[], char letra){
	int index = funcao_hash((int)letra - 64); //Utilizando o código ASCII da letra - 64 para usar como uma sequência a partir do 1.
	No * novo = (No *) malloc(sizeof(No));
	novo->conteudo = letra;
	novo->proximo = vetor[index].inicio;
	vetor[index].inicio = novo;
	vetor[index].tam++;
}

int buscar(Lista vetor[], char letra){
    int comparacoes=1;
	int index = funcao_hash((int)letra - 64);
	No * aux = vetor[index].inicio;
	while (aux && aux->conteudo != letra){
        comparacoes++;
		aux=aux->proximo;
	}
	if (aux){
        printf("\nComparações feitas: %d", comparacoes);
		return index;
	}
    printf("\nComparações feitas: %d", comparacoes-1);
	return -1;
}

void imprimir(Lista vetor[]){
	No * aux;
	for (int i=0; i<TAM; i++){
		aux = vetor[i].inicio;
		printf("\n%d: ", i);
		while (aux){
			printf("%c ", aux->conteudo);
			aux=aux->proximo;
		}
	}
	printf("\n");
}

//Teste de uso

/*
1
A
1
N
1
L
1
U
1
C
1
I
1
R
1
S
1
T
1
M
1
E
1
O
*/