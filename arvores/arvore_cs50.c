#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;

// árvore é um ponteiro para um nó que é a raiz da árvore que estamos pesquisando.
// número é o valor que estamos tentando encontrar na árvore.
int search(node *tree, int number)
{
    // Primeiro, nos certificamos de que a árvore não é NULL, se alcançamos um nó
    // na parte inferior, ou se nossa árvore estiver totalmente vazia
    if(tree == NULL){
        return 0;
    }
    // Se estivermos procurando por um número menor que o número da árvore,
    // pesquisa do lado esquerdo, usando o nó à esquerda como a nova raiz
    else if(number < tree->number)
    {
        return search(tree->left, number);
    }
    // Caso contrário, pesquise no lado direito, usando o nó à direita como a nova raiz
    else if (number > tree->number)
    {
        return search(tree->right, number);
    }
    // Finalmente, encontramos o número que procuramos, portanto, podemos retornar true
    // Podemos simplificar isso para apenas "outro", uma vez que não há outro caso possível
    else if(number == tree->number)
    {
        return 1;
    }
}