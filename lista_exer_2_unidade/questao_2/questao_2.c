/*Escreva uma função para verificar se uma árvore binária é uma árvore binária
de busca.*/

typedef struct arvore{
    int chave;
    struct arvore * dir;
    struct arvore * esq;
} arvore;

int eh_binaria(arvore * no){
    int resesq, resdir;
    if (!no){
        return 1;
    } else {
        resesq = eh_binaria(no->esq);
        resdir = eh_binaria(no->dir);
        if (!(no->esq) && !(no->dir)){ //não tiver filho
            return resesq * resdir;
        } else if (!(no->dir) && (no->esq)){ //tiver filho esquerdo
            if (no->esq->chave < no->chave){
                return resesq * resdir;
            } else {
                return 0;
            }
        } else if (!(no->esq) && (no->dir)){ //tiver filho direito
            if (no->dir->chave > no->chave){
                return resesq * resdir;
            } else {
                return 0;
            }
        } else {
            if (no->esq->chave < no->chave < no->dir->chave){ //tiver filho direito e esquerdo
                return resesq * resdir;
            } else {
                return 0;
            }
        }
    }
}
