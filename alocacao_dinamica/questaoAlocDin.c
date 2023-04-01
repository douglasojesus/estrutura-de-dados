/*Questão 1 - Alocação Dinâmica (já está pronta em anexo, resolvida em aula) - Não precisam enviar
Escreva um programa que lê um número inteiro N e aloca dinamicamente um vetor com N posições. 
Em seguida seu programa deve chamar uma única função que deverá ler uma sequência de N inteiros 
positivos naquele vetor, e calcular a média e a soma dos elementos do vetor. 
A main deve imprimir os resultados da função.*/

#include <stdio.h>
#include <stdlib.h>

void read(int *, int, int *);

int main(){
    int N, soma=0;
    int * vetor;
    printf("Um inteiro N: "); scanf("%d", &N);
    vetor = malloc(N * (sizeof(int)));
    read(vetor, N, &soma);
    printf("A soma: %d", soma);
    printf("\nA media: %.2f", (float) soma/N);
}

void read(int * vetor, int N, int * soma){
    for (int i=0; i<N; i++){
        printf("digite um numero positivo: "); scanf("%d", &vetor[i]);
        *soma=*soma+vetor[i];
    }
}