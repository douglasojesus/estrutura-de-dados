
#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int conteudo;
    struct No *proximo;
} No;

void pop(No **);
void insere(No **, int);
int soma_pares(No **);
void see(No **);
int posicao(No **, int);
No *concatena(No **, No **);
void inverte(No **);

void main()
{
    int opcao, num, soma;
    No *lista2 = NULL, *lista = NULL, *ponteiro;
    // No *lista2 = NULL;
    do
    {
        printf("\n(1) inserir no inicio;\n(2) remover o ultimo elemento;\n(3) soma dos pares;\n(4) ver lista;\n");
        printf("(5) retorna posicao;\n(6) concatena duas listas;\n(7) inverte a lista;\n>>> ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            printf("numero p/ lista: ");
            scanf("%d", &num);
            insere(&lista, num);
            // printf("numero p/ lista2: ");
            // scanf("%d", &num);
            // insere(&lista2, num);
        }
        else if (opcao == 2)
        {
            pop(&lista);
        }
        else if (opcao == 3)
        {
            soma = soma_pares(&lista);
            printf("soma dos pares: %d", soma);
        }
        else if (opcao == 4)
        {
            see(&lista);
        }
        else if (opcao == 5)
        {
            printf("numero: ");
            scanf("%d", &num);
            posicao(&lista, num);
        }
        else if (opcao == 6)
        {
            ponteiro = concatena(&lista, &lista2);
            see(&ponteiro);
        }
        else if (opcao == 7)
        {
            inverte(&lista);
        }
    } while (opcao != 0);
}

// funco insere
void insere(No **lista, int num)
{
    No *nova = (No *)malloc(sizeof(No));
    nova->conteudo = num;
    if (*lista == NULL)
    {
        nova->proximo = NULL;
    }
    else
    {
        nova->proximo = (*lista);
    }
    (*lista) = nova;
}

// funcao que recebe uma lista encadeada e retorna a soma dos pares
int soma_pares(No **lista)
{
    int soma = 0;
    No *aux = *lista;
    while (aux->proximo)
    {
        if (aux->conteudo % 2 == 0)
        {
            soma += aux->conteudo;
        }
        aux = aux->proximo;
    }
    return soma;
}

// funcao que recebe uma lista encadeada e remov o ultimo elemento da lista
void pop(No **lista)
{
    No *aux2, *aux = *lista;
    if (!aux)
    {
        printf("Sem elemento!");
    }
    else
    {
        while (aux->proximo)
        {
            aux2 = aux;
            aux = aux2->proximo;
        }
        free(aux);
        aux2->proximo = NULL;
    }
}

void see(No **lista)
{
    No *aux = *lista;
    if (aux->proximo)
    {
        while (aux->proximo)
        {
            printf("%d ", aux->conteudo);
            aux = aux->proximo;
        }
        printf("%d ", aux->conteudo);
    }
    else if (aux)
    {
        printf("%d", aux->conteudo);
    }
}

// retorna posicao
int posicao(No **lista, int num)
{
    int cont = 1;
    No *aux = *lista;
    while (aux->proximo && aux->conteudo != num)
    {
        aux = aux->proximo;
        cont++;
    }
    if (aux->conteudo == num)
    {
        return cont;
    }
    else
    {
        return -1;
    }
}

// receba L1 e L2, concatena. L1 estara conncatenada e L2 vazia;
No *concatena(No **lista, No **lista2)
{
    No *aux = *lista;
    if (!(*lista) && (*lista2))
    {
        return (*lista2);
    }
    else if ((*lista) && !(*lista2))
    {
        return (*lista);
    }
    else if (!(*lista) && !(*lista2))
    {
        return NULL;
    }
    else
    {
        while (aux->proximo)
        {
            aux = aux->proximo;
        }
        No *aux2 = *lista2;
        while (aux2->proximo)
        {
            No *nova = (No *)malloc(sizeof(No));
            nova->conteudo = aux2->conteudo;
            aux2 = aux2->proximo;
            aux->proximo = nova;
            aux = aux->proximo;
        }
        while (*lista2 != NULL)
        {
            aux = *lista2;
            *lista2 = (*lista2)->proximo;
            free(aux);
        }
        return (*lista);
    }
}

// receber lista encadeada e devolver invertida
void inverte(No **lista)
{
    No *aux2 = *lista, *aux = *lista, *head;
    int cont = 0, cont_aux = 0;
    while (aux->proximo)
    {
        aux = aux->proximo;
        cont++;
    }
    head = aux; // cabeca vira o ultimo elemento da lista
    while (cont > 0)
    {
        aux2 = *lista;
        cont_aux = cont;
        while (cont_aux > 0)
        { // loop até o ultimo elemento trocado
            aux2 = aux2->proximo;
            cont_aux--;
        }
        aux->proximo = aux2;
        aux = aux2;
        cont--;
    }
}