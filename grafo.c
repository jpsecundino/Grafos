#include <stdlib.h>
#include <stdio.h>

#define N 100

typedef struct _graph graph;

struct _graph {
	int cnt_edge;
	int mat[N][N];
};

graph * graph_create(){
	return calloc(1, sizeof(graph));
}

void graph_add_edge(graph * g, int u, int v, int w){
	if (g->mat[u][v] == 0) {
		g->cnt_edge++;
	}
	g->mat[u][v] = w;
	g->mat[v][u] = w;
}

void graph_remove_edge(graph * g, int u, int v){
	if (g->mat[u][v]) {
		g->cnt_edge--;
	}
	g->mat[u][v] = 0;
	g->mat[v][u] = 0;
}

int graph_get_edge(graph * g, int u, int v){
	return g->mat[u][v];
}

void graph_destroy(graph * g){
	free(g);
}

int graph_fleury_rec(graph * g, int *p, int *i, int u, int start);

int *graph_fleury(graph * g, int u) {
	int i = 1;
	int e = g->cnt_edge;
	int *path = malloc((g->cnt_edge + 1) * sizeof(int));
	path[0] = u;
	graph_fleury_rec(g, path, &i, 1, u);
	for (int j = 0; j < i; j++) {
		printf("%d ", path[j]);
	}
	puts("");
	return path;
}

int graph_fleury_rec(graph * g, int *p, int *i, int u, int start) {
	if (g->cnt_edge == 0) 
		return u == start;
	printf("%d\n", u);
	for (int v = 0; v < N; v++) {
		if (u == v || g->mat[u][v] == 0) 
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
	return 0;
}

int main() {
	graph * g = graph_create();
	graph_add_edge(g, 1, 2, 1);
	graph_add_edge(g, 1, 4, 1);
	graph_add_edge(g, 2, 4, 1);
	graph_add_edge(g, 2, 3, 1);
	graph_add_edge(g, 2, 5, 1);
	graph_add_edge(g, 3, 5, 1);
	graph_fleury(g, 1);
}
