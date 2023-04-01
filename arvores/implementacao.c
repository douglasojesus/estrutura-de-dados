# include <stdio.h>
# include <stdlib.h>
# include <conio.h>

typedef struct No{
	int chave;
	struct No* esq;
	struct No* dir;
} arvore;


void Insere (arvore ** , int);
void InOrdem (arvore *);
void PreOrdem (arvore *);
void PosOrdem (arvore *);
int Altura (arvore *);
int QtdNos (arvore *);
int somanos (arvore *);
int descendentes (arvore *);
int folhas (arvore *);
int qntd_nos(arvore *);
void Imprime (arvore *, int);
int comparacao (arvore *, arvore *);
int apenas_um_filho (arvore *);


void main()
{
	int item, opcao;
	arvore *raiz = NULL;
    arvore *raiz2 = NULL;

    //populando a arvore 2 para teste de comparação mais eficiente:
    Insere(&raiz2, 10); Insere(&raiz2, 15); Insere(&raiz2, 13);
    Insere(&raiz2, 3); Insere(&raiz2, 2); Insere(&raiz2, 8); Insere(&raiz2, 9);

	do {
			system("cls");
			printf("\nEscolha um opcao: \n");
			printf(" 1 - Insere um elemento na avore.\n");
			printf(" 2 - Imprime em InOrdem.\n");
			printf(" 3 - Imprime em PreOrdem\n");
			printf(" 4 - Imprime em PosOrdem\n");
			printf(" 5 - Imprime a arvore.\n");
			printf(" 6 - Altura da arvore.\n");
			printf(" 7 - Quantidade de nos.\n");
            printf(" 8 - Imprime a soma dos nos.\n");
            printf(" 9 - Quantidade de descendentes.\n");
            printf(" 10 - Quantidade de folhas.\n");
            printf(" 11 - Quantidade de nos da arvore.\n");
            printf(" 12 - Quantidade de nos que so tem um filho.\n");
            printf(" 13 - Compara duas arvores.\n");
			printf(" 15 - Sai do Programa.\n");
			printf("Opcao: ");
			scanf("%d", & opcao);
    
			switch(opcao)
			{
				case 1:
					printf("Digite o elemento a ser inserido na arvore: ");
					scanf("%d",&item);
					Insere(&raiz, item);
                    getch();
					break;
								  
				case 2:
					InOrdem(raiz);getch();
					break;

				case 3:
					PreOrdem(raiz);getch();
					break;
				
				case 4:
					PosOrdem(raiz);getch();
					break;
				
				case 5:
					Imprime(raiz,1);getch();
					break;
					
				case 6:
					printf("A altura da arvore eh %d.\n", Altura(raiz));getch();
					break;
					
				case 7:
					printf("A quantidade de nos da arvore eh %d.\n", QtdNos(raiz));getch();
					break;

                case 8:
                    printf("A soma dos nos da arvore eh %d.\n", somanos(raiz)); getch();

                case 9:
                    printf("A quantidade de descendentes eh %d.\n", descendentes(raiz)); getch();

                case 10:
                    printf("A quantidade de folhas eh %d.\n", folhas(raiz)); getch();
                
                case 11:
                    printf("A quantidade de nos da arvore eh %d.\n", qntd_nos(raiz)); getch();

                case 12:
                    printf("A quantidade de nos que so tem um filho eh %d.\n", apenas_um_filho(raiz)); getch();
					
                case 13:
                    printf("A arvore 2 ja tem os nos: \n");
                    Imprime(raiz2,1);
                    printf("A arvore 1 tem os nos: \n");
                    Imprime(raiz, 1);
                    if (comparacao(raiz, raiz2)){
                        printf("\nas arvores sao similares!\n");
                    } else {
                        printf("\nas arvores nao sao similares!\n");
                    }

				case 15:
					printf("\nFim do programa!!!\n");getch();
					break;

				default:  
					printf("\nOpcao invalida!\n");
					getch();
					break;
	}
	
  } while (opcao != 15);
  
  
}

void Insere (arvore **raiz, int x)
{
	arvore *p, *aux, *novo;

	novo = (arvore*) malloc(sizeof(arvore));
	novo->chave = x;
	novo->dir = NULL;
	novo->esq = NULL;

	if(*raiz == NULL)
		*raiz = novo;
	else
	{
		p = (*raiz);
		if(x >= p->chave)
			aux = p->dir;
		else
			aux = p->esq;

		while(aux!= NULL)
		{
			p = aux;
			if(x >= p->chave)
				aux = p->dir;
			else
				aux = p->esq;
		}

		if(x >= p->chave)
			p->dir= novo;
		else
			p->esq= novo;
	}
}

void Imprime(arvore * no, int l) {
	int i; 

	if (no == NULL) 
		return; 

	// Imprime a sub-árvore direita
	Imprime(no->dir, l+1); 

	// Imprime o espacamento do elemento
	for(i = 0; i < l; i++) {
		printf("      ");
	}

	printf("%d\n", no->chave); 

	// Imprime a sub-árvore esquerda
	Imprime(no->esq, l+1);
}

void InOrdem (arvore *raiz)
{
	if(raiz)
	{
		InOrdem(raiz->esq);
		printf("%d ", raiz->chave);
		InOrdem(raiz->dir);
	}
}

void PreOrdem (arvore *raiz)
{
	if(raiz)
	{
		printf("%d ", raiz->chave);
		PreOrdem(raiz->esq);
		PreOrdem(raiz->dir);
	}
}

void PosOrdem (arvore *raiz)
{
	if(raiz)
	{
		PosOrdem(raiz->esq);
		PosOrdem(raiz->dir);
		printf("%d ", raiz->chave);
	}
}

int Altura (arvore *r)
{
	int hL, hR;
	if (r == NULL)
		return -1;
	else
	{
		hL = Altura(r->esq);
		hR = Altura(r->dir);
		if (hL > hR)
			return hL + 1;
		else
			return hR + 1;
	}
}

int QtdNos (arvore * r)
{
	if (r == NULL)
		return 0;
	else
		return 1 + QtdNos(r->esq) + QtdNos(r->dir);
}

int somanos (arvore * raiz){
    int valore=0, valord=0;
    if (!raiz){
        return 0;
    } else {
        valore=somanos(raiz->esq);
        valord=somanos(raiz->dir);
        return valord + valore + raiz->chave;
    }
}

int descendentes (arvore * raiz){
    int valore=0, valord=0;
    if (!raiz){
        return -1;
    } else {
        valore = descendentes(raiz->esq);
        valord = descendentes(raiz->dir);
        return (valore+valord+2);
    }
}

int folhas (arvore * raiz){
    int valore=0, valord=0;
    if (!raiz){
        return 0;
    } else {
        valore = folhas(raiz->esq);
        valord = folhas(raiz->dir);
        if (valore+valord == 0){
            return 1;
        } else {
            return (valore + valord);
        }
    }
}

//A função recebe uma árvore binária e calcula e retorna a quantidade de
//nós internos da árvore.

int qntd_nos (arvore * raiz){
    int esquerda=0, direita=0;
    if (!raiz){
        return 0;
    } else {
        esquerda = qntd_nos (raiz->esq);
        direita = qntd_nos (raiz->dir);
        return (esquerda + direita + 1);
    }
}

//A função recebe uma árvore binária e retorna a quantidade de nós da
//árvore que possuem apenas 1 filho. Essa função deve ser recursiva.

int apenas_um_filho (arvore * raiz){
    int somae=0, somad=0;
    if (!raiz){
        return 0;
    } else {
        somae = apenas_um_filho (raiz->esq);
        somad = apenas_um_filho (raiz->dir);
        if (!(raiz->dir) && !(raiz->esq) || (raiz->dir) && (raiz->esq)){
            return (somae + somad);
        } else {
            return (somae + somad + 1);
        }
    }
}

//A função recebe uma árvore, verifica se a árvore tem mais nós na sub-
//árvore esquerda ou na sub-árvore direita.

//PENDENTE
char sub_arvore(arvore * raiz){
    int nos_esq=0, nos_dir=0;

    nos_dir = qntd_nos (raiz->dir);
    nos_esq = qntd_nos (raiz->esq);
    if (nos_esq > nos_dir){
        return 'e';
    }
}

/*A função recebe duas árvores binárias e verifica se elas são similares.
Duas árvores binárias são similares se elas são vazias ou se ambas
armazenam o mesmo valor em seu nó raiz, suas sub-árvores da esquerda
são similares e suas sub-árvores da direita também são similares.*/

//similar retorna 1 - true
//nao similar retorna 0 - true

int comparacao (arvore * raiz, arvore * raiz2){
    int valore, valord;
    if (!raiz && !raiz2){
        return 1;
    } else if (raiz && raiz2){
        valore = comparacao (raiz->esq, raiz2->esq);
        valord = comparacao (raiz->dir, raiz2->dir);
        if (raiz->chave != raiz2->chave){
            return 0;
        }
        return (valore*valord);
    } else {
        return 0;
    }
}

/*A função recebe uma árvore binária de busca e verifica se ela é
estritamente binária. Uma árvore binária de busca é estritamente binária
se todos os nós da árvore (exceto as folhas) tem 2 filhos.*/