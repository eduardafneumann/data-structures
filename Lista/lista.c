#include "lista.h"

typedef struct no_
{
    ITEM *item;
    NO *prox;
} NO;

struct lista_
{
    NO *inicio;
    NO *fim;
    int tamanho;
}

LISTA *
lista_criar()
{
    LISTA *lista = malloc(sizeof(LISTA));
    if (lista != NULL)
    {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

void apagar_recursiva(NO *no)
{
    if (no->prox != NULL)
    {
        apagar_recursiva(no->prox);
    }
    item_apagar(no->item);
    no->prox = NULL;
    free(no);
}

bool lista_apagar(LISTA **lista)
{
    if (!lista_vazia(*lista))
    {
        apagar_recursiva(lista->inicio);
        return true;
    }
    return false;
}

bool lista_inserir(LISTA *lista, ITEM *item)
{
    NO *novo = malloc(sizeof(NO));
    if (novo == NULL)
    {
        return false;
    }
    novo->item = item;
    novo->prox = NULL;

    if (!lista_vazia(lista))
    {
        lista->fim->prox = novo;
        lista->fim = novo;
        lista->tamanho++;
    }
    else
    {
        lista->inicio = novo;
        lista->fim = novo;
    }
    return true;
}

ITEM *lista_remover(LISTA *lista)
{
    ITEM *item = malloc(sizeof(ITEM));
    if (lista_vazia(lista) || item == NULL)
    {
        return false;
    }
    *item = item_get(lista->fim->item);

    NO *penultimo = lista->inicio;
    while (penultimo != lista->fim)
    {
        penultimo = penultimo->prox;
    }
    item_apagar(lista->fim->item);
    free(lista->fim);
    lista->fim = penultimo;
    lista->fim->prox = NULL;
    return true;
}

int lista_tamanho(LISTA *lista)
{
    return lista->tamanho;
}

bool lista_vazia(LISTA *lista)
{
    return lista->tamanho == 0 ? true : false;
}

void lista_imprimir(LISTA *lista)
{
    printf("Lista: \n");
    NO *atual = lista->inicio;
    for (int i = 1; i < lista->tamanho; i++)
    {
        printf("Lista:\n");
        item_imprimir(atual->item);
        atual = atual->prox;
    }
}