#include <stdio.h>
#include <string.h>

#define MAX_ITENS 100

int maior(int primeiro, int segundo) {
    return primeiro > segundo ? primeiro : segundo;
}

int lis_recursiva_aux(int sequencia[], int quantidade, int posicao, int anterior) {
    if (posicao == quantidade) {
        return 0;
    }

    int sem_atual = lis_recursiva_aux(sequencia, quantidade, posicao + 1, anterior);
    int com_atual = 0;

    /* Em cada posicao decidimos: pegar ou ignorar o numero atual. */
    if (anterior == -1 || sequencia[posicao] > sequencia[anterior]) {
        com_atual = 1 + lis_recursiva_aux(sequencia, quantidade, posicao + 1, posicao);
    }

    return maior(com_atual, sem_atual);
}

int lis_recursiva(int sequencia[], int quantidade) {
    return lis_recursiva_aux(sequencia, quantidade, 0, -1);
}

int lis_top_down_aux(int sequencia[], int quantidade, int posicao, int anterior,
                     int memo[MAX_ITENS][MAX_ITENS + 1]) {
    if (posicao == quantidade) {
        return 0;
    }

    int coluna_anterior = anterior + 1;
    /* anterior + 1 permite guardar anterior = -1 na coluna 0. */
    if (memo[posicao][coluna_anterior] != -1) {
        return memo[posicao][coluna_anterior];
    }

    int sem_atual = lis_top_down_aux(sequencia, quantidade, posicao + 1, anterior, memo);
    int com_atual = 0;

    if (anterior == -1 || sequencia[posicao] > sequencia[anterior]) {
        com_atual = 1 + lis_top_down_aux(sequencia, quantidade, posicao + 1, posicao, memo);
    }

    memo[posicao][coluna_anterior] = maior(com_atual, sem_atual);
    return memo[posicao][coluna_anterior];
}

int lis_top_down(int sequencia[], int quantidade) {
    int memo[MAX_ITENS][MAX_ITENS + 1];
    memset(memo, -1, sizeof(memo));
    return lis_top_down_aux(sequencia, quantidade, 0, -1, memo);
}

int lis_bottom_up(int sequencia[], int quantidade) {
    int tamanho_lis[MAX_ITENS];
    int melhor_tamanho = 0;

    for (int atual = 0; atual < quantidade; atual++) {
        tamanho_lis[atual] = 1;

        /* Tenta terminar a subsequencia no elemento atual. */
        for (int anterior = 0; anterior < atual; anterior++) {
            if (sequencia[anterior] < sequencia[atual] &&
                tamanho_lis[anterior] + 1 > tamanho_lis[atual]) {
                tamanho_lis[atual] = tamanho_lis[anterior] + 1;
            }
        }

        if (tamanho_lis[atual] > melhor_tamanho) {
            melhor_tamanho = tamanho_lis[atual];
        }
    }

    return melhor_tamanho;
}

int main(void) {
    int quantidade;
    int sequencia[MAX_ITENS];

    printf("Quantidade de numeros: ");
    scanf("%d", &quantidade);

    printf("Sequencia: ");
    for (int posicao = 0; posicao < quantidade; posicao++) {
        scanf("%d", &sequencia[posicao]);
    }

    printf("Recursiva: %d\n", lis_recursiva(sequencia, quantidade));
    printf("Top-down: %d\n", lis_top_down(sequencia, quantidade));
    printf("Bottom-up: %d\n", lis_bottom_up(sequencia, quantidade));

    return 0;
}
