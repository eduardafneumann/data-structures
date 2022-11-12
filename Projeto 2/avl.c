#include "avl.h"
#include "alocacao.h"

typedef struct no_{
    ITEM *item;
    NO* esquerda;
    NO* direita;
    int altura;    
} NO;

typedef struct avl_{
    NO *raiz;
}AVL;

NO *no_criar(){
    NO *no = malloc(sizeof(NO)); verifica_alocacao(no);
    return no;
}

AVL *avl_criar(){
    AVL *avl = malloc(sizeof(AVL)); verifica_alocacao(avl);
    avl->raiz = no_criar();
    avl->altura = -1;
}

void apagar_recursiva(NO *raiz){
    if(no==NULL) return;
    if(no->esquerda!=NULL) apagar_recursiva(no->esquerda);
    if(no->direita!=NULL) apagar_recursiva(no->direita);
}

void avl_apagar(AVL *avl){
    if(avl!=NULL) apagar_recursiva(avl->raiz);
}

void inserir_recursiva(NO *raiz, ITEM *item){
    if(raiz==NULL) return;
    int comparacao = item_comparar(item, raiz->item);
    if(comparacao>0) inserir_recursiva(raiz->esquerda);
    else if(comparacao<0) inserir_recursiva(raiz->direita);

}

void avl_inserir(AVL *avl, ITEM *item);

void troca_max_esquerda(NO *troca, NO *raiz, NO *anterior)
{
    if(troca->direita != NULL)
    {
        troca_max_esq(troca->direita, raiz, troca);
        return;
    }
    if(raiz == anterior)
        ant->esquerda = troca->esquerda;
    else
        ant->direita = troca->esquerda;

    raiz->item = troca->item;
    free(troca); 
    troca = NULL;
}

void remover_recursiva(NO **raiz, ITEM *item){
    if(*raiz == NULL) return (false);
    NO *p;
    
    if(item_comparar(item, (*raiz)->item)==0) {
        if ((*raiz)->esquerda == NULL|| (*raiz)->direita == NULL)
        { /*há um filho ou nenhum*/
            p = *raiz;
            if((*raiz)->esquerda == NULL)
                *raiz = (*raiz)->direita;
            else
                *raiz = (*raiz)->esquerda;
            item_apagar(p->item);
            free(p);
            p = NULL;
        }
        else /*há ambos os filhos*/
            troca_max_esq((*raiz)->esquerda, (*raiz), (*raiz));
    }
    else{
        if(item_comparar(item, (*raiz)->item)==0) remover_recursiva(&(*raiz)->esq, item);
        else remover_recursiva(&(*raiz)->direita, item);
    }

    if((*raiz)->direita != NULL){
        if((*raiz)->esquerda != NULL){ // tem 2 filhos
            (*raiz)->altura = max((*raiz)->esquerda->altura, (*raiz)->direita->altura) + 1;
        } else { // tem so filho direito
            (*raiz)->altura = (*raiz)->direita->altura;
        }
    } else {
        if((*raiz)->esquerda != NULL){ // tem so filho esquerdo
            (*raiz)->altura = (*raiz)->esquerda->altura;
        } else { // nao tem filhos
            (*raiz)->altura = 0;
        }
    }    
}

bool avl_remover(AVL *avl, ITEM *item){
    if(avl!=NULL) return remover_recursiva(&(avl->raiz), item)
}

void imprimir_recursiva(NO *no){
    if(no==NULL) return;
    imprimir_recursiva(no->esquerda);
    item_imprimir(no->item);
    imprimir_recursiva(no->direita);
}

void avl_imprimir(AVL *avl){
    if(avl!=NULL) imprimir_recursiva(avl->raiz);
}

NO *rotacao_direita(NO *desbalanceado) {
    NO *futura_raiz = desbalanceado->esquerda;
    NO *arvore_t2 = futura_raiz->direita;
    
    futura_raiz->direita = desbalanceado;
    desbalanceado->esquerda = arvore_t2;
    
    desbalanceado->altura = max(desbalanceado->esquerda->altura, desbalanceado->direita->altura) + 1;
    futura_raiz->altura = max(futura_raiz->esquerda->altura, futura_raiz->direita->altura) + 1;

    return futura_raiz;
}

NO *rotacao_esquerda(NO *desbalanceado) {
    NO *futura_raiz = desbalanceado->direita;
    NO *arvore_t2 = futura_raiz->esquerda;
    
    futura_raiz->esquerda = desbalanceado;
    desbalanceado->direita = arvore_t2;
    
    desbalanceado->altura = max(desbalanceado->esquerda->altura, desbalanceado->direita->altura) + 1;
    futura_raiz->altura = max(futura_raiz->esquerda->altura, futura_raiz->direita->altura) + 1;

    return futura_raiz;
}

//    int balance = getBalance(root);
//    if (balance > 1 && getBalance(root->left) >= 0)
//        return rightRotate(root);
//    
//    if (balance > 1 && getBalance(root->left) < 0) {
//        root->left = leftRotate(root->left);
//        return rightRotate(root);
//    }
//    
//    if (balance < -1 && getBalance(root->right) <= 0)
//        return leftRotate(root);
//    
//    if (balance < -1 && getBalance(root->right) > 0) {
//        root->right = rightRotate(root->right);
//        return leftRotate(root);
//}


int percorre_arvore(NO *atual, ITEM **array, int idx){
    if(atual == NULL){
        return 0;
    }
    array[idx] = atual->item;
    idx += percorre_arvore(atual->esquerda, array, idx + 1);
    idx += percorre_arvore(atual->direita, array, idx + 1);
    return idx + 1;
}

int tam_max(AVL *arvore){
    return ( 1 << (arvore->altura + 1) ) - 1;
}

ITEM *avl_get_array(AVL *arvore){
    ITEM **array = malloc(sizeof(NO *) * (tam_max() + 1));
    int tamanho_array = percorre_arvore(arvore->raiz, array, 0);   
    array[tamanho_array]=NULL;
    
    return array;
}

bool busca_recursiva(NO* raiz, int chave){
    if(raiz == NULL) return false;

    if(item_get_chave(raiz) == chave) return true;

    if(chave < item_get_chave(raiz))
        return avl_busca_recursiva(raiz->esquerda, chave);
    else
        return avl_busca_recursiva(raiz->direita, chave);
}

bool avl_busca(AVL* arvore, int chave){
    return avl_busca_recursiva(arvore->raiz, chave);
}

