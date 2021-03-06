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

double new_word_penality = 0.1;

/**
  * @brief Adds an element to the sentence sequence
*/
void add(int **seq, int *cnt, int *len, int x) {
    if (*cnt == *len) {
        *len = (*len) == 0 ? 1 : 2 * (*len);
        *seq = realloc(*seq, (*len) * sizeof(int));
    }
    (*seq)[(*cnt)++] = x;
}

double weight(graph *g, int u, int v, int freq) {
    return graph_mean_weight(g) / freq + new_word_penality;
}

/**
 * @brief d'Esopo-Pope Algorithm implementation
 */
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

 /**
  * @brief  Creates the graph from the dictionary
  * @note The graph returned needs to be deallocated
  * @param  *f: pointer to a file containing the dictionary
  * @param  *t: pointer to the trie that will receive the words from f
  * @retval pointer to a new Graph
 */
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
                int curr_word = get_id(t, word + j, 1) + FIRST_WORD_ID;
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
 /**
  * @brief  Reads the sequence of words given by the user
  * @note   Needs to be deallocated after use
  * @param  ***s: pointer to a memory location of a matrix that will contain the given words
  * @param  *total_size: pointer to memory locations of the total size of matriz, initializated with 0
  * @retval None
 */
void get_sentence(char ***s, int *total_size){
    char aux[1024];
    fgets(aux, 1024, stdin);

    *total_size = 0;
    for (int i = 0, j = 0; ; i++) {
        if (isalpha(aux[i])) {
            j++;
        } else {
            if (j > 0) {
                (*total_size)++;
            }
            j = 0;
        }
        if (aux[i] == '\0') {
            break;
        }
    }

    *s = malloc(*total_size * sizeof(char *));
    for (int i = 0, j = 0, k = 0; ; i++) {
        int end_flag = aux[i] == '\0';
        if (isalpha(aux[i])) {
            j++;
        } else {
            if (j > 0) {
                aux[i] = '\0';
                (*s)[k] = malloc(j + 1);
                strcpy((*s)[k], aux + i - j);
                k++;
            }
            j = 0;
        }
        if (end_flag) {
            break;
        }
    }
}

int main(int argc, char **argv) {
    //check for parameters
    if (argc < 2) {
        printf("Specify the dictionary file name at input: ./AutomaticSentenceGenerator <DictionaryFileName: string> <WordPenalty: double>\nThe last argument is optional\n");
        return 1;
    }
    
    //if the user specified the word penalty
    if (argc >= 3) {
        new_word_penality = atof(argv[2]);
        printf("Using word penalty as %f\n", new_word_penality);
    }

    //open dictionary
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Fail to open dicionary.\n");
        return 2;
    }

    printf("\n\t┌─┐┬ ┬┌┬┐┌─┐┌┬┐┌─┐┌┬┐┬┌─┐  ┌─┐┌─┐┌┐┌┌┬┐┌─┐┌┐┌┌─┐┌─┐  ┌─┐┌─┐┌┐┌┌─┐┬─┐┌─┐┌┬┐┌─┐┬─┐\n");
    printf(  "\t├─┤│ │ │ │ ││││├─┤ │ ││    └─┐├┤ │││ │ ├┤ ││││  ├┤   │ ┬├┤ │││├┤ ├┬┘├─┤ │ │ │├┬┘\n");
    printf(  "\t┴ ┴└─┘ ┴ └─┘┴ ┴┴ ┴ ┴ ┴└─┘  └─┘└─┘┘└┘ ┴ └─┘┘└┘└─┘└─┘  └─┘└─┘┘└┘└─┘┴└─┴ ┴ ┴ └─┘┴└─\n");

    //create graph from dictionary
    printf("\nLoading dictionary..\n");
    trie *t = create_trie();
    graph *g = load_words(f, t);
    printf("\nSuccess!\n\n");

    printf("Write a set of words wich exists on dicionary. Your sentence will be build based on that.\n");

    fclose(f);

    double *dist = malloc(graph_vertex_count(g) * sizeof(double));
    int *parent = malloc(graph_vertex_count(g) * sizeof(int));
    //principal routine
    while (1) {
        char **input = NULL;
        int cnt = 0;

        printf("Write some words -> ");
        //read input
        get_sentence(&input, &cnt);
        
        if (cnt == 0) {
            break;
        }

        node *output_head = NULL, *output_tail = NULL;

        int ok = 1;
        int u = BEGIN;
        for (int i = 0; i <= cnt; i++) {
            int v = i == cnt ? END : get_id(t, input[i], 0) + FIRST_WORD_ID; 
            if (v < 0) {
                printf("The word '%s' doesn't exists on dictionary", input[i]);
                ok = 0;
                break;
            }

            //find the shortest paths
            shortest_path(u, g, dist, parent);
            
            //no connection between words
            if (parent[v] == -1 && u != v) {
                printf("Impossible to build a sentence");
                ok = 0;
                break;
            }

            //add the words to a stack (to after read upside down the stack)
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
                deque_push_back(&output_head, &output_tail, word);
            }
        }
        
        printf("Output Sentence -> ");
        int first = 1;
        while (ok && output_head) {
            char *word = deque_pop_front(&output_head, &output_tail).pointer;
            if (!first) {
                printf(" ");
            } else {
                word[0] = toupper(word[0]);
            }
            first = 0;
            printf("%s", word);
            free(word);
        }
        printf(".\n");

        for (int i = 0; i < cnt; i++) {
            free(input[i]);
        }
        free(input);

        printf("\nWrite another set of words or press <ENTER> to quit\n");
    }

    trie_destroy(t);
    graph_destroy(g);
    free(dist);
    free(parent);
}
