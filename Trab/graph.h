#pragma once

#include "list.h"

/* Estrutura da aresta do grafo.
    Parâmetros:
        - int u : primeiro nó
        - int v : segundo nó
        - int w : peso da aresta entre os nós
*/
typedef struct _graph graph;
typedef struct _graph_edge {
    int u, v, w;
} graph_edge;

/*      Cria um novo grafo com determinado número de vértices.
    Parâmetros:
        - int vertices : número de vértices do grafo
    Retorno:
        - novo grafo criado
*/
graph *graph_create(int vertices);

/*      Cria um novo grafo a partir de uma sequencia de elementos.
    Parâmetros:
        - int *seq  : sequência de elementos a serem transformados em grafo
        - int len   : tamanho da sequência
    Retorno:
        - novo grafo criado
*/
graph *graph_from_sequence(int *seq, int len);

/*      Destroi grafo.
    Parâmetros:
        - graph *g  : grafo a ser destruído
    Retorno:
        - novo grafo criado
*/
void graph_destroy(graph *g);

/*      Adiciona aresta a um grafo.
    Parâmetros:
        - graph *g  : grafo no qual será adicionada a aresta
        - int u     : primeiro nó
        - int v     : segundo nó
        - int w     : peso da aresta que liga os nós
*/
void graph_edge_add(graph *g, int u, int v, int w);

/*      Retorna aresta entre dois nós.
    Parâmetros:
        - graph *g  : grafo que contém a aresta desejada
        - int u     : primeiro nó
        - int v     : segundo nó
    Retorno:
        - aresta entre os nós em questão
*/
graph_edge *graph_edge_get(graph *g, int u, int v);

/*      Remove aresta a um grafo.
    Parâmetros:
        - graph *g  : grafo do qual será removida a aresta
        - int u     : primeiro nó
        - int v     : segundo nó
*/
void graph_edge_remove(graph *g, int u, int v);

/*      Retorna lista de adjacência do nó em questão
    Parâmetros:
        - graph *g  : grafo que contém o nó em questão
        - int u     : nó cuja lista de adjacência será retornada
    Retorno:
        - lista de adjacência do nó em questão
*/
node *graph_edge_list(graph *g, int u);
