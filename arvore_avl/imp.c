#include<stdio.h>
#include<stdlib.h>

//Node types
const int ROOT = 1;
const int LEFT_CHILD = 2;
const int RIGHT_CHILD = 3;

//The node structure
typedef struct node{
	char *data;
	struct node *parent;
	struct node *left;
	struct node *right;
} Node;

Node *root;

Node *createNode(int nodeType, Node *parent, char *data){
	Node *node = malloc (sizeof(Node));
	
	if (node == NULL){
		exit(EXIT_FAILURE);
	}
	
	node->parent = parent;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	
	if(nodeType == LEFT_CHILD){
		parent->left = node;
	}
	else if(nodeType == RIGHT_CHILD){
		parent->right = node;
	}
	
	return node;
}

void printTree(Node *n, int space){	
	if (n != NULL){	
		int i;	
		for(i=0; i<space; i++){
			printf(" ");
		}	
		if(n->parent == NULL)
			printf("%s \n", n->data);
		else
			printf("%s [%s] \n", n->data, n->parent->data);
			
		printTree(n->left, space + 1);
		printTree(n->right, space + 1);
	}	
}

void freeTree(Node *n){
	if (n != NULL){
		freeTree(n->left);
		freeTree(n->right);
		free(n);
	}
}

int height(Node *n){
	if(n == NULL){
		return -1;
	}else{
		int hl = height(n->left);
		int hr = height(n->right);
		
		if(hl < hr){
			return hr + 1;
		} else{
			return hl + 1;
		}
	}
} 

void leftRotation(Node **node){ 
	Node *aux;	
	aux = (*node)->right;
	
	(*node)->right = aux->left; 
	if(aux->left != NULL)
		aux->left->parent = (*node); // Atualiza pai  		
	aux->left = (*node);
	aux->parent = (*node)->parent;	 // Atualiza pai
	(*node)->parent = aux;  // Atualiza pai 
	(*node) = aux;
}

void rightRotation(Node **node){
	Node *aux;	
	aux = (*node)->left;		
	(*node)->left = aux->right;
	if(aux->right != NULL)
		aux->right->parent = (*node); // Atualiza pai 	
	aux->right = (*node);
	aux->parent = (*node)->parent;	 // Atualiza pai
	(*node)->parent = aux;  // Atualiza pai 	
	(*node) = aux;
}

void rightAndLeftRotation(Node **node){
	rightRotation( &((*node)->right) );
 	leftRotation( node ); 
}

void leftAndRightRotation(Node **node){
	leftRotation( &((*node)->left) ); 
 	rightRotation( node ); 
}

// Retorna a difereça de altura entre as subarvores esquerda e direita
// <0 se lado esquerdo < lado direito
// =0 se forem iguais
// >0 se lado esquerdo > lado direito
int balancingFactor(Node* node){
	if(node==NULL){
		return 0;
	}
	
    return height(node->left) - height(node->right);
}

void restructureTree(Node **node){
	
	int aux_bf, bf = balancingFactor((*node));	
	
	if(bf < 0){ // Se a altura de T2 for maior que T1.
		aux_bf = balancingFactor((*node)->right);
		
		if(aux_bf <= 0){ // se a altura do lado direito de T2 for maior ou igual
			leftRotation(node); // rotação simples a esquerda
		}else{ // se a altura do lado esquerdo de T2 for maior
			rightAndLeftRotation(node); // rotação dupla direita-esquerda	
		}
	}	
	
	else if(bf>0){ // Se a altura de T1 for maior que T2	
		aux_bf = balancingFactor((*node)->left);
			
		if(aux_bf >= 0){ // se a altura do lado esquerdo de T1 for maior ou igual
			rightRotation(node); // rotação simples a direita
			
		}else{ // se a altura do lado direito de T1 for maior
			leftAndRightRotation(node); // rotação dupla esquerda-direita **
		}
	}
}

int isBalanced(Node* node){
	// Se o nó for nulo, está balanceado
	if (node == NULL){
		return 1;
	}
	// Se o nó não for nulo, verifica a subárvore esquerda e a subárvore
	// direita. Se as subárvores fores AVL então verifica o nó node.
	// Vocês podem inverter a ordem também, verificar o nó para então verificar os filhos 
	else{
		if ((!isBalanced(node->left)) || (!isBalanced(node->right))){
			return 0;			
		}
		
		int fb = balancingFactor(node);
	
		// Se a diferença entre as subárvores do 
		// nó for maior que 1, retorna falso.
		if (fb>1 || fb<-1){
			return 0;
		}
		// Senão, retorna true
		else{
			return 1;
		}
	}	
}

int strComp(void *A, void *B){
	/*	-1 indicando que o parâmetro 1 é menor que o parâmetro 2;
		0 indicando que os parâmetros são iguais;
		1 caso o primeiro seja maior que o segundo parâmetro. */
		
	return strcmp((char *)A, (char *)B);
	
	// Caso vocês estejam testando com uma árvore numérica, 
	// utilizem a função atoi para converter e comparar
	/*int numA = atoi(A), numB = atoi(B);
	if (numA < numB){ 
		return -1;
	}else if (numA > numB){ 
		return 1;
	}else{ 
		return 0
	}; */
}

int search(Node* n, void* key, int (*comp)(void *, void *)){
		
	if(n == NULL){ 
		return 0;
	}
		
	if(comp(key, n->data) < 0){
		return search(n->left, key, comp);
	
	}else if(comp(key,n->data) > 0){
		return search(n->right, key, comp);
	
	}else{
		return 1; 
	}
}

int Insert(Node** node, int nodeType, Node *parent, void* x, int (*comp)(void *, void *)){
	// Se o nó for nulo, significa que encontrou a 
	// posição correta para inserir o novo valor.
	if ( (*node) == NULL){
		// Passa como parâmetro o tipo do nó, o pai do nó e o valor
		(*node) = createNode(nodeType, parent, (char *) x);		
		// Retorna 1 informando que a inserçãofoi bem sucedida
		return 1;
	}
	// Entra no if se o valor de x for menor que o valor armazenado no nó atual
	else if (comp(x, (*node)->data) < 0){
		// Direciona a busca e inserção para a sub-árvore esquerda
		if ( Insert(&(*node)->left, LEFT_CHILD, (*node), x, comp) ){
			// Se a inserção for bem sucedida, verifica se a 
			// partir do nó atual a árvore está balanceada
			if(! isBalanced((*node)) ){	
				// Faz o balanceamento caso a árvore esteja desbalanceada
				restructureTree(node);
			}	
		}
		
	// Entra no else if se o valor de x for maior que o valor armazenado no nó atual
	}else if( comp(x, (*node)->data) > 0 ){
		// Direciona a busca e inserção para a sub-árvore direita
		if ( Insert(&(*node)->right, RIGHT_CHILD, (*node), x, comp) ){	
			// Se a inserção for bem sucedida, verifica se a 
			// partir do nó atual a árvore está balanceada		
			if(! isBalanced((*node)) ){
				// Faz o balanceamento caso a árvore esteja desbalanceada
				restructureTree(node);
			}
		}	
	}else{
		// Retorna 0 se o valor de x já 
		// estiver inserido na árvore
		return 0;
	}		
} 

int Remove(Node** node, void* x, int (*comp)(void *, void *)){
	// Se o nó atual for nulo, significa que o valor 
	// a ser removido não estava na árvore 
	if ( (*node) == NULL){
		// Retorna 0 indicando que o valor não foi removido
		return 0;
	}
	// Entra no else if se o valor de x for menor que o valor armazenado no nó atual
	else if (comp(x, (*node)->data) < 0){
		// Direciona a busca e remoção para a sub-árvore esquerda
		if ( Remove(&(*node)->left, x, comp) ){	
			// Se a remoção for bem sucedida, verifica se a 
			// partir do nó atual a árvore está balanceada	
			if(! isBalanced((*node)) ){					
				// Faz o balanceamento caso a árvore esteja desbalanceada
				restructureTree(node);
			}	
		}
	
	// Entra no else if se o valor de x for maior que o valor armazenado no nó atual
	}else if( comp(x, (*node)->data) > 0 ){ 
		// Direciona a busca e remoção para a sub-árvore direita
		if ( Remove(&(*node)->right, x, comp) ){
			// Se a remoção for bem sucedida, verifica se a 
			// partir do nó atual a árvore está balanceada			
			if(! isBalanced((*node)) ){	
				// Faz o balanceamento caso a árvore esteja desbalanceada
				restructureTree(node);
			}
		}
	
	}
	// Entra no else se o nó atual contém o valor x a ser removido
	else{ 
		// Chama a função responsável pela remoção do nó
		removeNode(node, comp);
		return 1;
	}		
}


void removeNode(Node** node, int (*comp)(void *, void *)){
	// Entra no if se o nó tiver um ou nenhum filho
	if(((*node)->left == NULL || (*node)->right == NULL)){
		Node *aux = (*node); 
		
		// Entra no if se existir filho esquerdo
		if((*node)->left != NULL)
			// Adciona no nó pai (node) 
			// o valor do filho esquerdo
	        *node = (*node)->left;
        else
			// Adciona no nó pai (node) o valor do filho direito  
			// que também pode ser nulo, caso node não tenha filho
			*node = (*node)->right;
			
		// Libera a memória utilizada no armazenamento do filho
		free(aux);
			
	}
	else { // Se o nó tiver dois filhos
		// Encontra o nó com menor elemento
		// a partir da sub-árvore direita
		Node* temp = (*node)->right;
	    Node* auxTemp = temp->left;
		// Encontra um nó para fazer a troca de 
		// valores com o nó a ser removido
	    while(auxTemp != NULL){
	        temp = auxTemp; 
	        auxTemp = auxTemp->left;
	    }
			
		// Troca o valor do nó a ser substituido pelo 
		// valor do nó temp	que tem 1 ou 0 filhos
		(*node)->data = temp->data;
			
		// Faz uma chamada à função remove para que esta remova o nó 
		// apontado por temp, pois seu valor está duplicado na árvores
		// Observe que passamos a sub-árvore direita de node pois 
		// se passarmos diretamente node, o mesmo seria removido.
		Remove(&(*node)->right, (*node)->data, comp);
		
		// Entra no if se após a remoção a árvore estiver desbalanceada
        if(! isBalanced((*node)) ){	
			// Faz o balanceamento caso a árvore esteja desbalanceada		
			restructureTree(node);
		}
	}
}

int main(void){	

	
	freeTree(root);
	return EXIT_SUCCESS;
}

