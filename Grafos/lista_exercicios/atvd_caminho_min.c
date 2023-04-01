/*
COMPANHIA AÉREA GOOD FEELINGS
Atividade sobre caminhos mínimos.
Aluno: Douglas Oliveira de Jesus
Disciplina: Estrutura de Dados
Professora: Ana Lúcia
*/

//Arestas: tempo.
//Objetivo: o tempo mais rápido de Joy até as outras cidades.
#include <stdio.h>
#include <stdlib.h>

typedef struct Voo{
    int num;
    int origem;
    int destino;
    int tempo;
} Voo;

typedef struct Grafo{
    int tam;
    Voo ** matriz;
} Grafo;

#define INFINITO 999999

Grafo inicializaGrafo(int tam){
    Grafo grafo;
    grafo.matriz = malloc(sizeof(Voo) * tam);
    grafo.tam = tam;
    for (int i=0; i<tam; i++){
        grafo.matriz[i] = malloc(sizeof(Voo) * tam);
    }
    for (int i=0; i<tam; i++){
        for (int j=0; j<tam; j++){
            grafo.matriz[i][j].tempo = 0;
        }
    }
    return grafo;
}

Grafo leArquivo(char * endereco, int tam){
    FILE * arquivo;
    int linhas;
    arquivo = fopen(endereco, "r");
    Grafo grafo = inicializaGrafo(tam);
    printf("Quantas linhas tem o arquivo: ");
    scanf("%d", &linhas);
    for (int i= 0; i<linhas; i++){
        int numero_voo, cod_origem, cod_destino, tempo_voo;
        fscanf(arquivo, "%d", &numero_voo);
        fscanf(arquivo, "%d", &cod_origem);
        fscanf(arquivo, "%d", &cod_destino);
        fscanf(arquivo, "%d", &tempo_voo);
        grafo.matriz[cod_origem][cod_destino].num = numero_voo;
        grafo.matriz[cod_origem][cod_destino].origem = cod_origem;
        grafo.matriz[cod_origem][cod_destino].destino = cod_destino;
        grafo.matriz[cod_origem][cod_destino].tempo = tempo_voo;
    }
    fclose(arquivo);
    return grafo;
}

void imprimeGrafo(Grafo grafo){
    for (int i=0; i<grafo.tam; i++){
        for (int j=0; j<grafo.tam; j++){
            printf("%d ", grafo.matriz[i][j].tempo);
        }
        printf("\n");
    }
    printf("\n");
}

//CAMINHO MAIS CURTO

int * vetorCusto(Grafo grafo, int origem){
    int * vetorcusto = malloc(sizeof(int*)*grafo.tam);
    for (int i=0; i<grafo.tam; i++){
        vetorcusto[i] = INFINITO; //distancia eh infinita para todos os vertices inicialmente
    }
    vetorcusto[origem] = 0; //distancia da origem para origem eh 0
    return vetorcusto;
}

int menorCaminhoAtual(Grafo grafo, int * vetorcusto, int * determinado){ //retorna o indice do menor caminho do vetor custo
    int menor=INFINITO;
    int indice=-1;
    for (int i=1; i<grafo.tam; i++){
        if (vetorcusto[i] < menor && determinado[i] == 0){
            menor = vetorcusto[i];
            indice = i;
        }
    }
    return indice;
}

int * dijkstra(Grafo grafo, int origem, int * predecessores){
    int * vetorcusto = vetorCusto(grafo, origem); //vetor que tem os caminhos
    int * determinado = malloc(sizeof(int *)*grafo.tam); //vetor determinado
    for (int i=0; i<grafo.tam; i++){
        determinado[i] = 0;
    }
    int verticeatual = origem;
    while (verticeatual != -1){ //enquanto ainda tiver vertice nao determinado
        for (int i=0; i<grafo.tam; i++){ //do vertice atual a todos seus adjacentes
            if (grafo.matriz[verticeatual][i].tempo){
                if (grafo.matriz[verticeatual][i].tempo + vetorcusto[verticeatual] < vetorcusto[i]){ //se o caminho atual for menor que o do vetor
                    vetorcusto[i] = grafo.matriz[verticeatual][i].tempo + vetorcusto[verticeatual];
                    predecessores[i] = verticeatual;
                }
            }
        }
        determinado[verticeatual] = 1;
        verticeatual = menorCaminhoAtual(grafo, vetorcusto, determinado);
    }
    return vetorcusto;
}

void main(){
    char endereco[30];
    int tamanho=9, cidade_destino;
    int origem, destino;
    int * predecessores = malloc(sizeof(int *)*tamanho);
    for (int i=0; i<tamanho; i++){
        predecessores[i] = -1;
    }
    printf("O TAMANHO DO GRAFO EH 9, POIS SAO 9 CIDADES!\n");
    printf("\nNome do arquivo do grafo: ");
    scanf("%s", endereco);
    Grafo grafo = leArquivo(endereco, tamanho);
    imprimeGrafo(grafo);
    int * vetor = dijkstra(grafo, 0, predecessores);
    printf("\nDigite o codigo da cidade destino: ");
    scanf("%d", &destino);
    printf("\nVetor de custo: ");
    for (int i=0; i<grafo.tam; i++){
        if (vetor[i] != INFINITO)
            printf("\n%d: %d", i, vetor[i]);
    }
    printf("\nPredecessores: ");
    for (int i=0; i<grafo.tam; i++){
        if (predecessores[i] != -1)
            printf("\n%d: %d", i, predecessores[i]);
    }
    printf("\nPara chegar na cidade destino de codigo %d, o menor tempo eh: %d minutos.", destino, vetor[destino]);
    printf("\nOs voos utilizados nesse trajeto sao: ");
    while (destino != 0){
        printf("\n%d", grafo.matriz[predecessores[destino]][destino].num);
        destino = predecessores[destino];
    }
}