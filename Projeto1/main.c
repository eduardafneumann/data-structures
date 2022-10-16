#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "alocacao.h"
#include "lista.h"
#include "grafo.h"
#include "pilha.h"

typedef struct caminho_
{
    int dist;
    PILHA *cidades;
} CAMINHO;

CAMINHO menor_caminho = {.dist = INT_MAX, .cidades = NULL};

bool *visitados = NULL;

void armazena_pilha(PILHA *visitadas, int dist)
{
    pilha_apagar(menor_caminho.cidades);
    menor_caminho.cidades = pilha_copia(visitadas);
    menor_caminho.dist = dist;
}

void solve(int cidade_origem, GRAFO *grafo, PILHA *caminho, int cidade, int dist)
{
    LISTA *vizinhanca = grafo_get_lista(grafo, cidade);
    VERTICE *proxima_cidade;
    int peso_estrada, vizinha;

    for (int i = 0; i < lista_tamanho(vizinhanca); i++)
    {
        proxima_cidade = lista_get_vertice(vizinhanca, i);
        peso_estrada = vertice_get_peso(proxima_cidade);
        vizinha = vertice_get_cidade(proxima_cidade);

        if (vizinha == cidade_origem)
        {
            // é um caminho valido
            if (pilha_tamanho(caminho) == grafo_tamanho(grafo))
            {
                dist += peso_estrada;
                // é menor que o menor ja achado
                if (dist < menor_caminho.dist)
                {
                    armazena_pilha(caminho, dist);
                }
            }
        }
        else
        {
            if (!visitados[vizinha])
            {
                pilha_inserir(caminho, item_criar(vizinha));
                visitados[vizinha] = true;

                solve(cidade_origem, grafo, caminho, vizinha, dist + peso_estrada);

                visitados[vizinha] = false;
                pilha_remover(caminho);
            }
        }
        proxima_cidade = NULL;
    }
    vizinhanca = NULL;
}

void ler_grafo(GRAFO *grafo)
{
    int vertice1, vertice2, peso;
    while (scanf("%d", &vertice1) != EOF)
    {
        scanf("%d %d", &vertice2, &peso);
        vertice1--;
        vertice2--;
        grafo_inserir(grafo, vertice1, vertice2, peso);
        grafo_inserir(grafo, vertice2, vertice1, peso);
    }
}

void imprimir_resposta(int cidade_origem)
{
    pilha_imprimir(menor_caminho.cidades);
    printf("%d\n", cidade_origem + 1);
}

int main()
{
    clock_t inicio, fim;
    inicio = clock();

    int n_cidades;
    scanf("%d", &n_cidades);

    int cidade_origem;
    scanf("%d", &cidade_origem);
    cidade_origem--;

    GRAFO *grafo = grafo_criar(n_cidades);
    ler_grafo(grafo);

    menor_caminho.cidades = pilha_criar(n_cidades);
    visitados = malloc(sizeof(bool)*n_cidades); verifica_alocacao(visitados);

    PILHA *caminho = pilha_criar(n_cidades);
    pilha_inserir(caminho, item_criar(cidade_origem));

    solve(cidade_origem, grafo, caminho, cidade_origem, 0);

    imprimir_resposta(cidade_origem);

    // desalocando a memória
    grafo_apagar(grafo);
    pilha_apagar(caminho);
    pilha_apagar(menor_caminho.cidades);

    fim = clock();
    printf("%lf\n", (double)(fim-inicio)/CLOCKS_PER_SEC); 
    return 0;
}