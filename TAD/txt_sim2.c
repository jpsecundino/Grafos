#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "graph.h"

// #define fileMAX 100
#define nameMAX 20
#define tagMAX 15
#define SIZE_BUFFER 512
#define SIZE_TAG 20
#define WORD_MAX 1000

const double WEIGHT[] = {1, 1, 0, 2};

enum Classes{
	ADJ = 1,
	ADV,
	CN,
	GER,
	PPT,
	PPA,
	IND,
	INF,
	MTH,
	V,
	WD,
	STT,
	QNT,
	PRS,
	PNM
};


typedef struct adjacencies_array{
	int adjacencies_by_word[WORD_MAX];
	int adjacencies_by_class[WORD_MAX];
	int size;
} adj_array;

int get_class_id(char *class){
	if(!strcmp(class, "ADJ")){
		return ADJ;
	}else if(!strcmp(class, "ADV")){
		return ADV;
	}else if(!strcmp(class, "CN")){
		return CN;
	}else if(!strcmp(class, "GER")){
		return GER;
	}else if(!strcmp(class, "PPT")){
		return PPT;
	}else if(!strcmp(class, "PPA")){
		return PPA;
	}else if(!strcmp(class, "IND")){
		return IND;
	}else if(!strcmp(class, "INF")){
		return INF;
	}else if(!strcmp(class, "MTH")){
		return MTH;
	}else if(!strcmp(class, "V")){
		return V;
	}else if(!strcmp(class, "WD")){
		return WD;
	}else if(!strcmp(class, "STT")){
		return STT;
	}else if(!strcmp(class, "QNT")){
		return QNT;
	}else if(!strcmp(class, "PRS")){
		return PRS;
	}else if(!strcmp(class, "PNM")){
		return PNM;
	}else{
		return -1;
	}
}

int isAceptedCharacter(char c){

	return  ((64 < c && c < 91) || ( 96 < c && c < 123)) ? 1 : 0;
}

void replaceChar(char *str, char replaced, char by){
	
	int str_sz = strlen(str);
	
	for(int i = 0; i < str_sz; i++){
		if(str[i] == replaced){
			str[i] = by;
		}
	}

}

void *to_lower_case(unsigned char *word){
	int word_size = strlen(word);
	
	for (int i = 0; i < word_size; i++){
		if((64 < word[i] && word[i] < 91)){
			word[i]+=32;
		}
		else if( word[i] == 195){
			if( 127 < word[i+1] && word[i+1] < 160  ){
				word[i+1]+=32;	
			}
		}
	}
}

int slash_counter(char *s){
	int slash_num = 0;
	int s_sz = strlen(s);
	
	for (int i = 0; i < s_sz; i++) {
		if (s[i] == '/') {
			slash_num++;
		}
	}
	
	return slash_num;
}

int str_contains(char *str, char this){
	int str_sz = strlen(str);
	for( int i = 0; i < str_sz; i++  ){
		if(str[i] == this)
			return i;
	}
	return -1;
}

void clear_inconvenient_chars(char *str){

	replaceChar(str, '*', ' ');
	replaceChar(str, '/', ' ');
	replaceChar(str, '#', ' ');

	int str_sz = strlen(str);
	for(int i = 0; i < str_sz; i++){
		if(str[i] == '<'){
			str[i] = ' ';
			str[i+1] = ' ';
			str[i+2] = ' ';
			i+=2;
			
			if(str[i+1] == '>'){
				str[i+1] = ' ';
				i += 1;
			}

		}
	}

}

int has_ignored_symbols(char *str){
	return (str[1] != '*' && str[0] != '<' && str[0] != '.' && str[0] != ',' && str[0] != ';' && str[0] != '!' && str[0] != '?') ? 0 : 1;
}

int is_valid_class(char tags[tagMAX][SIZE_TAG], char *class){
	for( int i = 0; i < tagMAX; i++  ){
		if(strcmp(class, tags[i]) == 0)
			return 1;
	}

	return 0;
}

adj_array *file_pasing( char *file_name, unsigned char word_classes[WORD_MAX][nameMAX], trie *t ){
	unsigned char buffer[SIZE_BUFFER];
	unsigned char word[nameMAX];
	unsigned char class[nameMAX];
	unsigned char inconvenient;
	
	char tag_list[tagMAX][SIZE_TAG] = {"ADJ", "ADV", "CN", "GER", "PPT", "PPA", "IND", 
								"INF", "MTH", "V", "WD", "STT", "QNT", "PRS", "PNM"};

	
	FILE *txt_1;
	txt_1 = fopen(file_name, "r");

	adj_array *seq = (adj_array *) calloc(1,sizeof(adj_array));
	int seq_it = 0;

	while (!feof(txt_1)) {// fazer pros dois textos
		fscanf(txt_1, "%s", buffer);
	
		if(!has_ignored_symbols(buffer)){			//ignora os sinais de pontuacao

			int slash_num = slash_counter(buffer);		// conta o número de barras

			clear_inconvenient_chars(buffer);		//limpa os caracteres indiferentes da string

			// printf("%s\n", buffer);			//ative se quiser ver o buffer formatado

			int word_id = 0;
			if(slash_num == 1) {
				sscanf(buffer, "%s %s %*s", word, class);
			} else if (slash_num == 2) {
				sscanf(buffer, "%*s %s %s %*s", word, class);
				if((inconvenient = str_contains(word, ',')) != -1){
					word[inconvenient] = '\0';
				}
			}
			
			to_lower_case(word); 				//coloca a string em letras minusculas

			if(is_valid_class(tag_list, class) && isAceptedCharacter(word[0])){		//adiciona palavra na trie se ela eh de uma das classes aceitaveis
				word_id = get_id(word, t);
				seq->adjacencies_by_word[seq_it] = word_id;
				seq->adjacencies_by_class[seq_it] = get_class_id(class);
				seq_it++;
				(seq->size)++;
				
				// strcpy(word_classes[word_id], class);
				// printf("{%s, %s, %d} -> ", word, class, get_id(word, t));
				// if( !strcmp(word_classes[word_id], class) && get_id(word, t) == word_id )
				// 	printf("Sucesso.\n"); 		//debugger para saber se a palavra foi inserida corretamente na trie e no vetor de classes
			}					

		}
	}
	
	fclose(txt_1);

	return seq;
}

int main(int argc, char const *argv[]){

	trie *t = create_trie();
	unsigned char word_classes[WORD_MAX][nameMAX] = {};
	char file_name[nameMAX] = {};
	
	printf("Digite o nome do primeiro arquivo\n");
	scanf("%s", file_name);

	adj_array *seq1 = file_pasing(file_name, word_classes, t);
	adj_array *seq2 = file_pasing(file_name, word_classes, t);

	printf("Digite o nome do segundo arquivo\n");
	scanf("%s", file_name);

	for (int i = 0; i < seq1->size; ++i)
	{
		printf("%d ", seq1->adjacencies_by_class[i]);
	}

	printf("\n");
	for (int i = 0; i < seq1->size; ++i)
	{
		printf("%d ", seq2->adjacencies_by_class[i]);
	}

	printf("\n");


	graph *g1_word = graph_from_sequence(seq1->adjacencies_by_word, seq1->size);
	graph *g2_word = graph_from_sequence(seq2->adjacencies_by_word, seq2->size);
	
	graph *g1_class = graph_from_sequence(seq1->adjacencies_by_class, seq1->size);
	graph *g2_class = graph_from_sequence(seq2->adjacencies_by_class, seq2->size);

	printf("\n");
	double 	s1 = graph_vertex_similarity(g1_word,g2_word),
			s2 = graph_edge_similarity(g1_word,g2_word),
			s3 = graph_vertex_similarity(g1_class,g2_class),
			s4 = graph_edge_similarity(g1_class,g2_class);
	double s = (s1 * WEIGHT[0] + s2 * WEIGHT[1] + s3 * WEIGHT[2] + s4 * WEIGHT[3]) / (WEIGHT[0] + WEIGHT[1] + WEIGHT[2] + WEIGHT[3]);
	printf("Similaridade %.3lf%%\n", s * 100);
	printf("=======================================================================================\n");
	//comparando pelas palavras
	printf("Similaridade de palavras: %.3lf%%\n", graph_vertex_similarity(g1_word,g2_word)*100);
	printf("Similaridade de conexões entre palavras: %.3lf%%\n", graph_edge_similarity(g1_word,g2_word)*100);
	//comparando pelas classes
	printf("Similaridade de classes gramaticais: %.3lf%%\n", graph_vertex_similarity(g1_class,g2_class)*100);
	printf("Similaridade de conexões entre classes gramaticais: %.3lf%%\n", graph_edge_similarity(g1_class,g2_class)*100);
	printf("=======================================================================================\n");


	free(seq1);
	free(seq2);
	graph_destroy(g1_word);
	graph_destroy(g2_word);
	graph_destroy(g1_class);
	graph_destroy(g2_class);	
	trie_destroy(t);



	return 0;
}
