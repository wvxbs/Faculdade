#include <stdio.h>
#include <string.h>

#define MAX_ITENS 100
#define MAX_CAPACIDADE 1000

int maior(int primeiro, int segundo) {
    return primeiro > segundo ? primeiro : segundo;
}

int mochila01_recursiva(int pesos[], int valores[], int quantidade, int capacidade) {
    if (quantidade == 0 || capacidade == 0) {
        return 0;
    }

    int ultimo = quantidade - 1;

    /* Se o ultimo item nao cabe, ele obrigatoriamente fica fora. */
    if (pesos[ultimo] > capacidade) {
        return mochila01_recursiva(pesos, valores, quantidade - 1, capacidade);
    }

    int sem_item = mochila01_recursiva(pesos, valores, quantidade - 1, capacidade);
    /* Caso contrario, comparamos deixar fora contra colocar dentro. */
    int com_item = valores[ultimo] +
                   mochila01_recursiva(pesos, valores, quantidade - 1, capacidade - pesos[ultimo]);

    return maior(com_item, sem_item);
}

int mochila01_top_down_aux(int pesos[], int valores[], int quantidade, int capacidade,
                           int memo[MAX_ITENS + 1][MAX_CAPACIDADE + 1]) {
    if (quantidade == 0 || capacidade == 0) {
        return 0;
    }

    if (memo[quantidade][capacidade] != -1) {
        return memo[quantidade][capacidade];
    }

    /* Estado: melhor valor usando os primeiros 'quantidade' itens. */
    int ultimo = quantidade - 1;

    if (pesos[ultimo] > capacidade) {
        memo[quantidade][capacidade] =
            mochila01_top_down_aux(pesos, valores, quantidade - 1, capacidade, memo);
    } else {
        int sem_item = mochila01_top_down_aux(pesos, valores, quantidade - 1, capacidade, memo);
        int com_item = valores[ultimo] +
                       mochila01_top_down_aux(pesos, valores, quantidade - 1,
                                              capacidade - pesos[ultimo], memo);
        memo[quantidade][capacidade] = maior(com_item, sem_item);
    }

    return memo[quantidade][capacidade];
}

int mochila01_top_down(int pesos[], int valores[], int quantidade, int capacidade) {
    int memo[MAX_ITENS + 1][MAX_CAPACIDADE + 1];
    memset(memo, -1, sizeof(memo));
    return mochila01_top_down_aux(pesos, valores, quantidade, capacidade, memo);
}

int mochila01_bottom_up(int pesos[], int valores[], int quantidade, int capacidade) {
    int melhor[MAX_ITENS + 1][MAX_CAPACIDADE + 1];

    for (int itens = 0; itens <= quantidade; itens++) {
        for (int limite = 0; limite <= capacidade; limite++) {
            if (itens == 0 || limite == 0) {
                melhor[itens][limite] = 0;
            } else {
                /* Cada celula decide se o item atual entra ou nao. */
                int item_atual = itens - 1;
                int sem_item = melhor[itens - 1][limite];
                int com_item = 0;

                if (pesos[item_atual] <= limite) {
                    com_item     = valores[item_atual] + melhor[itens - 1][limite - pesos[item_atual]];
                }

                melhor[itens][limite] = maior(com_item, sem_item);
            }
        }
    }

    return melhor[quantidade][capacidade];
}

int main(void) {
    int quantidade, capacidade;
    int pesos[MAX_ITENS], valores[MAX_ITENS];

    printf("Quantidade de itens e capacidade: ");
    scanf("%d %d", &quantidade, &capacidade);

    for (int posicao = 0; posicao < quantidade; posicao++) {
        printf("Peso e valor do item %d: ", posicao + 1);
        scanf("%d %d", &pesos[posicao], &valores[posicao]);
    }

    printf("Recursiva: %d\n", mochila01_recursiva(pesos, valores, quantidade, capacidade));
    printf("Top-down: %d\n", mochila01_top_down(pesos, valores, quantidade, capacidade));
    printf("Bottom-up: %d\n", mochila01_bottom_up(pesos, valores, quantidade, capacidade));

    return 0;
}
