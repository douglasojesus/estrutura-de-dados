/*
Pilha com ponteiros
Implementada com um nó como cabeça. Este nó não guarda conteúdo.
*/


#include <stdio.h>
#include <stdlib.h>

typedef struct pilha_no{
    int conteudo;
    struct pilha_no * proximo;
} Pilha_no;

Pilha_no * pilha_cria();
void pilha_push(Pilha_no *, int);
int pilha_pop(Pilha_no *);
void pilha_destroi(Pilha_no **);
void pilha_imprime(Pilha_no *);

int main(){
	Pilha_no * pilha = pilha_cria();
	pilha_push(pilha, 10);
	pilha_push(pilha, 11);
	pilha_push(pilha, 12);
	pilha_imprime(pilha);
	pilha_pop(pilha);
	pilha_imprime(pilha);
	pilha_push(pilha, 13);
	pilha_imprime(pilha);
	pilha_destroi(&pilha);
	pilha_imprime(pilha);
}

// Cria a pilha - cria o nó cabeça da pilha (não guarda valor, apenas o endereço do primeiro elemento da pilha
Pilha_no * pilha_cria(){
        Pilha_no * cabeca = (Pilha_no *) malloc(sizeof(Pilha_no));
        cabeca -> proximo = NULL;
        return cabeca;
}

// Procedimento para armazenar valores na pilha
void pilha_push(pilha_no * cabeca, int valor){
	if(cabeca){
        Pilha_no * novo_no = (Pilha_no *) malloc(sizeof(Pilha_no));
        novo_no -> conteudo = valor;
        novo_no -> proximo = cabeca -> proximo;
        cabeca -> proximo = novo_no;
	}
}

// Função para retirar elementos da pilha
int pilha_pop(Pilha_no * cabeca){
	if (cabeca){
		Pilha_no * no_eliminado = cabeca -> proximo;
	
		if (no_eliminado){
			int valor = no_eliminado -> conteudo;
			cabeca -> proximo = no_eliminado -> proximo;
			free(no_eliminado);
			return valor;
		}
	}
	return -1;
}

void pilha_destroi(Pilha_no * * pilha){
  Pilha_no * aux = * pilha; 	//variável auxiliar
  Pilha_no * temp;          	//variável temporária
  printf("%d\n",aux->conteudo); // conteúdo da cabeça - Lixo
  aux = aux -> proximo;			// pulando a cabeça da lista
  
  while (aux){            		//Verdadeiro enquanto aux for diferente de NULL
    temp = aux;           		//armazena o nó do topo da pilha
    printf("%d\n",aux->conteudo);
    aux = aux -> proximo;    	//caminha para o próximo item da pilha
    free(temp);           		//libera a memória do nó que estava no topo
  }
  (*pilha)->proximo = NULL;     //o próximo da cabeça da lista agora armazena NULL
}

void pilha_imprime(Pilha_no * pilha){
        pilha = pilha -> proximo;
        while(pilha){
                printf("[%d]->", pilha -> conteudo);                
                pilha = pilha -> proximo;
        }
        printf("NULL\n");
}
