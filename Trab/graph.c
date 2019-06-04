#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

struct _graph {
    int vertices;
    double mean_weight;
    node **list;
};

graph *graph_create(int vertices) {
    graph *g = calloc(1, sizeof(graph));
    g->list = calloc(vertices, sizeof(node *));
    g->vertices = vertices;
    return g;
}

graph *graph_from_sequence(int *seq, int len, int end) {
    int vertices = -1;
    int edge_sum = 0, edge_cnt = 0;
    for (int i = 0; i < len; i++) {
        vertices = MAX(vertices, seq[i]);
    }
    graph *g = graph_create(vertices + 1);
    for (int i = 1; i < len; i++) {
        if (seq[i - 1] == end) continue;
        graph_edge *ge = graph_edge_get(g, seq[i - 1], seq[i]);
        if (ge) {
            ge->w++;
        } else {
            graph_edge_add(g, seq[i - 1], seq[i], 1);
            edge_cnt++;
        }
        edge_sum++;
    }
    g->mean_weight = edge_sum / (double) edge_cnt;
    return g;
}

void graph_destroy(graph *g) {
    for (int i = 0; i < g->vertices; i++) {
        for (node *x = g->list[i]; x; x = list_next(x)) {
            free(list_val(x).pointer);
        }
        list_destroy(g->list[i]);
    }
    free(g->list);
    free(g);
}

void graph_edge_add(graph *g, int u, int v, int w) {
    graph_edge *ge = malloc(sizeof(graph_edge));
    *ge = (graph_edge){u, v, w};
    g->list[u] = list_insert(g->list[u], (node_val){.pointer = (void *)ge});
}

graph_edge *graph_edge_get(graph *g, int u, int v) {
    node *x = g->list[u];
    for (node *x = g->list[u]; x; x = list_next(x)) {
        graph_edge *ge = list_val(x).pointer;
        if (ge->v == v) {
            return ge;
        }
    }
    return NULL;
}

void graph_edge_remove(graph *g, int u, int v) {
    for (node *x = g->list[u]; x; x = list_next(x)) {
        graph_edge *ge = list_val(x).pointer;
        if (ge->v == v) {
            g->list[u] = list_delete(g->list[u], list_val(x));
            break;
        }
    }
}

node *graph_edge_list(graph *g, int u) {
    return g->list[u];
}

int graph_vertex_count(graph *g) {
    return g->vertices;
}

double graph_mean_weight(graph *g) {
    return g->mean_weight;
}
