#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graph.h"
#include "list.h"
#include "trie.h"

#define BUFFER_SIZE 128
#define BEGIN 0
#define END 1
#define FIRST_WORD_ID 2

void add(int **seq, int *cnt, int *len, int x) {
    if (*cnt == *len) {
        *len = (*len) == 0 ? 1 : 2 * (*len);
        *seq = realloc(*seq, (*len) * sizeof(int));
    }
    (*seq)[(*cnt)++] = x;
}

double weight(graph *g, int u, int v, int freq) {
    return graph_mean_weight(g) / freq + 0.1;
}

void shortest_path(int v0, graph *g, double *dist, int *parent) {
    int *set = malloc(graph_vertex_count(g) * sizeof(int));
    for (int i = 0; i < graph_vertex_count(g); i++) {
        set[i] = 2;
        dist[i] = INFINITY;
        parent[i] = -1;
    }
    dist[v0] = 0.0;
    node *head = NULL, *tail = head;
    deque_push_back(&head, &tail, (node_val){.ll = v0});
    while (head != NULL) {
        int u = deque_pop_front(&head, &tail).ll;
        set[u] = 0;
        for (node *x = graph_edge_list(g, u); x; x = list_next(x)) {
            graph_edge *ge = list_val(x).pointer;
            if (dist[ge->v] > dist[u] + weight(g, u, ge->v,ge->w)) {
                dist[ge->v] = dist[u] + weight(g, u, ge->v,ge->w);
                parent[ge->v] = u;
                if (set[ge->v] == 2) {
                    deque_push_back(&head, &tail, (node_val){.ll = ge->v});
                } else if (set[ge->v] == 0) {
                    deque_push_front(&head, &tail, (node_val){.ll = ge->v});
                }
                set[ge->v] = 1;
            }
        }
    }
    free(set);
}

graph *load_words(FILE *f, trie *t) {
    int *seq = NULL;
    int cnt = 0, cap = 0;

    char word[128];
    int last_word = BEGIN;
    while (fscanf(f, "%128s", word) == 1) {
        int len = strlen(word);
        for (int i = 0, j = 0; i <= len; i++) {
            if (!isalpha(word[i])) {
                int punct = word[i] == '.';
                word[i] = '\0';
                int curr_word = get_id(t, word + j) + FIRST_WORD_ID;
                if (curr_word != -1 + FIRST_WORD_ID) {
                    add(&seq, &cnt, &cap, last_word);
                    if (punct) {
                        add(&seq, &cnt, &cap, curr_word);
                        add(&seq, &cnt, &cap, END);
                        last_word = BEGIN;
                    } else {
                        last_word = curr_word;
                    }
                }
                j = i + 1;
            }
        }
    }
    if (last_word != BEGIN) {
        add(&seq, &cnt, &cap, last_word);
        add(&seq, &cnt, &cap, END);
    }

    graph *g = graph_from_sequence(seq, cnt, END);
    if (seq != NULL) {
        free(seq);
    }
    return g;
}

void get_sentence(char ***s, int *actual_size, int * total_size){
    int i = 0;
    char aux[128];

    while(scanf("%128s", aux) > 0){
        if(i == *total_size){
            *total_size = *total_size == 0 ? 1 : 2 * *total_size;
            *s = realloc(*s, *total_size * sizeof(char *));
        }

        (*s)[i] = malloc(sizeof(char) * 128);
        
        strcpy((*s)[i], aux);
        i++;
        if (i == 3) break;
    }
    *actual_size = i;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        return 2;
    }

    trie *t = create_trie();
    graph *g = load_words(f, t);

    fclose(f);

    double *dist = malloc(graph_vertex_count(g) * sizeof(double));
    int *parent = malloc(graph_vertex_count(g) * sizeof(int));
    char **input = NULL;
    int cnt = 0, len = 0;
    
    get_sentence(&input, &cnt, &len);

    int u = BEGIN;
    for (int i = 0; i <= cnt; i++){
        int v = i == cnt ? END : get_id(t, input[i]) + FIRST_WORD_ID; 
        if (v >= graph_vertex_count(g)) {
            printf("A palavra nao existe no dicionario\n");
            exit(0);
        }
        shortest_path(u, g, dist, parent);
        if (parent[v] == -1 && u != v) {
            printf("Nao foi possivel formar uma frase\n");
            exit(0);
        }
        printf("%d: ", i);
        u = v;
        node *stack = NULL;
        while (parent[v] != -1) {
            if(v != END) {
                stack = list_insert(stack, (node_val){.pointer=get_word(t, v - FIRST_WORD_ID)});
            }
            v = parent[v];
        }
        while (stack) {
            node_val word = list_val(stack);
            stack = list_delete(stack, word);
            printf("'%s' ", word.pointer);
            free(word.pointer);
        }
        printf("\n");
    }
    shortest_path(BEGIN, g, dist, parent);

    trie_destroy(t);
    graph_destroy(g);
    free(dist);
    free(parent);
}
