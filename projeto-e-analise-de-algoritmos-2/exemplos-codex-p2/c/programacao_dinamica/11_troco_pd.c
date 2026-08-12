#include <limits.h>
#include <stdio.h>
#include <string.h>

#define MAX_VALOR 10000

int menor(int primeiro, int segundo) {
    return primeiro < segundo ? primeiro : segundo;
}

int troco_recursivo(int moedas[], int quantidade_moedas, int valor) {
    if (valor == 0) {
        return 0;
    }

    int melhor = INT_MAX / 2;

    for (int posicao = 0; posicao < quantidade_moedas; posicao++) {
        /* Escolhe uma moeda e resolve o troco que sobrou. */
        if (moedas[posicao] <= valor) {
            int candidato = 1 + troco_recursivo(moedas, quantidade_moedas, valor - moedas[posicao]);
            melhor = menor(melhor, candidato);
        }
    }

    return melhor;
}

int troco_top_down_aux(int moedas[], int quantidade_moedas, int valor, int memo[]) {
    if (valor == 0) {
        return 0;
    }

    if (memo[valor] != -1) {
        return memo[valor];
    }

    /* memo[valor] evita recalcular o mesmo troco varias vezes. */
    int melhor = INT_MAX / 2;

    for (int posicao = 0; posicao < quantidade_moedas; posicao++) {
        if (moedas[posicao] <= valor) {
            int candidato = 1 + troco_top_down_aux(moedas, quantidade_moedas, valor - moedas[posicao], memo);
            melhor = menor(melhor, candidato);
        }
    }

    memo[valor] = melhor;
    return melhor;
}

int troco_top_down(int moedas[], int quantidade_moedas, int valor) {
    int memo[MAX_VALOR + 1];
    memset(memo, -1, sizeof(memo));
    return troco_top_down_aux(moedas, quantidade_moedas, valor, memo);
}

int troco_bottom_up(int moedas[], int quantidade_moedas, int valor) {
    int minimo[MAX_VALOR + 1];
    minimo[0] = 0;

    for (int total = 1; total <= valor; total++) {
        /* minimo[total] e construido usando valores menores ja resolvidos. */
        minimo[total] = INT_MAX / 2;

        for (int posicao = 0; posicao < quantidade_moedas; posicao++) {
            if (moedas[posicao] <= total) {
                int candidato = minimo[total - moedas[posicao]] + 1;
                minimo[total] = menor(minimo[total], candidato);
            }
        }
    }

    return minimo[valor];
}

int main(void) {
    int quantidade_moedas, valor;
    int moedas[100];

    printf("Quantidade de moedas e valor do troco: ");
    scanf("%d %d", &quantidade_moedas, &valor);

    printf("Valores das moedas: ");
    for (int posicao = 0; posicao < quantidade_moedas; posicao++) {
        scanf("%d", &moedas[posicao]);
    }

    printf("Recursiva: %d\n", troco_recursivo(moedas, quantidade_moedas, valor));
    printf("Top-down: %d\n", troco_top_down(moedas, quantidade_moedas, valor));
    printf("Bottom-up: %d\n", troco_bottom_up(moedas, quantidade_moedas, valor));

    return 0;
}
