/*Crie uma versão do programa GrafoMatriz.c que considere um grafo
com peso nas arestas. Modifique as funções que precisem ser
modificadas e crie uma função que remove a aresta de peso mínimo.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Grafo{
    int tamanho;
    int **matriz;
} Grafo;

Grafo inicializaGrafo(void);
void imprimeGrafo(Grafo);
void insereGrafo(Grafo *);
void removeArestaMin(Grafo *);

void main(){
    int opcao=1;
    Grafo grafo = inicializaGrafo();
    do{
        printf("(1) IMPRIME GRAFO\n");
        printf("(2) INSERE ARESTA\n");
        printf("(3) REMOVE ARESTA DE PESO MINIMO;\n");
        printf(">>> ");
        scanf("%d", &opcao);
        switch (opcao){
            case (1):
                imprimeGrafo(grafo);
                break;

            case (2):
                insereGrafo(&grafo);
                break;

            case (3):
                removeArestaMin(&grafo);
                break;
        }   
    } while (opcao != 0);
}

Grafo inicializaGrafo(void){
    int tam;
    printf("\nTamanho da matriz adjascente: ");
    scanf("%d", &tam);
    Grafo grafo;
    grafo.tamanho = tam;
    grafo.matriz = (int**) malloc(sizeof(int *)*tam);
    for (int i=0; i<tam; i++){
        grafo.matriz[i] = (int*) malloc(sizeof(int)*tam);
    }
    for (int i=0; i<tam; i++){
        for (int j=0; j<tam; j++){
            grafo.matriz[i][j] = 0;
        }
    }
    return grafo;
}

void imprimeGrafo(Grafo grafo){
    for (int i=0; i<grafo.tamanho; i++){
        printf("\nVertice %d: ", i);
        for (int j=0; j<grafo.tamanho; j++){
            if (grafo.matriz[i][j]){
                printf("%d(%d) ", j, grafo.matriz[i][j]);
            }
        }
    }
    printf("\n");
}

void insereGrafo(Grafo *grafo){
    int vert1, vert2, peso;
    printf("\nDigite os dois vertices separados por espaco: ");
    scanf("%d %d", &vert1, &vert2);
    printf("Digite o peso: ");
    scanf("%d", &peso);
    grafo->matriz[vert1][vert2] = peso;
}

void removeArestaMin(Grafo *grafo){
    int linhaMin, colunaMin, pesoMin;
    int primeiro = 1;
    for (int i=0; i<grafo->tamanho; i++){
        for (int j=0; j<grafo->tamanho; j++){
            if (grafo->matriz[i][j]){
                if (primeiro){
                    pesoMin = grafo->matriz[i][j];
                    primeiro = 0;
                }
                if (grafo->matriz[i][j] <= pesoMin){ //o minimo entre os maiores que 0
                    pesoMin = grafo->matriz[i][j];
                    linhaMin = i;
                    colunaMin = j;
                }
            }
        }
    }
    grafo->matriz[linhaMin][colunaMin] = 0;
}