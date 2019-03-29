#include "list.h"

typedef struct _graph graph;
typedef struct _edge {
    int u, v, w;
} graph_edge;

graph *graph_create(int vertices);
void graph_edge_add(graph *g, int u, int v, int w);
void graph_edge_remove(graph *g, int u, int v);
node *graph_edge_list(graph *g, int u);
void graph_destroy(graph *g);