#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define ALPHA_SIZE 26

typedef struct _trie_node trie_node;
typedef struct _trie trie;

/**
retorna ponteiro para um nó rececm criado
@argumentos:
	- end_id = id correspondente ao nó (0 se ele não finaliza uma palavra, ID da palavra caso contrário)
*/
trie_node *create_node(int end_id);

/**
retorna ponteiro para uma trie
a própria trie ja conta o ID da palavra
*/
trie *create_trie();

/**
adiciona uma palavra e retorna o seu ID ou retorna o ID da palavra já existente
@argumentos:
	-word - palavra a ser adicionada
	-t - ponteiro para a trie
@return:
	id da palavra
*/
int get_id(char *word, trie *t);

/**
destroi a trie
*/
void trie_destroy(trie *t);
