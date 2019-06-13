#pragma once

#include "list.h"

/**
 * @brief  Estrutura da aresta do grafo
 * @note   
 *      int u : primeiro nó
 *      int v : segundo nó
 *      int w : peso da aresta entre os nós
 * 
 */
typedef struct _graph graph;
typedef struct _graph_edge {
    int u, v, w;
} graph_edge;

/**
 * @brief  cria um novo grafo com determinado numero de vertices
 * @param  vertices: 
 * @retval 
 *      ponteiro do tipo graph se sucesso
 *      NULL, caso contrario
 */
graph *graph_create(int vertices);

/**
 * @brief  Cria um novo grafo a partir de uma sequencia de elementos
 * @param  *seq: sequência de elementos a serem transformados em grafo
 * @param  len: tamanho da sequencia
 * @param  end: ultimo elemento da sequencia
 * @retval 
 *         ponteiro para um grafo recem criado
 *         NULL se houver algum erro
 */
graph *graph_from_sequence(int *seq, int len, int end);

/**
 * @brief  Destroi o grafo
 * @param  *g: grafo a ser destruido
 * @retval None
 */
void graph_destroy(graph *g);

/**
 * @brief  Adiciona uma aresta ao grafo
 * @param  *g: grafo no qual será adicionada a aresta
 * @param  u: primeiro nó
 * @param  v: segundo nó
 * @param  w: peso da aresta que liga os nós
 * @retval None
 */
void graph_edge_add(graph *g, int u, int v, int w);

/*      Retorna aresta entre dois nós.
        - graph *g  : grafo que contém a aresta desejada
        - int u     : primeiro nó
        - int v     : segundo nó
    Retorno:
        - aresta entre os nós em questão
*/
/**
 * @brief  Retorna aresta entre dois nós.
 * @param  *g: grafo que contém a aresta desejada
 * @param  u: primeiro nó
 * @param  v: segundo nó
 * @retval 
 *          ponteiro para aresta entre os nos em questao
 *          NULL caso a aresta nao exista
 */
graph_edge *graph_edge_get(graph *g, int u, int v);

/**
 * @brief  Remove aresta a um grafo.
 * @note   
 * @param  *g: grafo do qual será removida a aresta
 * @param  u: primeiro nó
 * @param  v: segundo nó
 * @retval None
 */
void graph_edge_remove(graph *g, int u, int v);

/**
 * @brief  Retorna lista de adjacência do nó em questão
 * @note   
 * @param  *g: grafo que contém o nó em questão
 * @param  u: nó cuja lista de adjacência será retornada
 * @retval lista de adjacência do nó em questão
 */
node *graph_edge_list(graph *g, int u);

/**
 * @brief  Retorna o numero de vertices de um grafo
 * @param  *g: ponteiro para grafo
 * @retval numero de nos de um grafo
 */
int graph_vertex_count(graph *g);

/**
 * @brief  Retorna o peso medio das arestas de um grafo
 * @param  *g: ponteiro para o grafo em questão
 * @retval media dos pesos do grafo
 */
double graph_mean_weight(graph *g);
