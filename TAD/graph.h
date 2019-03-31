#pragma once

#include "list.h"

typedef struct _graph graph;
typedef struct _graph_edge {
    int u, v, w;
} graph_edge;

graph *graph_create(int vertices);
graph *graph_from_sequence(int *seq, int len);
void graph_destroy(graph *g);

double graph_vertex_similarity(graph *g1, graph *g2);
double graph_edge_similarity(graph *g1, graph *g2);

void graph_edge_add(graph *g, int u, int v, int w);
graph_edge *graph_edge_get(graph *g, int u, int v);
void graph_edge_remove(graph *g, int u, int v);
node *graph_edge_list(graph *g, int u);
