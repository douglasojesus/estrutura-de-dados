/*Questão 2 - Struct:
Um cliente em um banco é representado por:
• Número da conta - um número inteiro;
• Número da agência - um número inteiro;
• Saldo.
Escreva um programa que defina um registro capaz de armazenar um cliente do banco. 
Seu programa deve ler os dados de N clientes e armazená-los em um vetor, em seguida 
seu programa deve chamar uma única função para calcular a média dos saldos dos clientes, 
encontrar o número da conta e da agência do cliente com maior saldo e a conta e 
a agência do cliente com menor saldo. Além disso, deve calcular a porcentagem de 
clientes com saldo inferior a R$1000,00. Todas as respostas devem ser impressas 
pela função principal.*/

#include <stdio.h>

typedef struct{
    int conta;
    int agencia;
    float saldo;
} Cliente;

void read(Cliente *, int);
void fazTudo(Cliente *, int, float *, int *, int *, int *, int *, int *);

int main(){
    int num, agMaior, ctMaior, agMenor, ctMenor, inferior_a_mil=0;
    float soma=0;
    int *PTagMaior=&agMaior, *PTctMaior=&ctMaior, *PTagMenor=&agMenor, *PTctMenor=&ctMenor, 
    *PTinferior_a_mil=&inferior_a_mil;
    float *PTsoma=&soma;
    printf("Numero de clientes: "); scanf("%d", &num);
    Cliente clientes[num];
    read(clientes, num);
    fazTudo(clientes, num, PTsoma, PTagMaior, PTctMaior, PTagMenor, PTctMenor, PTinferior_a_mil);
    printf("\nA media dos saldos: %f", soma/num);
    printf("\nConta e Agencia do maior saldo: %d | %d", ctMaior, agMaior);
    printf("\nConta e Agencia do menor saldo: %d | %d", ctMenor, agMenor);
    printf("\nPorcentagem de clientes com saldo inferior a mil: %2d%%", (inferior_a_mil*100)/num);
    return 0;
}

void read(Cliente * clientes, int num){
    for (int i=0; i<num; i++){
        printf("\nconta: "); scanf(" %d", &clientes[i].conta);
        printf("agencia: "); scanf(" %d", &clientes[i].agencia);
        printf("saldo: "); scanf(" %f", &clientes[i].saldo);
    }
    printf("\nDados cadastrados!");
}

void fazTudo(Cliente * clientes, int num, float * soma, 
int * agMaior, int * ctMaior, int * agMenor, int * ctMenor, int * inferior_a_mil){
    float maior_saldo=clientes[0].saldo, menor_saldo=clientes[0].saldo;
    for (int i=0; i<num; i++){
        *soma+=clientes[i].saldo;
        if (clientes[i].saldo > maior_saldo){
            *agMaior=clientes[i].agencia;
            *ctMaior=clientes[i].conta;
            maior_saldo=clientes[i].saldo;
        } if (clientes[i].saldo < menor_saldo){
            *agMenor=clientes[i].agencia;
            *ctMenor=clientes[i].conta;
            menor_saldo=clientes[i].saldo;
        } if (clientes[i].saldo < 1000){
            *inferior_a_mil=*inferior_a_mil+1;
        }

    }

}