#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include "list.h"
#include "graph.h"
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

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        return 2;
    }
    srand(time(NULL));

    trie *t = create_trie();
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
    fclose(f);

    graph *g = graph_from_sequence(seq, cnt);

    int u = BEGIN;
    int it = 100;
    int first = 1;
    while (it--) {
        int v = -1, max_w = 0;
        for (node *x = graph_edge_list(g, u); x; x = list_next(x)) {
            graph_edge *ge = list_val(x).pointer;
            int change = ((ge->w > max_w || ge->v == END) && (rand() & 1)) || ((rand() & 3) == 0);
            if (change) {
                v = ge->v;
                max_w = ge->w;
            }
        }
        u = v;

        if (u == -1 || u == END) {
            break;
        }

        char *word = get_word(t, u - FIRST_WORD_ID);
        if (!first) {
            printf(" ");
        }
        first = 0;
        printf("%s", word);
    }
    printf(".\n");


    trie_destroy(t);
    graph_destroy(g);
    if (seq != NULL) {
        free(seq);
    }
}
