#include <stdio.h>
#include <string.h>

#define MAX 100

int maximo(int a, int b) {
    if (a > b)
        return a;

    return b;
}

void imprime_subsequencia_comum_maxima(
    char X[],
    char Y[],
    int C[MAX][MAX],
    int n,
    int m
) {
    char scm[MAX];

    int i = n;
    int j = m;
    int indice = C[n][m];

    scm[indice] = '\0';

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            scm[indice - 1] = X[i - 1];

            i--;
            j--;
            indice--;
        } else if (C[i - 1][j] > C[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("SCM: %s\n", scm);
}

void subsequencia_comum_maxima_bottom_up(char X[], char Y[]) {
    int n = strlen(X);
    int m = strlen(Y);

    int C[MAX][MAX];

    for (int i = 0; i <= n; i++) {
        C[i][0] = 0;
    }

    for (int j = 0; j <= m; j++) {
        C[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (X[i - 1] == Y[j - 1]) {
                C[i][j] = C[i - 1][j - 1] + 1;
            } else {
                C[i][j] = maximo(C[i - 1][j], C[i][j - 1]);
            }
        }
    }

    printf("\nTamanho da SCM: %d\n", C[n][m]);

    imprime_subsequencia_comum_maxima(X, Y, C, n, m);
}

int main() {
    char X[MAX];
    char Y[MAX];

    printf("Digite X: ");
    scanf("%s", X);

    printf("Digite Y: ");
    scanf("%s", Y);

    subsequencia_comum_maxima_bottom_up(X, Y);

    return 0;
}