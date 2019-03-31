#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<locale.h>
#define ALPHA_SIZE 58

typedef struct _trie_node trie_node;

struct _trie_node{
	trie_node *alphabet[ALPHA_SIZE];
	int end_id;
};



typedef struct _trie{
	trie_node *root;
	int last_id;
}trie;

trie_node *create_node(int end_id){
	trie_node *tn = (trie_node *) calloc(1, sizeof(trie_node));

	for( int i = 0; i < ALPHA_SIZE; i++ ){
		tn->alphabet[i] = NULL;
	}

	tn->end_id = end_id;

	return tn;
}

int return_index(unsigned char c){

	if(( 96 < c && c < 123 )){
		return c - 97;
	}

	if(  159 < c && c < 192 )
		return c - 134;

}

trie *create_trie(){
	trie *t = (trie *) calloc(1, sizeof(trie));

	t->root = (trie_node*) calloc(1, sizeof(trie_node));

	t->last_id = 0;

	return t;
}

int get_id(unsigned char *word, trie *t){
	int word_size = strlen(word);

	int id = 0;

	trie_node *n = t->root;						//no atual
	for( int i = 0; i < word_size; i++ ){
		int pos = 0;
		
		if(word[i] == 195){					//se o caractere for especial
			pos = return_index(word[i+1]);
			i +=1;
		}
		else{
			pos = return_index(word[i]);
		}

		if(n->alphabet[pos] == NULL){				//se o caractere ainda não existe na trie
			n->alphabet[pos] = create_node(0);
		}

		if(i == word_size -1 && n->alphabet[pos]->end_id == 0)	//if its the last caracter of the word and no word ends here
			n->alphabet[pos]->end_id = ++(t->last_id); 	//atualiza o end_id

		id = n->alphabet[pos]->end_id;


		n = n->alphabet[pos];

	}

	return id;
}

void node_destroy(trie_node *tn){

	for( int i = 0; i < ALPHA_SIZE; i++  ){
		if(tn->alphabet)
			node_destroy(tn->alphabet[i]);
	}

	free(tn);
}

void trie_destroy(trie *t){
	
	node_destroy(t->root);

	free(t);

}