#include <stdlib.h>
#include "avl.h"
#include "auxiliar.h"
#include <stdio.h>

typedef struct no_
{
    ITEM *item;
    struct no_ *esquerda;
    struct no_ *direita;
    int altura;
} NO;

typedef struct avl_
{
    NO *raiz;
    int altura;
} AVL;

int altura(NO *no)
{
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

int avl_tam_max(AVL *arvore)
{
    return (1 << (altura(arvore->raiz) + 1)) - 1;
}

NO *no_criar(ITEM *item)
{
    NO *no = malloc(sizeof(NO));
    verifica_alocacao(no);

    if (item != NULL)
    {
        no->item = item;
        no->esquerda = NULL;
        no->direita = NULL;
        no->altura = 0;
        return no;
    }

    return NULL;
}

void no_apagar(NO **no)
{   
    if(*no != NULL){
        item_apagar(&((*no)->item));
        free(*no);
        *no = NULL;
    }
}

AVL *avl_criar()
{
    AVL *avl = malloc(sizeof(AVL));
    verifica_alocacao(avl);
    avl->raiz = NULL;
    avl->altura = -1;

    return avl;
}

void apagar_recursiva(NO *raiz)
{
    if (raiz == NULL)
        return;
    if (raiz->esquerda != NULL)
        apagar_recursiva(raiz->esquerda);
    if (raiz->direita != NULL)
        apagar_recursiva(raiz->direita);

    no_apagar(&raiz);
}

void avl_apagar(AVL **avl)
{
    if (*avl != NULL){
        apagar_recursiva((*avl)->raiz);
        free(*avl); (*avl) = NULL;
    }
}

NO *rotacao_direita(NO *desbalanceado)
{
    NO *futura_raiz = desbalanceado->esquerda;
    NO *arvore_t2 = futura_raiz->direita;

    futura_raiz->direita = desbalanceado;
    desbalanceado->esquerda = arvore_t2;

    desbalanceado->altura = max(altura(desbalanceado->esquerda), altura(desbalanceado->direita)) + 1;
    futura_raiz->altura = max(altura(futura_raiz->esquerda), altura(futura_raiz->direita) + 1);

    return futura_raiz;
}

NO *rotacao_esquerda(NO *desbalanceado)
{
    NO *futura_raiz = desbalanceado->direita;
    NO *arvore_t2 = futura_raiz->esquerda;

    futura_raiz->esquerda = desbalanceado;
    desbalanceado->direita = arvore_t2;

    desbalanceado->altura = max(altura(desbalanceado->esquerda), altura(desbalanceado->direita)) + 1;
    futura_raiz->altura = max(altura(futura_raiz->esquerda), altura(futura_raiz->direita)) + 1;
    // futura_raiz->altura = max(futura_raiz->esquerda->altura, futura_raiz->altura) + 1;

    return futura_raiz;
}

NO *rotacao_direita_esquerda(NO *desbalanceado)
{
    desbalanceado->direita = rotacao_direita(desbalanceado->direita);
    return (rotacao_esquerda(desbalanceado));
}

NO *rotacao_esquerda_direita(NO *desbalanceado)
{
    desbalanceado->esquerda = rotacao_esquerda(desbalanceado->esquerda);
    return (rotacao_direita(desbalanceado));
}

NO *inserir_recursiva(NO *raiz, ITEM *item)
{
    if (raiz == NULL) // inserir na raíz
        raiz = no_criar(item);
    else if (item_comparar(item, raiz->item) < 0) // propagar recursão pela esquerda
        raiz->esquerda = inserir_recursiva(raiz->esquerda, item);
    else if (item_comparar(item, raiz->item) > 0) // propagar recursão pela direita
        raiz->direita = inserir_recursiva(raiz->direita, item);

    // volta da recursão

    // calcular altura
    raiz->altura = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;
    // calcular fator de balanceamento
    int fator_balanceamento = altura(raiz->esquerda) - altura(raiz->direita);

    if (fator_balanceamento == -2) // desbalanceada para direita
    {
        if (item_comparar(item, raiz->direita->item) > 0) // item foi inserido a direita do filho direito
            raiz = rotacao_esquerda(raiz);
        else
            raiz = rotacao_direita_esquerda(raiz);
    }

    if (fator_balanceamento == 2) // desbalanceada para esquerda
    {
        if (item_comparar(item, raiz->esquerda->item) < 0) // item foi inserido a esquerda do filho esquerdo
            raiz = rotacao_direita(raiz);
        else
            raiz = rotacao_esquerda_direita(raiz);
    }

    return raiz;
}

void avl_inserir(AVL *avl, ITEM *item)
{
    if (avl != NULL && item != NULL){
        avl->raiz = inserir_recursiva(avl->raiz, item);
    }
}

void troca_max_esquerda(NO *troca, NO *raiz, NO *anterior)
{
    if (troca->direita != NULL)
    {
        troca_max_esquerda(troca->direita, raiz, troca);
        return;
    }
    if (raiz == anterior)
        anterior->esquerda = troca->esquerda;
    else
        anterior->direita = troca->esquerda;

    raiz->item = troca->item;
    free(troca);
    troca = NULL;
}

NO *remover_recursiva(NO *raiz, ITEM *item)
{
    if (raiz == NULL) // não foi achado o item a ser removido
        return raiz;

    if (item_comparar(item, raiz->item) == 0) // o item a ser removido é a raiz
    {
        if (raiz->esquerda == NULL || raiz->direita == NULL) // há um filho ou nenhum
        {
            NO *apagar = raiz;

            // removendo a referência do no da árvore
            if (raiz->esquerda == NULL) // filho esquerdo não existe
                raiz = raiz->direita;
            else // filho direito não existe
                raiz = raiz->esquerda;

            // liberando a memória do nó
            no_apagar(&apagar);
        }
        else // há ambos os filhos
            troca_max_esquerda(raiz->esquerda, raiz, raiz);
    }
    else // o item a ser removido não é a raíz, deve propagar a recursão
    {
        if (item_comparar(item, raiz->item) < 0)
            remover_recursiva(raiz->esquerda, item);
        else
            remover_recursiva(raiz->direita, item);
    }

    // volta da recursão

    // calcular altura
    raiz->altura = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;
    // calcular fator de balanceamento
    int fator_balanceamento = raiz->esquerda->altura - raiz->direita->altura;

    if (fator_balanceamento == -2) // desbalanceada para direita
    {
        if (altura(raiz->direita->esquerda) - altura(raiz->direita->direita) <= 0)
            raiz = rotacao_esquerda(raiz); // direita é mais alta
        else 
            raiz = rotacao_direita_esquerda(raiz); // esquerda é mais alta
    }

    if (fator_balanceamento == 2) // desbalanceada para esquerda
    {
        if (altura(raiz->esquerda->esquerda) - altura(raiz->esquerda->direita) >= 0)
            raiz = rotacao_esquerda(raiz); // esquerda é mais alta
        else 
            raiz = rotacao_direita_esquerda(raiz); // direita é mais alta
    }

    return raiz;
}

void avl_remover(AVL *avl, ITEM *item)
{
    if (avl != NULL && item != NULL)
        remover_recursiva(avl->raiz, item);
}

void imprimir_recursiva(NO *no)
{
    if (no == NULL){
        return;
    }
        
    imprimir_recursiva(no->esquerda);
    item_imprimir(no->item);
    imprimir_recursiva(no->direita);
}

void avl_imprimir(AVL *avl)
{
    if (avl != NULL){
        printf("--------\n");
        imprimir_recursiva(avl->raiz);
        printf("\n--------\n");
    }

}

int percorre_arvore(NO *atual, ITEM **array, int idx)
{
    if (atual == NULL)
    {
        return idx;
    }
    idx = percorre_arvore(atual->esquerda, array, idx);
    idx = percorre_arvore(atual->direita, array, idx);
    array[idx] = atual->item;
    return idx+1;
}

ITEM **avl_get_array(AVL *arvore)
{
    ITEM **array = malloc(sizeof(ITEM *) * (avl_tam_max(arvore) + 1));
    int tamanho_array = percorre_arvore(arvore->raiz, array, 0);
    array[tamanho_array] = NULL;
    return array;
}

bool avl_busca_recursiva(NO *raiz, int chave)
{
    if (raiz == NULL)
        return false;

    if (item_get_chave(raiz->item) == chave)
        return true;

    if (chave < item_get_chave(raiz->item))
        return avl_busca_recursiva(raiz->esquerda, chave);
    else
        return avl_busca_recursiva(raiz->direita, chave);
}

bool avl_busca(AVL *arvore, int chave)
{
    return avl_busca_recursiva(arvore->raiz, chave);
}
