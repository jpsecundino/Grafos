#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "list.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

struct _graph{
    node **list;
    int vertices;    
};

graph *graph_create(int vertices) {
    graph *g = calloc(1, sizeof(graph));
    g->list = calloc(vertices, sizeof(node *));
    g->vertices = vertices;
    return g;
}

graph *graph_from_sequence(int *seq, int len) {
    int vertices = -1;
    for (int i = 0; i < len; i++) {
        vertices = MAX(vertices, seq[i]);
    }
    graph *g = graph_create(vertices + 1);
    for (int i = 1; i < len; i++) {
        graph_edge *ge = graph_edge_get(g, seq[i - 1], seq[i]);
        if (ge) {
            ge->w++;
        } else {
            graph_edge_add(g, seq[i - 1], seq[i], 1);
        }
    }
    graph_edge_add(g, seq[len - 1], -1, 1);
    return g;
}

void graph_destroy(graph *g) {
    for(int i = 0; i < g->vertices; i++) {
        for (node *x = g->list[i]; x; x = list_next(x)) {
            free(list_val(x).pointer);
        }
        list_destroy(g->list[i]);
    }
    free(g->list);
    free(g);
}

double graph_vertex_similarity(graph *g1, graph *g2) {
    int max_vertices = MAX(g1->vertices, g2->vertices);
    int common_vertices = 0;
    int total_vertices = 0;

    for (int i = 0; i < max_vertices; i++) {
        if (i < g1->vertices && i < g2->vertices && g1->list[i] && g2->list[i]) {
            common_vertices++;
        }
        if ((i < g1->vertices && g1->list[i]) || (i < g2->vertices && g2->list[i])) {
            total_vertices++;
        }
    }

    return common_vertices / (double) total_vertices;
}

double graph_edge_similarity(graph *g1, graph *g2) {
    int max_vertices = MAX(g1->vertices, g2->vertices);
    int common_weight = 0;
    int total_weight = 0;

    int *g1_weights = malloc(max_vertices * sizeof(int));
    int *g2_weights = malloc(max_vertices * sizeof(int));
    for (int i = 0; i < max_vertices; i++) {
        memset(g1_weights, 0, max_vertices * sizeof(int));
        memset(g2_weights, 0, max_vertices * sizeof(int));
        if (i < g1->vertices) {
            for (node *x = g1->list[i]; x; x = list_next(x)) {
                graph_edge *ge = list_val(x).pointer;
                if (0 <= ge->v && ge->v < max_vertices) {
                    g1_weights[ge->v] += ge->w;
                }
            }
        }
        if (i < g2->vertices) {
            for (node *x = g2->list[i]; x; x = list_next(x)) {
                graph_edge *ge = list_val(x).pointer;
                if (0 <= ge->v && ge->v < max_vertices) {
                    g2_weights[ge->v] += ge->w;
                }
            }
        }
        for (int j = 0; j < max_vertices; j++) {
            common_weight += MIN(g1_weights[j], g2_weights[j]);
            total_weight += MAX(g1_weights[j], g2_weights[j]);
        }
    }
    return common_weight / (double) total_weight;
}

void graph_edge_add(graph *g, int u, int v, int w) {
    graph_edge *ge = malloc(sizeof(graph_edge));
    *ge = (graph_edge) {u, v, w};
    g->list[u] = list_insert(g->list[u], (node_val) {.pointer = (void*) ge});
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
        if(ge->v == v){
            g->list[u] = list_delete(g->list[u], list_val(x));
            break;
        }
    }
}

node *graph_edge_list(graph *g, int u) {
    return g->list[u];
}
