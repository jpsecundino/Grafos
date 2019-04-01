#include <stdlib.h>
#include <stdio.h>

#define N 100

typedef struct _graph graph;

struct _graph {
	int cnt_edge;
	int mat[N][N];
};

/*	Cria novo grafo
	Retorno:
		novo grafo
*/
graph * graph_create(){
	return calloc(1, sizeof(graph));
}

/*	Adiciona nova aresta ao grafo
	Parâmetros:
		- graph *g : grafo em questão
		- int u	   : primeiro nó
		- int v    : segundo nó 
		- int w    : peso da aresta entre os nós
*/
void graph_add_edge(graph *g, int u, int v, int w){
	if (g->mat[u][v] == 0) {
		g->cnt_edge++;
	}
	g->mat[u][v] = w;
	g->mat[v][u] = w;
}


/*	Remova uma aresta do grafo
	Parâmetros:
		- graph *g : grafo em questão
		- int u	   : primeiro nó 
		- int v    : segundo nó
*/
void graph_remove_edge(graph * g, int u, int v){
	if (g->mat[u][v]) {
		g->cnt_edge--;
	}
	g->mat[u][v] = 0;
	g->mat[v][u] = 0;
}

/*	Destroi um grafo
*/
void graph_destroy(graph * g){
	free(g);
}

/*	Procura o "pai" de um elemento.
	Parâmetros:
		- int x : elemento cujo pai será procurado
		- int *p: vetor de "pais"
	Retorno:
		Caso x possua um "pai", retorna o "pai" de x;
		Caso contrário, retorna x.
*/
int find(int x, int *p) {
    return p[x] ? p[x] = find(p[x], p) : x;
}

/*	Junta dois elementos num mesmo componente
	Parâmetros:
		- int x	: primeiro elemento
		- int y	: segundo elemento
		- int*p	: vetor de "pais"
*/
void join(int x, int y, int *p) {
    x = find(x, p);
    y = find(y, p);

    if (x == y) return;
    if (x < y) {
        p[y] = x;
    } else {
        p[x] = y;
    }
}

/*	Verifica se é possível ter um ciclo euleriano no grafo dado
	Parâmetros:
		- graph *g : grafo a ser analisado
	Retorno:
		1 se for possível;
		0 se não for possível.
*/
int is_possible(graph *g){
    int count_degree = 0;
    
    for (int i = 0; i < N; i++) {
        for( int j = 0; j < N; j++) {
            if(g->mat[i][j]) {
                count_degree++;
            }
        }
        
        if(count_degree % 2 != 0)
            return 0;
        
        count_degree = 0;
    }

    return 1;
}

/*	Verifica se a aresta entre dois nós é uma ponte
	Parâmetros:
		- graph *g : grafo que contém os elementos a serem analisados
		- int u	   : primeiro nó
		- int v    : segundo nó
	Retorno:
		1 se for ponte;
		0 se não for ponte.
*/
int graph_bridge(graph *g, int u, int v) {
    if (u > v) {
        int k = u;
        u = v;
        v = k;
    }
    int *p1 = calloc(N, sizeof(int));
    int *p2 = calloc(N, sizeof(int));

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (g->mat[i][j] == 0) continue;
            join(i, j, p1);
            if (i != u || j != v) {
                join(i, j, p2);
            }
        }
    }

    int b = 0;
    for (int i = 1; i < 6; i++) {
        if (find(i, p1) != find(i, p2)) {
            b = 1;
        }
    }

    free(p1);
    free(p2);
    return b;
}

int graph_fleury_rec(graph * g, int *p, int *i, int u, int start);

/*	Verifica, através do algoritmo de Fleury, se é possível ter um ciclo euleriano no grafo dado.
	Parâmetros:
		- graph *g : grafo a ser analisado
		- int u	   : nó inicial
	Retorno:
		Vetor de inteiros com os nós na ordem em que foram visitados
*/
int *graph_fleury(graph * g, int u) {
    if (!is_possible(g)) {
        return NULL;
    }
	int i = 1;
	int e = g->cnt_edge;
	int *path = malloc((g->cnt_edge + 1) * sizeof(int));
	path[0] = u;
    graph_fleury_rec(g, path, &i, 1, u);
    return path;
}


/*	Função recursiva auxiliar à graph_fleury().
	Parâmetros:
		- graph *g : grafo a ser analisado
		- int *p   : vetor que representa um possível ciclo euleriano
		- int *i   : índice do vetor p
		- int u    : nó atual
		- int start: nó inicial
	Retorno:
		1 se for possível fazer o ciclo euleriano;
		0 se for impossível.
*/
int graph_fleury_rec(graph * g, int *p, int *i, int u, int start) {
	if (g->cnt_edge == 0) 
		return u == start;
    for (int use_bridge = 0; use_bridge <= 1; use_bridge++) {
        for (int v = 0; v < N; v++) {
            if (u == v || g->mat[u][v] == 0)
                continue;
            if (!use_bridge && graph_bridge(g, u, v))
                continue;
            int aux = g->mat[u][v];
            graph_remove_edge(g, u, v);
            p[(*i)++] = v;
            int ok = graph_fleury_rec(g, p, i, v, start);
            graph_add_edge(g, u, v, aux);
            if (ok) 
                return 1;
            (*i)--;
        }
    }
	return 0;
}

int main() {
    graph *g = graph_create();
    int u, v;
    while (scanf("%d %d", &u, &v) == 2) {
        if (u == -1 || v == -1) break;
        graph_add_edge(g, u, v, 1);	// adiciona nós ao grafo e cria aresta entre eles
    }

    int *path = graph_fleury(g, 1);	// procura ciclo euleriano no grafo dado
    if (path) {				
	    for (int j = 0; j < g->cnt_edge + 1; j++) {
		    printf("%d ", path[j]);	// caso haja ciclo euleriano no grafo, imprime o caminho
	    }
	    printf("\n");
    } else {
        printf("Ciclo euleriano inexistente.\n");
    }
    graph_destroy(g);
}
