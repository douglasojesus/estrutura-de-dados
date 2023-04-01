/*Foi feita uma pesquisa em uma cidade.  De cada entrevistado foram coletados 
os seguintes dados: idade, sexo, número de filhos e salário. Escreva um programa 
que contenha um tipo registro capaz de armazenar os dados de cada entrevistado, 
leia e armazene os dados de 120 entrevistados em um vetor e escreva uma função 
para cada um dos itens abaixo:
a) Calcule e retorne a média salarial dos entrevistados;
b) Ache e imprima o sexo dos entrevistados com salário mais alto e mais baixo;
c) Calcule e retorne a quantidade de pessoas com menos de 30 anos, mais de 5 
filhos e salário menor que R$ 1.000,00;
d) Calcule e retorne a porcentagem de pessoas do sexo feminino que possuem 
filhos que responderam a pesquisa.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int idade;
    char sexo;
    int filhos;
    float salario;
} Pessoa;

void leitura(Pessoa *, int);
float media_salarial(Pessoa *, int);
void salarios_extremos(Pessoa *, int);
int quantidade_de_pessoas(Pessoa *, int );
float porcentagem(Pessoa *, int);

void main(){
    int num, quantidade;
    float media, porc;
    printf("\nNumero de entrevistados: "); scanf("%d", &num);
    Pessoa *entrevistados = (Pessoa *) malloc(num * sizeof(Pessoa));
    leitura(entrevistados, num);
    media = media_salarial(entrevistados, num);
    printf("\nMedia: %f", media);
    salarios_extremos(entrevistados, num);
    quantidade=quantidade_de_pessoas(entrevistados, num);
    printf("\nQuantidade de pessoas com - 30 anos, + 5 filhos e salario -1000: %d", quantidade);
    porc=porcentagem(entrevistados, num);
    printf("\nPorcentagem de mães: %.2f%%", porc);
}

//Fazendo a leitura dos entrevistados
void leitura(Pessoa *vetor, int num){
    for (int i=0; i<num; i++){
        printf("\nIdade: "); scanf(" %d", &vetor[i].idade);
        printf("Sexo: "); scanf(" %c", &vetor[i].sexo);
        printf("Filhos: "); scanf(" %d", &vetor[i].filhos);
        printf("Salario: "); scanf(" %f", &vetor[i].salario);
    }
    printf("\nDados cadastrados!\n");
}

//a) Calcule e retorne a média salarial dos entrevistados
float media_salarial(Pessoa *vetor, int num){
    float soma=0;
    for (int i=0; i<num; i++){
        soma+=vetor[i].salario;
    }
    return (soma/num);
}

//b) Ache e imprima o sexo dos entrevistados com salário mais alto e mais baixo;
void salarios_extremos(Pessoa *vetor, int num){
    float maior=vetor[0].salario, menor=vetor[0].salario;
    char sexo_maior=vetor[0].sexo, sexo_menor=vetor[0].sexo;
    
    for (int i=0; i<num; i++){
        if (vetor[i].salario > maior){
            maior=vetor[i].salario;
            sexo_maior=vetor[i].sexo;
        }
        if (vetor[i].salario < menor){
            menor=vetor[i].salario;
            sexo_menor=vetor[i].sexo;
        }
    }
    printf("\nSexo do entrevistado com salario mais alto: %c", sexo_maior);
    printf("\nSexo do entrevistado com salario mais baixo: %c", sexo_menor);
}

//c) Calcule e retorne a quantidade de pessoas com menos de 30 anos, mais de 5 
//filhos e salário menor que R$ 1.000,00;
int quantidade_de_pessoas(Pessoa *vetor, int num){
    int quantidade = 0;
    for (int i=0; i<num; i++){
        if (vetor[i].idade < 30 && vetor[i].filhos > 5 && vetor[i].salario < 1000){
            quantidade++;
        }
    }
    return quantidade;
}

//d) Calcule e retorne a porcentagem de pessoas do sexo feminino que possuem 
//filhos que responderam a pesquisa.
float porcentagem(Pessoa *vetor, int num){
    int quantidade=0;
    for (int i=0; i<num; i++){
        if (vetor[i].sexo == 'M' && vetor[i].filhos > 0){
            quantidade++;
        }
    }
    return ((100 * quantidade)/num);
}

/*testes:
5
20
M
2
1000.0
34
H
3
2000
25
M
1
550.50
18
H
6
999.9
17
M
9
800
*/