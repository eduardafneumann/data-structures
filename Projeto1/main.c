#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "alocacao.h"
#include "lista.h"
#include "grafo.h"
#include "pilha.h"
#include "solucao.h"

typedef struct info_{
    GRAFO *grafo;
    int cidade_origem;
    bool *visitados;
    SOLUCAO *melhor_solucao;
    PILHA *caminho_atual;
} INFO;

void solve(INFO *info, int cidade, int dist)
{
    LISTA *vizinhanca = grafo_get_lista(info->grafo, cidade);
    VERTICE *proxima_cidade;
    int peso_estrada, vizinha;

    for (int i = 0; i < lista_tamanho(vizinhanca); i++)
    {
        proxima_cidade = lista_get_vertice(vizinhanca, i);
        peso_estrada = vertice_get_peso(proxima_cidade);
        vizinha = vertice_get_cidade(proxima_cidade);

        if (vizinha == info->cidade_origem)
        {
            // é um caminho valido
            if (pilha_tamanho(info->caminho_atual) == grafo_tamanho(info->grafo))
            {
                dist += peso_estrada;
                // é menor que o menor ja achado
                if (dist < solucao_get_dist(info->melhor_solucao))
                {
                    solucao_armazena(info->melhor_solucao, info->caminho_atual, dist);
                }
            }
        }
        else
        {
            if (!info->visitados[vizinha])
            {
                pilha_inserir(info->caminho_atual, item_criar(vizinha));
                info->visitados[vizinha] = true;

                solve(info, vizinha, dist + peso_estrada);

                info->visitados[vizinha] = false;
                pilha_remover(info->caminho_atual);
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

INFO *info_gerar(){
    // lendo input
    int n_cidades;
    scanf("%d", &n_cidades);
    int cidade_origem;
    scanf("%d", &cidade_origem);
    cidade_origem--;

    // criando o grafo, melhor solução, vetor de visitados e pilha do caminho
    GRAFO *grafo = grafo_criar(n_cidades);
    
    SOLUCAO *melhor_solucao = solucao_criar(n_cidades);
    bool *visitados = malloc(sizeof(bool)*n_cidades); verifica_alocacao(visitados);
    PILHA *caminho_atual = pilha_criar(n_cidades);
    pilha_inserir(caminho_atual, item_criar(cidade_origem));

    // lendo resto do input
    ler_grafo(grafo);

    // alocando e inicializando a info
    INFO *info = malloc(sizeof(INFO*));
    info->grafo = grafo; info->cidade_origem = cidade_origem; info->visitados = visitados; info->melhor_solucao = melhor_solucao; info->caminho_atual = caminho_atual;
    return info;
    grafo_tamanho(info->grafo);
}

void info_desalocar(INFO *info){
    grafo_apagar(info->grafo);
    free(info->visitados);
    solucao_apagar(info->melhor_solucao);
    pilha_apagar(info->caminho_atual);
    free(info);
}

int main()
{
    // criando info
    INFO *info = info_gerar();
    grafo_tamanho(info->grafo);

    // resolvendo
    solve(info, info->cidade_origem, 0);

    // imprimindo a solução
    //pilha_imprimir(solucao_get_cidades(info->melhor_solucao));
    //if(pilha_vazia(solucao_get_cidades(info->melhor_solucao))) printf("AAAAAAA");
    //solucao_imprimir(info->melhor_solucao, info->cidade_origem);

    // desalocando a memória
    //info_desalocar(info);
    
    return 0;
}