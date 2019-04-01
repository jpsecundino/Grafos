#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <unistd.h>

typedef struct _graph graph;

struct _graph {
    int n, m;
};
/*      Imprime a matriz que simboliza o grafo e o local do fantasma e do pacman
    Parametros:
        -int n : numero de linhas
        -int m : numero de colunas
        -int x_jog, y_jog : coordenadas do pacman
        -int x_fant, y_fant : coordenadas do fantasma
*/
void print_matrix(int n, int m, int x_jog, int y_jog, int x_fant, int y_fant) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == x_jog && j == y_jog) {
                printf("P	");
            } else if (i == x_fant && j == y_fant) {
                printf("G	");
            } else {
                printf(".	");
            }
        }
        printf("\n");
    }
    printf("\n\n");

    struct timespec t = {
        (time_t) 0,
        (long) 3e8
    };
    nanosleep(&t, NULL);
}
/*      Identificar o sinal do numero 
    Parametro:
        -int n : numero a ser identificado
    Retorno:
        - 1 : se o numero for positivo
        - -1: se o numero for negativo
        - 0 : se o numero for 0
*/
int signal(int n) {
    return n > 0 ? 1 : n < 0 ? -1 : 0;
}

/*      Mover o pac man e o fantasma
    Parametro:
        - graph *g : 
        - int i, j : coordenadas do pac man
        - int ghost_i, ghost_j : coordenadas do fantasma
    Sem retorno     
*/
void move(graph *g, int i, int j, int ghost_i, int ghost_j) {
    int d_x = ghost_i - i;
    int d_y = ghost_j - j;

    print_matrix(g->n, g->m, i, j, ghost_i, ghost_j);

    if (d_x == d_y && d_x == 0) {
        printf("pegou\n");
        return;
    }

    if (rand() & 1) {
        switch (rand() & 3) {
            case 0:
                if (ghost_i < g->n - 1 && ghost_i != i - 1) {
                    ghost_i++;
                    break;
                }
            case 1:
                if (ghost_i > 0 && ghost_i != i + 1) {
                    ghost_i--;
                    break;
                }
            case 2:
                if (ghost_j < g->m - 1 && ghost_j != j - 1) {
                    ghost_j++;
                    break;
                }
            case 3:
                if (ghost_j > 0 && ghost_j != j + 1) {
                    ghost_j--;
                    break;
                }
        }
    }

    if (d_x) {
        i += signal(d_x);
    } else {
        j += signal(d_y);
    }

    move(g, i, j, ghost_i, ghost_j);
}

int main() {
    srand(time(0));
    int n, m, x_player, y_player, x_ghost, y_ghost;
    // posicao inicial do pacman e do fantas a
    scanf("%d %d %d %d %d %d, ", &n, &m, &x_player, &y_player, &x_ghost, &y_ghost);
    graph g = {
        n,
        m
    };
    move(&g, x_player, y_player, x_ghost, y_ghost);
}
