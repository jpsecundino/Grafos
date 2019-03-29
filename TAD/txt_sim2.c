#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define fileMAX 100
#define nameMAX 20
#define tagMAX 15

int main(int argc, char const *argv[])
{
	char tag_list[tagMAX][3] = {"ADJ", "ADV", "CN", "GER", "PPT", "PPA", "IND", 
								"INF", "MTH", "V", "WD", "STT", "QNT", "PRS", "PNM"};

	FILE *txt_1/*, *txt_2*/;
	Node *vec_txt1 = (Node*) calloc(fileMAX, sizeof(Node));
	// Node *vec_txt2 = (Node*) calloc(fileMAX, sizeof(Node));

	// Inserir nome do primeiro texto
	char file_name[nameMAX] = "1.txt";
	// scanf("%s", file_name);
	txt_1 = fopen(file_name, "r");

	// Inserir nome do segundo texto
	// char file_name[nameMAX];
	// scanf("%s", file_name);
	// txt_2 = fopen(file_name, "r");

	char buffer[512];
	while (!feof(txt_1)) {		// fazer pros dois textos
		fscanf(txt_1, "%s", buffer);
	
		int len = strlen(buffer);
		int slash_num = 0; 	// número de barras
		for (int i = 0; i < len; i++) {
			if (buffer[i] == '/') {
				slash_num++;
			}
		}
		
		int i = 0;
		int word_counter = 0;
		if (slash_num == 1) {
			// considerando buffer[i] = buffer[0] como início da palavra,
			// inserir palavra e posicao da tag no vetor de tags numa trie,
			// usando um ID pra marcar o fim dela

			// iterar até achar uma '/'
			// começar a armazenar a tag, usando sempre 3 char

		} else if (slash_num == 2) {
			while (buffer[i] != '/')
				i++;

			i++;	// primeiro char depois da '/'
			
			// inserir palavra e posicao da tag no vetor de tags numa trie,
			// usando um ID pra marcar o fim dela
		}
	}

	fclose(txt_1);
	// fclose(txt_2);
	free(buffer);

	return 0;
}