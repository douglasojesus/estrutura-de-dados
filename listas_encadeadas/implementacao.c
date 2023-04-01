//Implementação de uma lista encadeada com as funções de inserir, visualizar, buscar e remover.

#include <stdio.h>
#include <stdlib.h>

//Criando a estrutura para a célula da lista.
typedef struct node{
    int value;
    struct node * next;
} node;

//Declarando as funções.
int menu();
void appendinicio(node **);
void append(node **);
void see(node *);
int search(node *);
void removenum(node **);
void removeall(node **);

void main(){
    //Declarando variáveis;
    node * head = NULL;
    int comando;
    //Loop.
    do{
        comando = menu();
        if (comando == 1){
            appendinicio(&head);
        } else if (comando == 2){
            append(&head);
        } else if (comando == 3){
            see(head);
        } else if (comando == 4){
            search(head);
        } else if (comando == 5){
            removenum(&head);
        } else if (comando == 6){
            removeall(&head);
        }
    }while (comando != 7);
}

void appendinicio(node ** lista){
    int entrada;
    printf("Digite o numero inteiro: "); scanf("%d", &entrada);
    //Se a lista tiver vazia.
    if (!(*lista)){
        (*lista) = (node *) malloc(sizeof(node));
        (*lista)->value=entrada;
        (*lista)->next=NULL;
        printf("\nENDERECO DA HEAD >>>> %p\n", *lista);
    } //Se a lista tiver elemento.
    else {
        node * new = (node *) malloc(sizeof(node));
        printf("\nNOVO ENDERECO ALOCADO >>>> %p", new);
        new->value=entrada;
        printf("\nENDERECO DA ANTIGA HEAD >>>> %p", *lista);
        new->next=*lista; //O proximo do new sempre vai ser o início da lista;
        *lista=new; //O início da lista torna a ser o novo nó criado.
        printf("\nENDERECO DA NOVA HEAD >>>> %p\n", *lista);
        
    }
}

void append(node ** lista){
    int entrada;
    printf("Digite o numero inteiro: "); scanf("%d", &entrada);
    //Se a lista tiver vazia.
    if (!(*lista)){
        (*lista) = (node *) malloc(sizeof(node));
        (*lista)->value=entrada;
        (*lista)->next=NULL;
        printf("\nENDERECO DA HEAD >>>> %p\n", *lista);
    } else {
        node * new = (node *) malloc(sizeof(node));
        printf("\nNOVO ENDERECO ALOCADO >>>> %p\n", new);
        node * aux = *lista;
        //Verificando se o next aponta para nulo.
        while (aux->next){
            aux = aux -> next; //Se não, aux vai percorrendo a lista até encontrar o último.
        }
        aux -> next = new; //New é adicionado no final da lista.
        new -> value = entrada;
        new -> next = NULL; //New aponta para NULL.
    }
}

void see(node * lista){
    node * aux = lista;
    if (!aux){
        printf("[]");
    } else {
        printf("\n[");
        while (aux){
            printf("%d", aux->value);
            aux = aux->next;
            if (aux){
                printf(", ");
            } else {
                printf("]\n");
            }
        }
    }
}

int search(node * lista){
    int index=0, busca;
    node * aux = lista;
    printf("\nNumero a ser buscado: "); scanf("%d", &busca);
    while (aux && aux->value != busca){
        index++;
        aux=aux->next;
    }
    if (aux){
        printf("\nElemento encontrado no index: %d\n", index);
    } else {
        printf("\nElemento não encontrado!\n");
    }
}

void removenum(node ** lista){
    //Criando variaveis auxiliares.
    node * aux1 = *lista, * aux2 = *lista;
    int eliminar;
    printf("\nNumero a ser eliminado: "); scanf("%d", &eliminar);
    if (aux1->value == eliminar){
        *lista = (*lista)->next;
        free(aux1);
        printf("\nNumero removido com sucesso!\n");
    } else {
        while (aux1 && aux1->value != eliminar){
            aux2 = aux1;
            aux1 = aux1->next;
        }
        if (aux1 != NULL){
            aux2 -> next = aux1 -> next;
            free(aux1);
            printf("\nNumero removido com sucesso!\n");
        } else {
            printf("\nNumero nao encontrado na lista.\n");
        }
    }
}

void removeall(node ** lista){
    node * aux1 = *lista;
    while (aux1){
        *lista = (*lista)->next;
        free(aux1);
        aux1 = *lista;
    }
    printf("\nNumeros removidos com sucesso!");
}

int menu(){
    int entrada;
    printf("\nO que você quer fazer?\n");
    printf("[1] Inserir elemento no início da lista;\n");
    printf("[2] Inserir elemento no final da lista;\n");
    printf("[3] Visualizar toda a lista;\n");
    printf("[4] Buscar um elemento na lista;\n");
    printf("[5] Remover um elemento da lista;\n");
    printf("[6] Remover toda a lista;\n");
    printf("[7] Quit.\n");
    do {
        printf("Coloque de [1] a [7]:\n->>> "); scanf("%d", &entrada);
    } while (entrada != 1 && entrada != 2 && entrada != 3 && entrada != 4 && 
    entrada != 5 && entrada != 6 && entrada != 7);
    return entrada;
}

/*Testes
1
23
1
32
1
52
1
78
1
998
2
845
2
669
2
0
1
7
3
5
*/