/*Questão 2 - Alocação Dinâmica
Uma empresa de seguros deseja cadastrar os seguintes dados de cada um de 
seus clientes: matrícula do cliente, nome do cliente, valor da apólice, 
idade do cliente, estado civil do cliente (S, C ou D). Escreva um programa
que contenha uma estrutura capaz de armazenar os dados de cada cliente. 
O programa também deve ler o número de clientes da empresa, armazenar os
dados de todos os clientes em um vetor alocado dinamicamente, e chamar 
uma função que calcula e imprime a média de valores de apólice dos clientes
casados, o nome e o estado civil do cliente com o maior valor de apólice, 
e a porcentagem de clientes com menos de 40 anos.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int matricula;
    char nome[50];
    float apolice;
    int idade;
    char est_civil;
} Cliente;

void read(Cliente *, int);
void faztudo(Cliente *, int);

int main(){
    int num;
    printf("numero de clientes da empresa: "); scanf("%d", &num);
    Cliente * vetor = (Cliente *) malloc(num * sizeof(Cliente));
    read(vetor, num);
    faztudo(vetor, num);
}

void read(Cliente * vetor, int num){
    for (int i=0; i<num; i++){
        printf("matricula: "); scanf(" %d", &vetor[i].matricula);
        printf("nome: "); scanf(" %s", vetor[i].nome);
        printf("apolice: "); scanf(" %f", &vetor[i].apolice);
        printf("idade: "); scanf(" %d", &vetor[i].idade);
        printf("estado civil: "); scanf(" %c", &vetor[i].est_civil);
    }
    printf("Dados cadastrados!");
}

void faztudo(Cliente * vetor, int num){
    float soma_apolice=0;
    float maior_apolice=vetor[0].apolice;
    char nome_maior_apolice[50];
    strcpy(nome_maior_apolice, vetor[0].nome);
    char est_civil_maior_apolice=vetor[0].est_civil;
    int clientes_menos_40=0, num_casados=0;

    for (int i=0; i<num; i++){
        if (vetor[i].est_civil == 'C'){
            soma_apolice+=vetor[i].apolice;
            num_casados++;
        }
        if (vetor[i].apolice > maior_apolice){
            maior_apolice=vetor[i].apolice;
            strcpy(nome_maior_apolice, vetor[i].nome);
            est_civil_maior_apolice=vetor[i].est_civil;
        }
        if (vetor[i].idade < 40){
            clientes_menos_40++;
        }
    }

    printf("\nA media de valores de apolice dos casados: %.2f", soma_apolice/num_casados);
    printf("\nNome e estado civil de cliente com maior apolice: %s | %c", nome_maior_apolice, est_civil_maior_apolice);
    printf("\nPorcentagem de clientes com menos de 40 anos: %d%%", (clientes_menos_40*100)/num);
}

/*Teste:
5
1234
Douglas
5000.0
20
C
2345
Joao
90000
37
S
3456
Maria
10
20
D
4567
Joana
120000
40
C
5678
Marcelina
12345
39
C

Resultados:
45781.66
Joana | C
80%
*/