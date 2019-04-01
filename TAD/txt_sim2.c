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

const double WEIGHT[] = {1, 1, 2};
//Lisa de classes relevantes para a comparacao
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

//struct que acumula as palavras e as suas classes
typedef struct adjacencies_array{
	int adjacencies_by_word[WORD_MAX];
	int adjacencies_by_class[WORD_MAX];
	int size;
} adj_array;

/*	Verifica qual a classe de class e retorna o ID
    Parametros:
    	- char *class: classe a ser verificada
    Retorno:
	- int: representando o Id da classe
	
*/
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
/*	Verifica se é um char valido
    Parametros:
    	- char c: char a ser vericado
    Retorno:
	- 1 : char valido
	- 0 : char invalido
	
*/
int isAceptedCharacter(char c){

	return  ((64 < c && c < 91) || ( 96 < c && c < 123)) ? 1 : 0;
}

/*	 Substitui um caracter por outro na string 
    Parametros:
    	- char *str: string 
	- char replaced:char que sera substituido 
	- char by: char que substituira
    Sem retorno
	
*/
void replaceChar(char *str, char replaced, char by){
	
	int str_sz = strlen(str);
	
	for(int i = 0; i < str_sz; i++){
		if(str[i] == replaced){
			str[i] = by;
		}
	}

}
/*	 transforma a string em minuscula 
    Parametros:
    	- unsigned char *word: string que sera transformada
    Sem retorno
	
*/
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
/*	Conta quantas barras '/' tem na string
    Parametros:
    	- char *s: string 
    Retorno:
    	- int slash_num: numero de barras
	
*/
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
/*	Verifica se a string contem o caracter 
    Parametros:
    	- char *str: string 
	- char this: caracter procurado
    Retorno:
    	- int pos: posicao do caracter
	- -1 : caracter nao encontrado	
*/
int str_contains(char *str, char this){
	int str_sz = strlen(str);
	for( int i = 0; i < str_sz; i++  ){
		if(str[i] == this)
			return i;
	}
	return -1;
}
/*	Retira da string caracteres indesejados
    Parametros:
    	- char *str: string 
    Sem retorno
    	
*/
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
/*	Verifica se a string nao contem caracteres indesejados
    Parametros:
    	- char *str: string 
    Retorno:
    	- int 1: se nao contem os caracteres
	- int 0: se contem os caracteres
    	
*/
int has_ignored_symbols(char *str){
	return (str[1] != '*' && str[0] != '<' && str[0] != '.' && str[0] != ',' && str[0] != ';' && str[0] != '!' && str[0] != '?') ? 0 : 1;
}

/*	Verifica se é uma classe valida
    Parametros:
    	- char tags: matriz que contem as tags validas
	- char *class: classe a ser verificada
    Retorno:
    	- int 1: se é valida
	- int 0: se não é valida
    	
*/
int is_valid_class(char tags[tagMAX][SIZE_TAG], char *class){
	for( int i = 0; i < tagMAX; i++  ){
		if(strcmp(class, tags[i]) == 0)
			return 1;
	}

	return 0;
}
/*	Lê o arquivo e faz o parsing
    Parametros:
    	- char *file_name: nome do arquivo
	- char word_classes[id][]: matriz que guarda, de acordo com o ID, a classe da palavra
	- trie *t: ponteiro para arvore
    Retorno:
    	- adj_array : que contem a sequencia de palavras e a sequencia de classes de acordo com id
    	
*/
adj_array *file_parsing( char *file_name, unsigned char word_classes[WORD_MAX][nameMAX], trie *t ){
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
	adj_array *seq1 = file_parsing(file_name, word_classes, t);

	printf("Digite o nome do segundo arquivo\n");
	scanf("%s", file_name);
	adj_array *seq2 = file_parsing(file_name, word_classes, t);
	
	//cria o grafo com os ids das palavras lidas nos dois textos
	graph *g1_word = graph_from_sequence(seq1->adjacencies_by_word, seq1->size);
	graph *g2_word = graph_from_sequence(seq2->adjacencies_by_word, seq2->size);
	
	//cria o grafo com os ids das classes lidas nos dois textos
	graph *g1_class = graph_from_sequence(seq1->adjacencies_by_class, seq1->size);
	graph *g2_class = graph_from_sequence(seq2->adjacencies_by_class, seq2->size);
	
	double 	sim_wordv = graph_vertex_similarity(g1_word,g2_word),//similaridade entre os vertices dos grafos
		sim_worde = graph_edge_similarity(g1_word,g2_word),//similaridade entre as arestas dos grafos
		sim_classe = graph_edge_similarity(g1_class,g2_class);//similaridade entre as classes dos grafos
	//faz uma media ponderada com as similaridades, similidares 
	double sim_mean = (sim_wordv * WEIGHT[0] + sim_worde * WEIGHT[1] + sim_classe * WEIGHT[2] ) / (WEIGHT[0] + WEIGHT[1] + WEIGHT[2]);
	
	printf("\n");
	printf("=======================================================================================\n");
	//comparando pelas palavras
	printf("Similaridade de palavras: %.3lf%%\n", sim_wordv*100);
	printf("Similaridade de conexões entre palavras: %.3lf%%\n", sim_worde*100);
	//comparando pelas classes
	printf("Similaridade de conexões entre classes gramaticais: %.3lf%%\n", sim_classe*100);
	printf("Similaridade média: %.3lf%%\n", sim_mean * 100);
	printf("=======================================================================================\n");
	printf("\n");

	free(seq1);
	free(seq2);
	graph_destroy(g1_word);
	graph_destroy(g2_word);
	graph_destroy(g1_class);
	graph_destroy(g2_class);	
	trie_destroy(t);



	return 0;
}
