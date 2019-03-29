#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <unistd.h>

typedef struct _graph graph;

struct _graph {
    int n, m;
};

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

int signal(int n) {
    return n > 0 ? 1 : n < 0 ? -1 : 0;
}

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
    scanf("%d %d %d %d %d %d, ", &n, &m, &x_player, &y_player, &x_ghost, &y_ghost);
    graph g = {
        n,
        m
    };
    move(&g, x_player, y_player, x_ghost, y_ghost);
}