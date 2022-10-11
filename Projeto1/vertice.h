#ifndef VERTICE_H
#define VERTICE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct vertice_ VERTICE;

VERTICE *vertice_criar(int prox_cidade, int peso);
bool vertice_apagar(VERTICE **vertice);
void vertice_imprimir(VERTICE *vertice);
int vertice_get_cidade(VERTICE *vertice);
int vertice_get_peso(VERTICE *vertice);
bool vertice_set_cidade(VERTICE *vertice, int cidade);
bool vertice_set_peso(VERTICE *vertice, int peso);
size_t vertice_size();

#endif
