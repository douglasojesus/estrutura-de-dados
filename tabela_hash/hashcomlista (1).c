#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    struct no * proximo;
} no;

typedef struct th{
    int posicao;
    no * head;
} th;

int funcaohash(int, int);
th * criarTabela(int);
void inserir(th **, int, int);
void imprimir(th *, int);

void main(){
    int opcao=-1, num;
    int tamanhotabela = 10;
    printf("\nTABELA HASH\n");
    th * tabela = criarTabela(tamanhotabela);
    do {
        printf("\n(1) inserir\n(2) imprimir\n(3) buscar\n>> ");
        scanf("%d", &opcao);
        switch (opcao){
        case 1: printf("num: "); scanf("%d", &num); inserir(&tabela, tamanhotabela, num); break;
        case 2: imprimir(tabela, tamanhotabela);
        }
    } while (opcao);

}

int funcaohash(int tam, int chave){
    return (chave % tam);
}

th * criarTabela(int tam){
    th * novo = (th *) malloc(tam * sizeof(th));
    th * aux = novo;
    if (novo){ //se alocou com sucesso
        for (int i=0; i<tam; i++){
            aux->posicao=i;
            aux->head=NULL;
            aux+=1; // quando você coloca o i do for, se você reparar bem as posição vão passar do limite. Por exemplo o aux += 1, ele vai pra posição 1, correto? 
            //agora o proximo i vai ser 2, ou seja aux+=2 PARTINDO DA POSICAO 1, por isso ai o erro. QUando você coloca +=1 sempre, ele sempre vai andar UMA posição.
        }
        return novo;
    } else {
        printf("\nerro ao criar tabela!\n");
        return NULL;
    }
}

void imprimir(th * tabela, int tam){//Outra coisa, não há necessidade de passar ponteiro de ponteiro quando se quer MOSTRAR/PRINTAR algo, ponteiro de ponteiro,
// é quando você quer ALTERAR algo dentro dua sua estrutura dinamica(alocada).
    if (tabela){
        th * aux = tabela;
        for (int i=0; i<tam; i++){
            no * celula = aux->head;// Você tava pegando o valor da variavel TABELA, ou seja o valor de tabela nessa função da FIXA, oq vc tá mudando é a variavel AUX,
            // Por isso aqui é aux->head.
            printf("\nindice: %d -> ", aux->posicao);
            while (celula){
                printf("%d ", celula->conteudo);
                celula=celula->proximo;
            }
            aux+=1;
        }
    }
}

void inserir(th ** tabela, int tamanho, int num){
    if (*tabela){
        int indice = funcaohash(tamanho, num);
        no * novo = (no *) malloc(sizeof(no));
        novo->conteudo = num;
        th * aux=(*tabela);
        aux = aux + indice;
        novo->proximo = aux->head;
        aux->head=novo;
        //otimização: usar ((*tabela)+indice)->head; ao invés de criar aux
    }
}