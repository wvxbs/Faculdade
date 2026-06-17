#include <limits.h>
#include <stdio.h>
#include <string.h>

#define MAX_MATRIZES 100

int cadeia_matrizes_recursiva(int dimensoes[], int inicio, int fim) {
    if (inicio == fim) {
        return 0;
    }

    int melhor = INT_MAX;

    /* Testa todos os pontos onde a cadeia pode ser dividida. */
    for (int divisao = inicio; divisao < fim; divisao++) {
        int custo = cadeia_matrizes_recursiva(dimensoes, inicio, divisao) +
                    cadeia_matrizes_recursiva(dimensoes, divisao + 1, fim) +
                    dimensoes[inicio - 1] * dimensoes[divisao] * dimensoes[fim];

        if (custo < melhor) {
            melhor = custo;
        }
    }

    return melhor;
}

int cadeia_matrizes_top_down_aux(int dimensoes[], int inicio, int fim,
                                 int memo[MAX_MATRIZES + 1][MAX_MATRIZES + 1]) {
    if (inicio == fim) {
        return 0;
    }

    if (memo[inicio][fim] != -1) {
        return memo[inicio][fim];
    }

    /* Estado: menor custo para multiplicar Ai...Afim. */
    int melhor = INT_MAX;

    for (int divisao = inicio; divisao < fim; divisao++) {
        int custo = cadeia_matrizes_top_down_aux(dimensoes, inicio, divisao, memo) +
                    cadeia_matrizes_top_down_aux(dimensoes, divisao + 1, fim, memo) +
                    dimensoes[inicio - 1] * dimensoes[divisao] * dimensoes[fim];

        if (custo < melhor) {
            melhor = custo;
        }
    }

    memo[inicio][fim] = melhor;
    return melhor;
}

int cadeia_matrizes_top_down(int dimensoes[], int quantidade_matrizes) {
    int memo[MAX_MATRIZES + 1][MAX_MATRIZES + 1];
    memset(memo, -1, sizeof(memo));
    return cadeia_matrizes_top_down_aux(dimensoes, 1, quantidade_matrizes, memo);
}

int cadeia_matrizes_bottom_up(int dimensoes[], int quantidade_matrizes,
                              int divisao[MAX_MATRIZES + 1][MAX_MATRIZES + 1]) {
    int custo[MAX_MATRIZES + 1][MAX_MATRIZES + 1];

    for (int matriz = 1; matriz <= quantidade_matrizes; matriz++) {
        custo[matriz][matriz] = 0;
    }

    for (int tamanho = 2; tamanho <= quantidade_matrizes; tamanho++) {
        /* Calcula cadeias pequenas antes das cadeias maiores. */
        for (int inicio = 1; inicio <= quantidade_matrizes - tamanho + 1; inicio++) {
            int fim = inicio + tamanho - 1;
            custo[inicio][fim] = INT_MAX;

            for (int corte = inicio; corte < fim; corte++) {
                int candidato = custo[inicio][corte] +
                                custo[corte + 1][fim] +
                                dimensoes[inicio - 1] * dimensoes[corte] * dimensoes[fim];

                if (candidato < custo[inicio][fim]) {
                    custo[inicio][fim] = candidato;
                    /* Guarda onde cortar para reconstruir a parentizacao. */
                    divisao[inicio][fim] = corte;
                }
            }
        }
    }

    return custo[1][quantidade_matrizes];
}

void imprimir_parentizacao(int divisao[MAX_MATRIZES + 1][MAX_MATRIZES + 1], int inicio, int fim) {
    if (inicio == fim) {
        printf("A%d", inicio);
        return;
    }

    printf("(");
    imprimir_parentizacao(divisao, inicio, divisao[inicio][fim]);
    printf(" x ");
    imprimir_parentizacao(divisao, divisao[inicio][fim] + 1, fim);
    printf(")");
}

int main(void) {
    int quantidade_matrizes;
    int dimensoes[MAX_MATRIZES + 1];
    int divisao[MAX_MATRIZES + 1][MAX_MATRIZES + 1];

    printf("Numero de matrizes: ");
    scanf("%d", &quantidade_matrizes);

    printf("Dimensoes p0 ate pn: ");
    for (int posicao = 0; posicao <= quantidade_matrizes; posicao++) {
        scanf("%d", &dimensoes[posicao]);
    }

    printf("Recursiva: %d\n",
           cadeia_matrizes_recursiva(dimensoes, 1, quantidade_matrizes));
    printf("Top-down: %d\n",
           cadeia_matrizes_top_down(dimensoes, quantidade_matrizes));

    int custo_otimo = cadeia_matrizes_bottom_up(dimensoes, quantidade_matrizes, divisao);
    printf("Bottom-up: %d\n", custo_otimo);
    printf("Parentizacao: ");
    imprimir_parentizacao(divisao, 1, quantidade_matrizes);
    printf("\n");

    return 0;
}
