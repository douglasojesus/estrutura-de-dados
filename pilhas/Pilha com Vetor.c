# include <stdio.h>
# include <conio.h>
# include <stdlib.h>

#define MAX 20

typedef struct
{
	char topo;
	char elementos[MAX];
} Pilha;


int Pop (Pilha *);
int Empty (Pilha);
void Push (Pilha *, int);
void Print (Pilha);

int main()
{
	Pilha p;
	char entrada[20],resp, x;
	
	p.topo = -1;

	do
	{
		printf("\n\nEscolha uma das opcoes abaixo:\n\n");
		printf("(1) Empilha um elemento.\n");
		printf("(2) Desempilha um elemento.\n");
		printf("(3) Imprime a Pilha.\n");
		printf("(4) Verifica \"parentizacao\"\n");
		printf("(5) Sair do programa.\n");
		printf("\nOpcao: ");
		scanf("%d", &resp);

		switch(resp) 
		{
			case (1):
				printf("\n\nDigite o elemento que deseja empilhar:");
				scanf(" %c", &x);
				Push(&p, x);
				break;
				
			case (2):
				x = Pop(&p);
				if (x > 0)
					printf("\n\nO elemento %c foi desempilhado.", x);
				break;
				
			case (3):
				Print(p);
				break;
				
			case (4):
				printf("Entre com uma cadeia de caracteres contendo prenteses, colchetes e chaves: ");
				fflush(stdin);
				gets (entrada);
				break;
				
			case (5):
				printf("Fim do programa!");
				break;
			
			default :
				printf("Opcao Invalida!");
			break;
		}

		printf("\n\nPressione uma tecla para continuar...");
		getch();
		system("cls");
	}while(resp != 5);
}

int Empty(Pilha p1)
{
	return (p1.topo == -1);
}

void Push(Pilha *p1, int valor)
{
	if(p1->topo >= MAX - 1)
		printf("\nPilha CHEIA!!!\n");
	else
	{
	   p1->topo++;
	   p1->elementos[p1->topo] = valor;
	}
}

int Pop(Pilha *p1)
{
	int elemento;
	if(Empty(*p1))
	{
		printf("\nPilha VAZIA!!!\n");
		return -1;
	}
	else
	{
		elemento = p1->elementos[p1->topo];
		p1->topo--;
		return elemento;
	}
}

void Print (Pilha p)
{
	int i;
	
	
	if(p.topo == -1)
		printf("Pila vazia!");
	else
	{
		printf("Pilha: \n");
		for (i = p.topo; i >= 0; i--)
		{
			printf("%c\n", p.elementos[i]);
		}
	}
}