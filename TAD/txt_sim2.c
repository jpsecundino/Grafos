#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

// #define fileMAX 100
#define nameMAX 20
#define tagMAX 15
#define SIZE_BUFFER 512
#define SIZE_TAG 4
#define WORD_MAX 600


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
	return (str[0] != '<' && str[0] != '.' && str[0] != ',' && str[0] != ';' && str[0] != '!' && str[0] != '?') ? 0 : 1;
}

int class_acepted(char tags[tagMAX][SIZE_TAG], char *class){
	for( int i = 0; i < tagMAX; i++  ){
		if(strcmp(class, tags[i]) == 0)
			return 1;
	}

	return 0;
}

int main(int argc, char const *argv[]){

	char tag_list[tagMAX][SIZE_TAG] = {"ADJ", "ADV", "CN", "GER", "PPT", "PPA", "IND", 
								"INF", "MTH", "V", "WD", "STT", "QNT", "PRS", "PNM"};

	FILE *txt_1/*, *txt_2*/;
	char word[nameMAX];
	char class[nameMAX];
	char inconvenient;

	// Inserir nome do primeiro texto
	char file_name[nameMAX] = "sample.txt";
	printf("Digite o nome do arquivo\n");
	scanf("%s", file_name);
	txt_1 = fopen(file_name, "r");

	char buffer[SIZE_BUFFER];
	int word_counter = 0;
	
	trie *t = create_trie();
	char word_classes[WORD_MAX][nameMAX] = {};

	while (!feof(txt_1)) {// fazer pros dois textos
		fscanf(txt_1, "%s", buffer);
	
		if(!has_ignored_symbols(buffer)){		//ignora os sinais de pontuacao

			int slash_num = slash_counter(buffer);		// conta o número de barras

			clear_inconvenient_chars(buffer);				//limpa os caracteres indiferentes da string

			// printf("%s\n", buffer);			//ative se quiser ver o buffer formatado

			int id = 0;
			if(slash_num == 1) {
				sscanf(buffer, "%s %s %*s", word, class);
			} else if (slash_num == 2) {
				sscanf(buffer, "%*s %s %s %*s", word, class);
				if((inconvenient = str_contains(word, ',')) != -1){
					word[inconvenient] = '\0';
				}
			}

			//adiciona palavra na trie se ela eh de uma das classes aceitaveis
			if(class_acepted(tag_list, class)){
					id = get_id(word, t);
					strcpy(word_classes[id], class);
					// printf("{%s, %s}\n", word, class );
					printf("%s %s %s %d%d", word, word_classes[id], class, get_id(word, t), id );
			}

			if(id)
				word_counter++;

		}
	}

	trie_destroy(t);

	fclose(txt_1);

	return 0;
}