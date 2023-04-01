/*Implementar uma função que recebe duas pilhas p e q,
implementadas com listas encadeadas, como parâmetro,
sendo que a pilha q está vazia. Você deve transferir todos
os elementos de p para q de maneira que q seja uma cópia
idêntica de p.*/
#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int conteudo;
	struct No *proximo;
} No;

void copy(No **, No **);
void push(No **, int);
void see(No *);

void main(){
	No (*lista)=NULL, (*lista2)=NULL;
	int num;
	printf("\nse 0 for digitado, a inserção para.");
	printf("\npush num: "); scanf("%d", &num);
	while (num != 0){
		push(&lista, num);
		printf("push num: "); scanf("%d", &num);
	}
	printf("\npilha p:\n"); see(lista);
	printf("\npilha q:\n"); see(lista2);
	printf("\nfazendo copia...\n");
	copy(&lista, &lista2);
	printf("\npilha p:\n"); see(lista);
	printf("\npilha q:\n"); see(lista2);
	printf("\nadicione mais um elemento na pilha p:\n"); scanf("%d", &num);
	push(&lista, num);
	printf("\npilha p:\n"); see(lista);
	printf("\npilha q:\n"); see(lista2);
	
}

void copy(No **lista, No **lista2){
	No *aux=*lista, *aux2;

	if (!(aux->proximo) && aux){
		No *novo=(No *) malloc(sizeof(No));
		novo->conteudo=aux->conteudo;
		*lista2=novo;
		novo->proximo=NULL;
	} else {
		//vai adicionando os elementos na pilha q de acordo com "andar"
		//da pilha p. se tiver no primeiro elemento, eh alocado um espaco
		//que vai para pilha q com o mesmo conteudo do primeiro elemento de 
		//p. e assim sucessivamente.
		while (aux){
			No *novo=(No *) malloc(sizeof(No));
			novo->conteudo=aux->conteudo;
			
			if (!(*lista2)){
				*lista2=novo;
				novo->proximo=NULL;
				aux2=novo;
			} else {
				aux2->proximo=novo;
				novo->proximo=NULL;
				aux2=novo;
			}
					
			aux=aux->proximo;
		}
	}
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

void see(No *lista){
	No *aux=lista;
	printf("\n");
	while (aux){
		printf("%d ", aux->conteudo);
		aux=aux->proximo;
	}
	printf("\n");
}