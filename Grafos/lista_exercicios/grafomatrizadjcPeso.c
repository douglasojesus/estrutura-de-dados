# include <stdlib.h>
# include <stdio.h>
# include <conio.h>

typedef struct{
  int n;
  int **Adj;
} Grafo;

void CriaGrafoVazio (Grafo *, int ); //n precisou corrigir
void InsereAresta (Grafo, int, int, int); //corrigido
int ExisteAresta (Grafo, int, int); //corrigido
void RemoveAresta (Grafo, int, int); //n precisou corrigir
void LiberaGrafo (Grafo *); //n precisou corrigir
void ImprimeGrafo (Grafo); //corrigido
void LeGrafoArquivo (Grafo *, char *); //n precisou corrigir
void ImprimeGrafoArquivo (Grafo, char *); //n precisou corrigir
void ImprimeAdjc(Grafo, int); //n precisou corrigir
int GrauVertice(Grafo, int); //n precisou corrigir
void GrauMaxMin(Grafo); //n precisou corrigir
void GrauIOVertice(Grafo, int); //n precisou corrigir
void Caminho(Grafo); //n precisou corrigir
void removeArestaMin(Grafo *); 

int main(){
	int resp, aux, u, v, num, peso;
	char c, nomeArq[50];
	Grafo G;
	
	do{
		printf("\n\nEscolha uma das opcoes abaixo:\n\n");
		printf("(1) Le um grafo do arquivo.\n");
		printf("(2) Insere uma aresta.\n");
		printf("(3) Busca uma aresta.\n");
		printf("(4) Remove uma aresta.\n");
		printf("(5) Imprime o grafo na tela.\n");
		printf("(6) Imprime o grafo no arquivo.\n");
		printf("(7) Imprime adjascentes.\n");
		printf("(8) Imprime grau do vertice.\n");
		printf("(9) Imprime o grau max e min do grafo.\n");
		printf("(10) Imprime grau de entrada e saida de um vertice.\n");
		printf("(11) Informa se uma sequencia de inteiros eh caminho.\n");
		printf("(12) Remove aresta minima.\n");
		printf("(13) Sai do programa.\n");
		printf("\nOpcao: ");
		scanf("%d", &resp);

		switch(resp){
			case (1):
				printf("\n\nDigite o nome do arquivo que contem o grafo:");
				fflush(stdin);
				//gets(nomeArq);
				scanf("%s", nomeArq);
				LeGrafoArquivo (&G, nomeArq);
				break;
				
			case (2):
				printf("\n\nDigite a primeira extremidade da aresta:");
				scanf("%d", &u);
				printf("\n\nDigite a segunda extremidade da aresta:");
				scanf("%d", &v);
				printf("\n\nDigite o peso: ");
				scanf("%d", &peso);
				InsereAresta (G, u, v, peso);
				break;
				
			case (3):
				printf("\n\nDigite a primeira extremidade da aresta:");
				scanf("%d", &u);
				printf("\n\nDigite a segunda extremidade da aresta:");
				scanf("%d", &v);

				aux = ExisteAresta (G, u, v);
				if(aux)
					printf ("Aresta encontrada!");
				else
					printf("\n\nAresta nao encontrada!");			
				break;
			
			case (4):
				printf("\n\nDigite a primeira extremidade da aresta:");
				scanf("%d", &u);
				printf("\n\nDigite a segunda extremidade da aresta:");
				scanf("%d", &v);
				RemoveAresta(G, u, v);
				break;
			
			case (5):
				ImprimeGrafo (G);
				break;
				
			case (6):
				printf("\n\nDigite o nome do arquivo onde deseja salvar o grafo:");
				fflush(stdin);
				scanf("%s", nomeArq);
				ImprimeGrafoArquivo (G, nomeArq);
				break;

			case (7):
				printf("\nInsira o índice: ");
				scanf("%d", &num);
				ImprimeAdjc(G, num);
				break;

			case (8):
				printf("\nInsira o índice: ");
				scanf("%d", &num);
				printf("\nO grau do índice %d eh: %d.", num, GrauVertice(G, num));
				break;
			
			case (9):
				GrauMaxMin(G);
				break;

			case (10):
				printf("\nInsira o indice: ");
				scanf("%d", &num);
				GrauIOVertice(G, num);
				break;

			case (11):
				Caminho(G);
				break;

			case (12):
				removeArestaMin(&G);
				break;

			case (13):
				printf("Fim do programa!");
				break;
			
			default:
				printf("Opcao Invalida!");
				break;
		}
	}while(resp != 13);
	LiberaGrafo(&G);
}

/* inicializa um grafo vazio com os vértices 0, 1, ..., n - 1 */
void CriaGrafoVazio (Grafo *G, int n)
{  
  int u;
  int v;

  G->n = n;
  /* alocando espaço de memória para a matriz de adjacência */
  
  G->Adj = (int **) malloc (n * sizeof (int *));
  for (u = 0; u < n; u++)
    G->Adj[u] = (int *) malloc (n * sizeof (int));
  /* ===================================================== */

  /* inicializando o grafo vazio */
  for (u = 0; u < n; u++)
    for (v = 0; v < n; v++)
      G->Adj[u][v] = 0;
}

/* insere a aresta (u, v) no grafo g */
void InsereAresta (Grafo G, int u, int v, int peso){
  G.Adj[u][v] = peso;
}

/* devolve 1 se a aresta (u, v) é aresta de g;
   0, caso contrário */
int ExisteAresta (Grafo G, int u, int v){
	if (G.Adj[u][v]){
		return 1;
	}
	return 0;
}

/* remove a aresta (u, v) do grafo g */
void RemoveAresta (Grafo G, int u, int v){
  G.Adj[u][v] = 0;
}

/* libera o espaço de memória alocado para o grafo g */ 
void LiberaGrafo (Grafo *G){
  int u;
  for (u = 0; u < G->n; u++)
    free (G->Adj[u]);
  free (G->Adj);
  G -> n = 0;
}

/* imprime na tela uma lista de adjacência de cada vértice */
void ImprimeGrafo(Grafo grafo){
	for (int i=0; i<grafo.n; i++){
		printf("\nVertice %d: ", i);
		for (int j=0; j<grafo.n; j++){
			if (grafo.Adj[i][j]){
				printf("%d(%d) ", j, grafo.Adj[i][j]);
			}
		}
	}
	printf("\n");
}

void LeGrafoArquivo (Grafo *G, char *arq){
	int n, i, j;
	FILE *f;
	f = fopen (arq, "r");
	fscanf (f, "%d", &n);  
	CriaGrafoVazio (G, n);  
	for (i = 0; i < G->n; i++)
		for (j = 0; j < G->n; j++)
		fscanf (f, "%d", &G->Adj[i][j]);  
	fclose (f);
}

void ImprimeGrafoArquivo (Grafo G, char *arq){  
	int i, j;
	FILE *f;
	f = fopen (arq, "w");
	fprintf (f, "%d\n", G.n);
	for (i = 0; i < G.n; i++)
	{
	    for (j = 0; j < G.n; j++)
	      	fprintf (f, "%d ", G.Adj[i][j]);
	    fprintf (f, "\n");
	}
  fclose (f);
}

//Imprime a lista de adjacentes de um dado vértice u;
void ImprimeAdjc(Grafo G, int index){
	for (int i = 0; i < G.n; i++){
		if (G.Adj[index][i])
			printf("%d ", i);
	}
}

//Calcula o grau de um dado vértice através de uma função;
int GrauVertice(Grafo G, int index){
	int cont = 0;
	for (int i = 0; i < G.n; i++){
		if (G.Adj[index][i])
			cont++;
	}
	return cont;
}

//Calcula o grau máximo e o grau mínimo de um grafo;
void GrauMaxMin(Grafo G){
	int cont;
	int graumax = 0;
	int graumin = (G.n)-1;
	for (int i=0; i<G.n; i++){
		cont = 0;
		for (int j=0; j<G.n; j++){
			if (G.Adj[i][j])
				cont++;
		}
		if (cont > graumax){
			graumax=cont;
		}
		if (cont < graumin){
			graumin=cont;
		}
	}
	printf("\nGrau maximo: %d\nGrau minimo: %d", graumax, graumin);
}

//Calcule o grau de entrada e o grau de saída de um dado vértice;
void GrauIOVertice(Grafo G, int index){
	int gentrada=0, gsaida=0;
	for (int i=0; i<G.n; i++){
		if (G.Adj[i][index]){ //acessando colunas, entradas
			gentrada++;
		}
		if (G.Adj[index][i]){ //acessando os itens da linha, saidas
			gsaida++;
		}
	}
	printf("Grau de entrada: %d\nGrau de saida: %d", gentrada, gsaida);
}

//Ler n inteiros e dizer se é uma sequência de vértices representando um caminho no grafo.
void Caminho(Grafo G){
	int n, num;
	printf("\nInforme a quantidade de numeros a serem lidos: ");
	scanf("%d", &n);
	int vetor[n];
	for (int i=0; i<n; i++){
		printf("\nNum: ");
		scanf("%d", &vetor[i]);
	}
	for (int i=0; i<n-1; i++){
		if (!(G.Adj[vetor[i]][vetor[i+1]])){
			printf("\nNão é um caminho!");
			return;
		}
	}
	printf("\nÉ um caminho!");
}

//remove aresta minima
void removeArestaMin(Grafo *grafo){
    int linhaMin, colunaMin, pesoMin;
    int primeiro = 1;
    for (int i=0; i<grafo->n; i++){
        for (int j=0; j<grafo->n; j++){
            if (grafo->Adj[i][j]){
                if (primeiro){
                    pesoMin = grafo->Adj[i][j];
                    primeiro = 0;
                }
                if (grafo->Adj[i][j] <= pesoMin){ //o minimo entre os maiores que 0
                    pesoMin = grafo->Adj[i][j];
                    linhaMin = i;
                    colunaMin = j;
                }
            }
        }
    }
    grafo->Adj[linhaMin][colunaMin] = 0;
}