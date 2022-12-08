#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "auxiliar.h"
#include "item.h"

typedef struct no_
{
    ITEM *item;
    struct no_ *esquerda;
    struct no_ *direita;
    int altura;
} NO;

// o conjunto é uma árvore avl
typedef struct set_
{
    NO *raiz;
} SET;

// retorna a altura do nó fornecido (útil para evitar acessos indevidos quando o nó é nulo)
int altura(NO *no)
{
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

NO *no_criar(int chave)
{
    ITEM *item = item_criar(chave);

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
    if (*no != NULL)
    {
        item_apagar(&((*no)->item));
        free(*no);
        *no = NULL;
    }
}

SET *set_criar()
{
    SET *set = malloc(sizeof(SET));
    verifica_alocacao(set);
    set->raiz = NULL;

    return set;
}

void apagar_recursiva(NO *raiz)
{
    // caso base
    if(raiz==NULL)
        return;

    // propagação da recursão
    apagar_recursiva(raiz->esquerda);
    apagar_recursiva(raiz->direita);

    // visita
    no_apagar(&raiz);
}

void set_apagar(SET **set)
{
    if (*set != NULL)
    {
        apagar_recursiva((*set)->raiz);
        free(*set);
        (*set) = NULL;
    }
}

NO *rotacao_direita(NO *desbalanceado)
{
    // o filho esquerdo do nó desbalanceado será a nova raíz da subarvore
    NO *futura_raiz = desbalanceado->esquerda;

    // o nó desbalanceado se tornará o filho direito da futura raíz, e o filho direito
    // atual da futura raíz se tornará o filho esquerdo do nó desbalanceado
    NO *arvore_t2 = futura_raiz->direita;
    futura_raiz->direita = desbalanceado;
    desbalanceado->esquerda = arvore_t2;

    // os nó desbalanceado e a nova raíz (anteriormente filho esquerdo do desbalanceado)
    // mudaram de altura, vamos recalculá-las
    desbalanceado->altura = max(altura(desbalanceado->esquerda), altura(desbalanceado->direita)) + 1;
    futura_raiz->altura = max(altura(futura_raiz->esquerda), altura(futura_raiz->direita)) + 1;

    return futura_raiz;
}

NO *rotacao_esquerda(NO *desbalanceado)
{
    // o filho direito do nó desbalanceado será a nova raíz da subarvore
    NO *futura_raiz = desbalanceado->direita;

    // o nó desbalanceado se tornará o filho esquerdo da futura raíz, e o filho esquerdo
    // atual da futura raíz se tornará o filho direito do nó desbalanceado
    NO *arvore_t2 = futura_raiz->esquerda;
    futura_raiz->esquerda = desbalanceado;
    desbalanceado->direita = arvore_t2;

    // o nó desbalanceado e a nova raíz (anteriormente filho esquerdo do desbalanceado)
    // mudaram de altura, vamos recalculá-las
    desbalanceado->altura = max(altura(desbalanceado->esquerda), altura(desbalanceado->direita)) + 1;
    futura_raiz->altura = max(altura(futura_raiz->esquerda), altura(futura_raiz->direita)) + 1;

    return futura_raiz;
}

NO *rotacao_direita_esquerda(NO *desbalanceado)
{
    // no filho direito do nó desbalanceado é realizada uma rotação direita
    desbalanceado->direita = rotacao_direita(desbalanceado->direita);

    // no nó desbalanceado é realizada uma rotação esquerda
    return (rotacao_esquerda(desbalanceado));
}

NO *rotacao_esquerda_direita(NO *desbalanceado)
{
    // no filho esquerdo do nó desbalanceado é realizada uma rotação esquerda
    desbalanceado->esquerda = rotacao_esquerda(desbalanceado->esquerda);

    // no nó desbalanceado é realizada uma rotação direita
    return (rotacao_direita(desbalanceado));
}

NO *inserir_recursiva(NO *raiz, int chave)
{
    if (raiz == NULL) // deve ser inserido na raíz
        raiz = no_criar(chave);

    else if (item_get_chave(raiz->item) > chave) // propagar recursão pela esquerda
        raiz->esquerda = inserir_recursiva(raiz->esquerda, chave);

    else if (item_get_chave(raiz->item) < chave) // propagar recursão pela direita
        raiz->direita = inserir_recursiva(raiz->direita, chave);

    // volta da recursão

    // calcular altura
    raiz->altura = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;

    // calcular fator de balanceamento
    int fator_balanceamento = altura(raiz->esquerda) - altura(raiz->direita);

    if (fator_balanceamento == -2) // desbalanceada para direita
    {
        if (item_get_chave(raiz->direita->item) < chave) // item foi inserido a direita do filho direito
            raiz = rotacao_esquerda(raiz);
        else
            raiz = rotacao_direita_esquerda(raiz);
    }

    if (fator_balanceamento == 2) // desbalanceada para esquerda
    {
        if (item_get_chave(raiz->esquerda->item) > chave) // item foi inserido a esquerda do filho esquerdo
            raiz = rotacao_direita(raiz);
        else
            raiz = rotacao_esquerda_direita(raiz);
    }

    return raiz;
}

void set_inserir(SET *set, int chave)
{
    if (set != NULL)
        set->raiz = inserir_recursiva(set->raiz, chave);
}

// troca o nó 'raiz' pelo filho máximo da subarvore esquerda
void troca_max_esquerda(NO *troca, NO *raiz, NO *anterior)
{
    if (troca->direita != NULL) // se ainda existe um nó mais a direita (chave maior)
    {
        troca_max_esquerda(troca->direita, raiz, troca);
        return;
    }

    // achou o nó mais a direita (filho máximo)

    if (raiz == anterior) // se é o filho esquerdo da raiz
        anterior->esquerda = troca->esquerda;
    else // caso contrário, será filho direito de alguém (apontado por 'anterior')
        anterior->direita = troca->esquerda;

    // subtitui o item contido no nó a ser removido ('raiz') pelo item do nó encontrado
    raiz->item = troca->item;

    // remove o item que deve ser removido
    free(troca);
    troca = NULL;
}

NO *remover_recursiva(NO *raiz, int chave)
{
    if (raiz == NULL) // não foi achado o item a ser removido
        return NULL;

    if (item_get_chave(raiz->item) == chave) // o item a ser removido é a raiz
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
        else                                                // há ambos os filhos
            troca_max_esquerda(raiz->esquerda, raiz, raiz); // procura o nó mais a direita na sub-arvore esquerda para colocar na raiz
    }
    else // o item a ser removido não é a raíz, deve propagar a recursão
    {
        if (item_get_chave(raiz->item) > chave)
            raiz->esquerda = remover_recursiva(raiz->esquerda, chave);
        else
            raiz->direita = remover_recursiva(raiz->direita, chave);
    }

    // volta da recursão

    if (raiz != NULL)
    {

        // calcular altura
        raiz->altura = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;

        // calcular fator de balanceamento
        int fator_balanceamento = altura(raiz->esquerda) - altura(raiz->direita);

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
                raiz = rotacao_direita(raiz); // esquerda é mais alta
            else
                raiz = rotacao_esquerda_direita(raiz); // direita é mais alta
        }
    }

    return raiz;
}

void set_remover(SET *set, int chave)
{
    if (set != NULL)
        set->raiz = remover_recursiva(set->raiz, chave);
}

// imprime em ordem
void imprimir_recursiva(NO *no)
{
    if (no == NULL)
        return;

    imprimir_recursiva(no->esquerda);
    item_imprimir(no->item);
    imprimir_recursiva(no->direita);
}

void set_imprimir(SET *set)
{
    if (set != NULL)
    {
        printf("----------\n");
        imprimir_recursiva(set->raiz);
        printf("\n----------\n");
    }
}

bool pertence_recursiva(NO *raiz, int chave)
{
    if (raiz == NULL) // não achou a chave na árvore
        return false;

    if (item_get_chave(raiz->item) == chave) // achou a chave
        return true;

    // propagação da recursão
    if (chave < item_get_chave(raiz->item))
        return pertence_recursiva(raiz->esquerda, chave);
    else
        return pertence_recursiva(raiz->direita, chave);
}

bool set_pertence(SET *set, int chave)
{
    return pertence_recursiva(set->raiz, chave);
}

// percorre a arvore que 'raiz' faz parte, buscando cada elemento no 'set' e se achado
// inserindo em 'interseccao'
void interseccao_recursiva(SET *set, SET *interseccao, NO *raiz)
{
    if (raiz == NULL) // caso base
        return;

    if (set_pertence(set, item_get_chave(raiz->item))) // se o item está na insterseccao
        set_inserir(interseccao, item_get_chave(raiz->item));

    // propagação da recursão
    interseccao_recursiva(set, interseccao, raiz->esquerda);
    interseccao_recursiva(set, interseccao, raiz->direita);
}

SET *set_interseccao(SET *set1, SET *set2)
{
    SET *interseccao = set_criar();

    interseccao_recursiva(set1, interseccao, set2->raiz);
    return interseccao;
}

void copiar_recursiva(SET *copia, NO *raiz)
{
    // caso base
    if (raiz == NULL) 
        return; 

    // visita (inserção)
    set_inserir(copia, item_get_chave(raiz->item));

    // propagação da recursão
    copiar_recursiva(copia, raiz->esquerda);
    copiar_recursiva(copia, raiz->direita);
}

// copia 'set' em outro set e o retorna
SET *set_copiar(SET *set)
{
    SET *copia = set_criar();
    copiar_recursiva(copia, set->raiz);
    return copia;
}

void uniao_recursiva(NO *raiz, SET *uniao)
{
    // caso base
    if (raiz == NULL)
        return;

    // visita (inserção)
    if (!set_pertence(uniao, item_get_chave(raiz->item)))
        set_inserir(uniao, item_get_chave(raiz->item));

    // propagação da recursão
    uniao_recursiva(raiz->esquerda, uniao);
    uniao_recursiva(raiz->direita, uniao);
}

SET *set_uniao(SET *set1, SET *set2)
{
    // colocamos todos os elementos do primeiro set na resposta
    SET *uniao = set_copiar(set1);

    // essa função vai adicionar na resposta os itens
    // do segundo set que não estão no primeiro set
    uniao_recursiva(set2->raiz, uniao);

    return uniao;
}
