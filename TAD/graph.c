#include<stdlib.h>
#include "graph.h"
#include "list.h"
struct _graph{
	node **list;
	int vertices;	
};

graph *graph_create(int vertices){
	graph *g = calloc(1, sizeof(graph));
	g->list = calloc(vertices, sizeof(node*));
	g->vertices = vertices;
	return g;
}	

void graph_edge_add(graph *g, int u, int v, int w){
	graph_edge *ge = malloc(sizeof(graph_edge));
	*ge = (graph_edge) {u, v, w};
	g->list[u] = list_insert( g->list[u], (node_val) (void*) ge );
}

void graph_edge_remove(graph *g, int u, int v){
	node * x = g->list[u]; 
	while(x){
		graph_edge* ge= list_val(x).pointer; 
		if( ge->v == v ){
			g->list[u] = list_delete(g->list[u], list_val(x));
			break;
		}
		x = list_next(x);
	}

}

node *graph_edge_list(graph *g, int u){
	return g->list[u];
}

void graph_destroy(graph *g){
	for( int i = 0; i < g->vertices; i++  ){
		list_destroy(g->list[i]);
	}
	free(g->list);
	free(g);

}