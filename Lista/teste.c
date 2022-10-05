#include "lista.h"
#include "../Item/item.h"

int main(){
    LISTA *lista = lista_criar();
    lista_inserir(lista, item_criar(1));
    lista_inserir(lista, item_criar(2));
    lista_imprimir(lista);
    lista_remover(lista);
    lista_imprimir(lista);

    return 0;
}