#include <stdio.h>
#include <string.h>

#define MAX_TEXTO 100

int maior(int primeiro, int segundo) {
    return primeiro > segundo ? primeiro : segundo;
}

int lcs_recursiva(char texto_a[], char texto_b[], int tamanho_a, int tamanho_b) {
    if (tamanho_a == 0 || tamanho_b == 0) {
        return 0;
    }

    if (texto_a[tamanho_a - 1] == texto_b[tamanho_b - 1]) {
        /* Caracteres iguais entram na subsequencia. */
        return 1 + lcs_recursiva(texto_a, texto_b, tamanho_a - 1, tamanho_b - 1);
    }

    int remover_a = lcs_recursiva(texto_a, texto_b, tamanho_a - 1, tamanho_b);
    int remover_b = lcs_recursiva(texto_a, texto_b, tamanho_a, tamanho_b - 1);
    return maior(remover_a, remover_b);
}

int lcs_top_down_aux(char texto_a[], char texto_b[], int tamanho_a, int tamanho_b,
                     int memo[MAX_TEXTO + 1][MAX_TEXTO + 1]) {
    if (tamanho_a == 0 || tamanho_b == 0) {
        return 0;
    }

    if (memo[tamanho_a][tamanho_b] != -1) {
        return memo[tamanho_a][tamanho_b];
    }

    /* Estado: LCS dos prefixos texto_a[0..tamanho_a) e texto_b[0..tamanho_b). */
    if (texto_a[tamanho_a - 1] == texto_b[tamanho_b - 1]) {
        memo[tamanho_a][tamanho_b] =
            1 + lcs_top_down_aux(texto_a, texto_b, tamanho_a - 1, tamanho_b - 1, memo);
    } else {
        int remover_a = lcs_top_down_aux(texto_a, texto_b, tamanho_a - 1, tamanho_b, memo);
        int remover_b = lcs_top_down_aux(texto_a, texto_b, tamanho_a, tamanho_b - 1, memo);
        memo[tamanho_a][tamanho_b] = maior(remover_a, remover_b);
    }

    return memo[tamanho_a][tamanho_b];
}

int lcs_top_down(char texto_a[], char texto_b[]) {
    int memo[MAX_TEXTO + 1][MAX_TEXTO + 1];
    memset(memo, -1, sizeof(memo));
    return lcs_top_down_aux(texto_a, texto_b, strlen(texto_a), strlen(texto_b), memo);
}

int lcs_bottom_up(char texto_a[], char texto_b[], char resposta[]) {
    int tamanho_a = strlen(texto_a);
    int tamanho_b = strlen(texto_b);
    int tamanho_lcs[MAX_TEXTO + 1][MAX_TEXTO + 1];

    for (int linha = 0; linha <= tamanho_a; linha++) {
        for (int coluna = 0; coluna <= tamanho_b; coluna++) {
            /* A tabela cresce comparando prefixos das duas sequencias. */
            if (linha == 0 || coluna == 0) {
                tamanho_lcs[linha][coluna] = 0;
            } else if (texto_a[linha - 1] == texto_b[coluna - 1]) {
                tamanho_lcs[linha][coluna] = 1 + tamanho_lcs[linha - 1][coluna - 1];
            } else {
                tamanho_lcs[linha][coluna] =
                    maior(tamanho_lcs[linha - 1][coluna], tamanho_lcs[linha][coluna - 1]);
            }
        }
    }

    int linha = tamanho_a;
    int coluna = tamanho_b;
    int posicao_resposta = tamanho_lcs[tamanho_a][tamanho_b];
    resposta[posicao_resposta] = '\0';

    /* Volta pela tabela para montar uma subsequencia comum encontrada. */
    while (linha > 0 && coluna > 0) {
        if (texto_a[linha - 1] == texto_b[coluna - 1]) {
            resposta[--posicao_resposta] = texto_a[linha - 1];
            linha--;
            coluna--;
        } else if (tamanho_lcs[linha - 1][coluna] >= tamanho_lcs[linha][coluna - 1]) {
            linha--;
        } else {
            coluna--;
        }
    }

    return tamanho_lcs[tamanho_a][tamanho_b];
}

int main(void) {
    char texto_a[MAX_TEXTO + 1];
    char texto_b[MAX_TEXTO + 1];
    char resposta[MAX_TEXTO + 1];

    printf("Primeira sequencia: ");
    scanf("%100s", texto_a);

    printf("Segunda sequencia: ");
    scanf("%100s", texto_b);

    printf("Recursiva: %d\n", lcs_recursiva(texto_a, texto_b, strlen(texto_a), strlen(texto_b)));
    printf("Top-down: %d\n", lcs_top_down(texto_a, texto_b));
    printf("Bottom-up: %d\n", lcs_bottom_up(texto_a, texto_b, resposta));
    printf("Uma SCM: %s\n", resposta);

    return 0;
}
