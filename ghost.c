#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <unistd.h>

typedef struct _graph graph;

struct _graph {
	int n, m;
	int ghost_x, ghost_y;
};

void print_matrix(int n, int m, int x_jog, int y_jog, int x_fant, int y_fant){

	for( int i = 0; i < n; i++ ){
		for (int j = 0; j < m; ++j){
			if(i == x_jog && j == y_jog){
				printf("O	");
			}else if(i == x_fant && j == y_fant){
				printf("G	");
			}else{
				printf(".	");
			}
		}
		printf("\n");
	}

	printf("\n\n");
	//for( int i = 0; i < 100000000; i++ ){
	//	;
	//}
	struct timespec t = {(time_t) 0, (long) 3e8};
	nanosleep(&t, NULL);
}

int signal(int n) {
	return n > 0 ? 1 : n < 0 ? - 1 : 0;
}

void move(graph *g, int i, int j) {
	int d_x = g->ghost_x - i;
	int d_y = g->ghost_y - j;
	

	print_matrix(g->n, g->m, i, j, g->ghost_x, g->ghost_y);

	if (d_x == d_y && d_x == 0) {
		printf("pegou\n");
		return;
	}

	if (rand() & 1) {
		switch (rand() & 3) {
			case 0: if (g->ghost_x < g->n - 1) {
				g->ghost_x++;
				break;
			}
			case 1: if (g->ghost_x > 0) {
				g->ghost_x--;
				break;
			}
			case 2: if (g->ghost_y < g->m - 1) {
				g->ghost_y++;
				break;
			}
			case 3: if (g->ghost_y > 0) {
				g->ghost_y--;
				break;
			}
		}
	}

	if (d_x) {
		i += signal(d_x);
	} else {
		j += signal(d_y);
	}

	move(g, i, j);
}

int main() {
	srand(time(0));
	graph g = {10, 10, 5, 5};
	move(&g, 0, 0);
}