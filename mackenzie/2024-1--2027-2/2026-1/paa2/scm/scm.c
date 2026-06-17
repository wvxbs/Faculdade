#include <stdio.h>
#define MAX 100

int r[MAX][MAX];

void mostrarMatrizInt(int linhas, int colunas, int matriz[linhas][colunas]) {
    for(int i = 0; i < linhas; i++) {

        for(int j = 0; j < colunas; j++) {

            printf("%2d ", matriz[i][j]);
        }

        printf("\n");
    }
}

void mostrarMatrizChar(int linhas, int colunas, char matriz[linhas][colunas]) {
    for(int i = 0; i < linhas; i++) {

        for(int j = 0; j < colunas; j++) {

            printf(" %c ", matriz[i][j]);
        }

        printf("\n");
    }
}

int scm_bottom_up(int x[], int y[], int m, int n, int c[m + 1][n + 1], char b[m + 1][n + 1]) {
    for(int i = 0; i <= n; i++) c[i][0] = 0;
    for(int j = 0; j <= n; j++) c[0][j] = 0;

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if(x[i - 1] == y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = '-';
            }
            else {
                if(c[i][j - 1] > c[i - 1][j]) {
                    c[i][j] = c[i][j - 1];
                    b[i][j] = '<';
                }
                else {
                    c[i][j] = c[i][j - 1];
                    b[i][j] = '^';;
                }
            }
        }
    }

    return c[m][n];
}

int scm_top_down(int x[], int y[], int m, int n) {
    if(m == 0 || n == 0) return 0;

    if(r[m][n] != -1) return r[m][n];

    if(x[m] == y[n]) {
        r[m][n] = 1 + scm_top_down(x, y, m, n);
    }+
    else {
        if(c[m][n - 1] > c[m - 1][n]) {
            c[m][n] = c[m][n - 1];
        }
        else {
            c[m][n] = c[m][n - 1];
        }
    }

    scm_top_down(x, y, m - 1, n, c);
}

int main() {

    int x[] = {1, 2, 3, 4, 1};
    int y[] = {3, 4, 1, 2, 1, 3};

    int m = 5;
    int n = 6;

    int c[m + 1][n + 1];
    char b[m + 1][n + 1];

    int bottom_up = scm_bottom_up(x, y, m, n, c, b);
    int top_down = scm_top_down(x, y, m, n);

    printf("Tamanho da scm_bottom_up: %d\n\n", bottom_up);

    printf("Matriz C:\n");
    mostrarMatrizInt(m + 1, n + 1, c);

    printf("\nMatriz B:\n");
    mostrarMatrizChar(m + 1, n + 1, b);

    return 0;
}