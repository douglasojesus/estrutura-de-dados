//Autor: Douglas Oliveira de Jesus
//Data: 09/09/22
//Curso: Engenharia de Computação | UEFS
//Disciplina: Estrutura de Dados
//Professora: Cláudia Pinto

#include <stdio.h>
#include <stdlib.h>

//struct para lista duplamente encadeada
typedef struct LDE{
	int conteudo;
	struct LDE * proximo;
	struct LDE * anterior;
}LDE;

//struct para lista simplesmente encadeada e circular
typedef struct No{
    int conteudo;
    struct No *proximo;
} No;

void append(No **, int);
void see(No *);
int soma_pares(No **); //questao 01
void pop(No **); //questao 02
int posicao(No **, int); //questao 03
No *concatena(No **, No **); //questao 04
void inverte(No **); //questao 05
void appendLDE_ordenado(LDE **, int); //questao 06
void seeLDE(LDE *); //questao 06
LDE *ordena_LDE(LDE **, LDE **); //questao 06
void insere_circular(No **, int); //questao 07
void see_circular(No *); //questao 07

void main(){
    int opcao, num, soma, escolha, index;
    No *lista2 = NULL, *lista = NULL, *ponteiro;
    LDE *listaLDE = NULL, *listaLDE2 = NULL, *listaLDE3=NULL;
    No *listacircular=NULL;
    do{
        printf("\n(1) append;\n(2) pop;\n(3) soma dos pares da lista 1;\n(4) ver lista;\n");
        printf("(5) retorna posicao da lista 1;\n(6) concatena duas listas;\n(7) inverte a lista 1;\n");
        printf("(8) append LDE ordenado;\n(9) ver LDE;\n(10) ordena a LDE1 E LDE2 em LDE3;\n");
        printf("(11) append circular;\n(12) ver circular;\n>>> ");
        scanf("%d", &opcao);

        if (opcao == 1){
            printf("lista 1 ou 2: "); scanf("%d", &escolha);
            printf("numero p/ lista: "); scanf("%d", &num);
            if (escolha == 1){
                append(&lista, num);
            } else if (escolha == 2){
                append(&lista2, num);
            }
        }else if (opcao == 2){
            printf("lista 1 ou 2: "); scanf("%d", &escolha);
            if (escolha == 1){
                pop(&lista);
            } else if (escolha == 2){
                pop(&lista2);
            }
        }else if (opcao == 3){
            soma = soma_pares(&lista);
            printf("\nsoma dos pares: %d\n", soma);
        }else if (opcao == 4){
            printf("\nlista 1: "); see(lista);
            printf("\nlista 2: "); see(lista2);
        }else if (opcao == 5){
            printf("\nnumero: ");
            scanf("%d", &num);
            index=posicao(&lista, num);
            printf("\nposicao: %d", index);
        }else if (opcao == 6){
            ponteiro = concatena(&lista, &lista2);
            see(ponteiro);
        }else if (opcao == 7){
            inverte(&lista);
        }else if (opcao == 8){
            printf("lista 1 ou 2: "); scanf("%d", &escolha);
            printf("numero p/ lista: "); scanf("%d", &num);
            if (escolha == 1){
                appendLDE_ordenado(&listaLDE, num);
            } else if (escolha == 2){
                appendLDE_ordenado(&listaLDE2, num);
            }
        } else if (opcao == 9){
            printf("\nlista 1: "); seeLDE(listaLDE);
            printf("lista 2: "); seeLDE(listaLDE2);
            printf("lista 3: "); seeLDE(listaLDE3);
        } else if (opcao == 10){
            listaLDE3=ordena_LDE(&listaLDE, &listaLDE2);
            printf("\nlistas 1 e 2 ficaram vazias.");
            printf("\nlista 3: "); seeLDE(listaLDE3);
        } else if (opcao == 11){
            printf("numero p/ lista: "); scanf("%d", &num);
            insere_circular(&listacircular, num);
        } else if (opcao == 12){
            printf("lista circular: "); see_circular(listacircular);
        }
    } while (opcao != 0);
}

//Append na lista simplesmente encadeada;
void append(No ** lista, int entrada){
    //Se a lista tiver vazia.
    if (!(*lista)){
        (*lista) = (No *) malloc(sizeof(No));
        (*lista)->conteudo=entrada;
        (*lista)->proximo=NULL;
    } else {
        No * new = (No *) malloc(sizeof(No));
        No * aux = *lista;
        //Verificando se o proximo aponta para nulo.
        while (aux->proximo){
            aux = aux -> proximo; //Se não, aux vai percorrendo a lista até encontrar o último.
        }
        aux -> proximo = new; //New é adicionado no final da lista.
        new -> conteudo = entrada;
        new -> proximo = NULL; //New aponta para NULL.
    }
}

//Ver lista simplesmente encadeada.
void see(No * lista){
    No * aux = lista;
    if (!aux){
        printf("[]");
    } else {
        printf("\n[");
        while (aux){
            printf("%d", aux->conteudo);
            aux = aux->proximo;
            if (aux){
                printf(", ");
            } else {
                printf("]\n");
            }
        }
    }
}

/*Escreva uma função que recebe uma lista encadeada e retorna a soma dos
elementos pares.*/
int soma_pares(No **lista){
    int soma = 0;
    No *aux = *lista;
    //percorre a lista até o último elemento
    while (aux->proximo){
        //verifica se o aux atual é par
        if (aux->conteudo % 2 == 0){
            //adiciona o conteudo de aux na var soma
            soma += aux->conteudo;
        }
        aux = aux->proximo;
    }
    return soma;
}

/*Escreva uma função que recebe uma lista encadeada como parâmetro e remove o
último elemento da lista.*/
void pop(No **lista){
    No *aux2, *aux = *lista;
    //verifica se a lista é vazia
    if (!aux){
        printf("\nlista vazia!");
    }
    else{
        //percorre até o último elemento
        while (aux->proximo){
            //aux2 vai ser um indice menor que aux
            aux2 = aux;
            aux = aux2->proximo;
        }
        //libera a memoria do ponteiro aux
        free(aux);
        aux2->proximo = NULL;
    }
}

/*Escreva uma função que recebe uma lista encadeada e retorna a posição, a partir
do início da lista (posição 1), da primeira ocorrência de um valor n, recebido por
parâmetro. Se não houver, retornar o valor –1.*/
int posicao(No **lista, int num){
    //começa com 1 devido ao requisito da questao
    int cont = 1;
    No *aux = *lista;
    //percorre até o ultimo elemento ou até achar o valor buscado
    while (aux->proximo && aux->conteudo != num){
        aux = aux->proximo;
        //contadora recebe 1 a cada iteração
        cont++;
    }
    if (aux->conteudo == num){
        return cont;
    }
    else{
        return -1;
    }
}

/*Escreva uma função que receba duas listas encadeadas de inteiros L1 e L2e
concatene-as. Ao final desse processo, L1 conterá os elementos das duas listas e
L2 estará vazia.*/
No *concatena(No **lista, No **lista2){
    No *aux = *lista;
    //verifica possibilidades entre listas, se uma, ou mais, está vazia
    if (!(*lista) && (*lista2)){
        return (*lista2);
    }else if ((*lista) && !(*lista2)){
        return (*lista);
    }else if (!(*lista) && !(*lista2)){
        return NULL;
    }//se ambas não tiverem vazias:
    else{
        //percorre ate o ultimo elemento
        while (aux->proximo){
            aux = aux->proximo;
        }
        No *aux2 = *lista2;
        //percorre até o ultimo elemento da segunda lista
        while (aux2){
            //eh criado uma nova alocacao
            No *nova = (No *)malloc(sizeof(No));
            //os conteudos das novas alocacoes serao os mesmos
            //dos conteudos da lista 2
            nova->conteudo = aux2->conteudo;
            aux2 = aux2->proximo;
            //aux vira "nova" para continuar a inserção no proximo
            aux->proximo = nova;
            aux = aux->proximo;
        }
        aux->proximo=NULL;
        //destruicao da lista 2:
        while (*lista2 != NULL){
            aux = *lista2;
            *lista2 = (*lista2)->proximo;
            free(aux);
        }
        return (*lista);
    }
}

/*Escreva uma função que recebe uma lista simplesmente encadeada e a inverte.*/
/*nessa função, é trabalhado apenas a lista original
o ultimo elemento se torna o primeiro (head)
e os antepenultimos vao se tornando os proximos da lista
seguindo a nova heap
 10 20 30 40
 10 20 30 | 40
 10 20 | 40 30
 10 | 40 30 20
 40 30 20 10
 os endereços continuam os mesmos
 só é mudado a referencia dos "proximos"*/
void inverte(No **lista){
    No *aux2 = *lista, *aux = *lista, *head;
    int cont = 0, cont_aux = 0;
    while (aux->proximo){
        aux = aux->proximo;
        //contadora guarda a quantidade de elementos que tem na lista
        cont++;
    }
    head = aux; // cabeca vira o ultimo elemento da lista
    //enquanto houver elemento, o anterior da nova head será posterior
    while (cont > 0){ 
        aux2 = *lista; //aux2 guarda o inicio da lista
        //script para ir até antes do último elemento trocado
        cont_aux = cont;
        while (cont_aux > 1){ // loop até o ultimo elemento trocado
            aux2 = aux2->proximo;
            cont_aux--;
        }
        //o proximo elemento da lista sendo invertida eh o aux2, que foi o ultimo elemento
        //da lista que ainda não foi modificado
        aux->proximo = aux2;
        //aux recebe o ultimo elemento da lista invertida para continuar com o loop
        aux = aux2;
        //menos um elemento da lista que ainda não foi invertida
        cont--;
    }
    aux2->proximo=NULL;
    (*lista)=head;
}

/*Append LDE ordenado*/
void appendLDE_ordenado(LDE **lista, int num){
	LDE *novo = (LDE *) malloc(sizeof(LDE));
	novo->conteudo=num;
	//se a lista tiver vazia
	if (!(*lista)){
		novo->proximo=NULL;
		novo->anterior=NULL;
		(*lista)=novo;
	} else {
		LDE *aux=*lista;
		while (aux->proximo && (aux->conteudo) < num){
			aux=aux->proximo;
		}
		//se nao tiver proximo
		if (!(aux->proximo) && (aux->conteudo) < num){
			//se for o ultimo elemento
			novo->proximo=NULL;
			novo->anterior=aux;
			aux->proximo=novo;
		} else {
			novo->anterior=aux->anterior;
			novo->proximo=aux;
			aux->anterior=novo;
			if (novo->anterior){
				novo->anterior->proximo=novo;
			} else {
				(*lista)=novo;
			}
		}
	}
}

/*Ver LDE*/
void seeLDE(LDE *lista){
	LDE *aux=lista;
	if (lista){
		printf("\n");
		while (aux){
			printf("%d ", aux->conteudo);
			aux=aux->proximo;
			}
		printf("\n");
		}
	}

/*Escreva uma função que recebe duas listas duplamente encadeadas ordenadas
crescentemente L1 e L2 e cria uma terceira lista L3, também ordenada
crescentemente, resultado da intercalação dos elementos de L1 e L2. Ao final da
função, L1 e L2 devem estar vazias e L3 contendo todos os elementos das duas
listas de forma ordenada crescentemente.*/
LDE *ordena_LDE(LDE **lista, LDE **lista2){
    LDE *L3=NULL;
    LDE *aux=*lista, *aux2=*lista2;
    
    if (aux){
        appendLDE_ordenado(&L3, aux->conteudo);
        while (aux->proximo){
            aux=aux->proximo;
            //utilizando a funcao já pronta de inserir de maneira ordenada
            appendLDE_ordenado(&L3, aux->conteudo);
        } 
    }
    
    if (aux2){
        appendLDE_ordenado(&L3, aux2->conteudo);
        while (aux2->proximo){
            aux2=aux2->proximo;
            appendLDE_ordenado(&L3, aux2->conteudo);
        }
    }
    
    *lista=NULL;
    *lista2=NULL;
    return L3;
    //possível melhoria: destruir as listas 1 e 2 com free, ao invés de mudar a head
}

/*Escreva uma função que insere elementos em uma lista encadeada circular*/ 
void insere_circular(No **lista, int num){
    No * head = *lista, *aux = *lista;
    No * nova = (No *) malloc(sizeof(No));
    nova->conteudo=num;
    //se a lista for nula
    if (!head){
        nova->proximo=nova;
        (*lista)=nova;
    } else {
        //enquanto o proximo não for a propria cabeça, pule para proximo
        while (aux->proximo != head){
            aux=aux->proximo;
        }
        //nova é adicionado no "final" da lista, antes da head
        aux->proximo=nova;
        nova->proximo=head;
        (*lista)=head;
    }
}

/*e outra para imprimi-la.*/
void see_circular(No *lista){
    No *aux=lista;
    if (aux){
        printf("\n");
        while (aux->proximo != lista){
            printf("%d ", aux->conteudo);
            aux=aux->proximo;
        } printf("%d\n", aux->conteudo);
    }
}