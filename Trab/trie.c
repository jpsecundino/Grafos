#include "trie.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define K 26

typedef struct _trie_node trie_node;

struct _trie_node {
    char c;
    int id;
    int depth;
    int ending;
    trie_node *children[K];
    trie_node *parent;
};

struct _trie {
    trie_node *root;
    trie_node **id_inv;
    int node_cnt, node_cap;
};

trie *create_trie() {
    trie *t = calloc(1, sizeof(trie));

    if (t == NULL) {
        return NULL;
    }

    t->root = calloc(1, sizeof(trie_node));

    if (t->root == NULL) {
        free(t);
        return NULL;
    }

    t->root->id = -1;

    return t;
}

static void node_destroy(trie_node *tn) {
    if (tn == NULL) {
        return;
    }
    for (int i = 0; i < K; i++) {
        node_destroy(tn->children[i]);
    }
    free(tn);
}

void trie_destroy(trie *t) {
    node_destroy(t->root);
    if (t->id_inv != NULL) {
        free(t->id_inv);
    }
    free(t);
}

int get_id(trie *t, char *str, int insert) {
    trie_node *n = t->root;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
        int j = c - 'a';
        if (n->children[j] == NULL) {
            if (!insert) {
                return -100;
            }
            trie_node *p = calloc(1, sizeof(trie_node));
            n->children[j] = p;

            p->c = c;
            p->id = t->node_cnt;
            p->depth = i + 1;
            p->parent = n;

            if (t->node_cnt == t->node_cap) {
                t->node_cap = t->node_cap == 0 ? 1 : 2 * t->node_cap;
                t->id_inv = realloc(t->id_inv, t->node_cap * sizeof(trie_node *));
            }
            t->id_inv[t->node_cnt] = p;
            t->node_cnt++;
        }
        n = n->children[j];
    }
    if (n->ending == 0 && !insert) {
        return -100;
    }
    n->ending = 1;
    return n->id;
}

char *get_word(trie *t, int id) {
    trie_node *n = t->id_inv[id];
    char *str = malloc(n->depth);
    str[n->depth] = '\0';
    for (int i = n->depth - 1; i >= 0; i--) {
        str[i] = n->c;
        n = n->parent;
    }
    return str;
}
