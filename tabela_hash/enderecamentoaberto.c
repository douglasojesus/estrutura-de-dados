#include <stdio.h>

//10 elementos
//10 * 2 = 20, o número primo mais próximo é: 19
//fator de carga: 10/19 = 0,52
//função de espalhamento: chave % 19

#define TAM 19

void inserindo(int *, int);
void imprimindo(int *);
int busca(int *, int);

void main(){
    int vetor[TAM], opcao=-1, num, buscado;
    for (int i=0; i<TAM; i++){
        vetor[i]=0;
    }
    do{
        printf("\n(1) inserir\n(2) imprimir\n(3) buscar\n>> ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1: printf("num: "); scanf("%d", &num); inserindo(vetor, num); break;
            case 2: imprimindo(vetor); break;
            case 3: printf("num: "); scanf("%d", &num); buscado=busca(vetor, num);
            printf("\nindice do num %d: %d\n", num, buscado); break;
        }

    } while (opcao != 0);

}

void inserindo(int vetor[], int num){
    int indice = num % TAM;
    while (vetor[indice] != 0 && indice < TAM){
        indice++;
    }
    if (vetor[indice] != 0){
        indice = 0;
        while (vetor[indice] != 0 && indice != (num%TAM)){
            indice++;
        }
    }
    if (vetor[indice] == 0){
        vetor[indice] = num;
    } else {
        printf("\nvetor cheio! não é possível adicionar mais itens!\n");
    }
}

void imprimindo(int vetor[]){
    for (int i=0; i<TAM; i++){
        printf("\nindex: %d  --  conteudo: %d", i, vetor[i]);
    }
}

int busca(int vetor[], int num){
    int indice = num % TAM;
    if (vetor[indice] == num){
        return indice;
    } else {
        while (vetor[indice] != num && indice < TAM){
            indice++;
        }
        if (vetor[indice] != num){
            indice = 0;
            while (vetor[indice] != num && indice != (num%TAM)){
                indice++;
            }
        }
        if (vetor[indice] == num){
            return indice;
        } else {
            return -1;
        }
    }
    
}