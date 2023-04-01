

/*
Passos:
Ler arquivo;
Registrar dados do arquivo;
Ler uma cidade destino;
Retornar qual menor tempo possível;
Retornar quais sãos os voos utilizados no trajeto.
*/

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
    arquivo = fopen(endereco, "r");
    Grafo grafo = inicializaGrafo(tam);
    for (int i= 0; i<4; i++){
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

int indiceCustoMenor(int * vetorcustomenor, Grafo grafo){
    int indice = 0;
    int menorcusto = vetorcustomenor[0];
    for (int i=0; i<grafo.tam; i++){
        if (vetorcustomenor[i] < menorcusto && (vetorcustomenor[i] != -1)){
            menorcusto = vetorcustomenor[i];
            indice = i;
        }
    }
    return indice;
}

void removerIndiceCustoMenor(int * vetorcustomenor, int indice){
    vetorcustomenor[indice] = -1;
}

void verificarAdjacentes(Grafo grafo, int indice_origem){
    for (int i=0; i<grafo.tam; i++){
        grafo.matriz[indice_origem][i];
    }
}

int maiorAresta(Grafo grafo){
    int maior=0;
    for (int i=0; i<grafo.tam; i++){
        for (int j=0; j<grafo.tam; j++){
            if (grafo.matriz[i][j].tempo > maior){
                maior = grafo.matriz[i][j].tempo;
            }
        }
    }
    return maior;
}

int * vetorCusto(Grafo grafo, int origem){
    int vetorcusto[grafo.tam];
    int maioraresta = maiorAresta(grafo);
    for (int i=0; i<grafo.tam; i++){
        vetorcusto[i] = (maioraresta*(grafo.tam - 1)) + 1; //distancia eh infinita para todos os vertices inicialmente
    }
    vetorcusto[origem] = 0; //distancia da origem para origem eh 0
    return vetorcusto;
}

int menorCaminhoAtual(Grafo grafo, int * vetorcusto, int * determinado){ //retorna o indice do menor caminho do vetor custo
    int maioraresta = maiorAresta(grafo);
    int menor=maioraresta*(grafo.tam - 1) + 1;
    int indice=-1;
    for (int i=1; i<grafo.tam; i++){
        if (vetorcusto[i] < menor && determinado[i] == 0){
            menor = vetorcusto[i];
            indice = i;
        }
    }
    return indice;
}

void dijkstra(Grafo grafo, int origem){
    int * vetorcusto = vetorCusto(grafo, origem); //vetor que tem os caminhos
    int determinado[grafo.tam]; //vetor determinado
    for (int i=0; i<grafo.tam; i++){
        determinado[i] = 0;
    }
    int verticeatual = origem;
    while (verticeatual != -1){ //enquanto ainda tiver vertice nao determinado
        for (int i=0; i<grafo.tam; i++){ //do vertice atual a todos seus adjacentes
            if (grafo.matriz[verticeatual][i].tempo){
                if (grafo.matriz[origem][i].tempo + vetorcusto[verticeatual] < vetorcusto[i]){ //se o caminho atual for menor que o do vetor
                    vetorcusto[i] = grafo.matriz[origem][i].tempo + vetorcusto[verticeatual];
                }
            }
        }
        determinado[verticeatual] = 1;
        //int verticeatual = menorCaminhoAtual(grafo, vetorcusto);
    }
}

void main(){
    char endereco[30];
    int tamanho, cidade_destino;
    printf("\nNome do arquivo do grafo: ");
    scanf("%s", endereco);
    printf("\nTamanho do grafo: ");
    scanf("%d", &tamanho);
    Grafo grafo = leArquivo(endereco, tamanho);
    imprimeGrafo(grafo);
    printf("Codigo da cidade destino: ");
    scanf("%d", &cidade_destino);
    dijkstra(grafo, 0);
}

/*
0 Joy
1 Hope
2 Friendship
3 Surprise
4 Honesty
5 Wonderland
6 Optimism
7 Confidence
8 Happiness
*/

/*


void incializaCaminhoMaisCurto(Grafo grafo, int origem, int * predecessor, int * distancia){
    int maioraresta = maiorAresta(grafo);
    for (int i=0; i<grafo.tam; i++){
        predecessor[i] = -1;
        distancia[i] = (maioraresta*(grafo.tam - 1)) + 1;
    }
    distancia[origem] = 0;
}

void relaxamento(int v, int u, int * distancia, int * predecessor, Grafo grafo){
    if (distancia[v] > distancia[u] + grafo.matriz[u][v].tempo){
        predecessor[v] = u;
        distancia[v] = distancia[u] + grafo.matriz[u][v].tempo;
    }
}


void dijkstra(Grafo grafo, int origem){
    int predecessor[grafo.tam];
    int distancia[grafo.tam];
    int vertices[grafo.tam];
    for (int i=0; i<grafo.tam; i++){
        vertices[i] = i;
    }
    incializaCaminhoMaisCurto(grafo, origem, predecessor, distancia);
    while (vertices){
        
    }

}
*/