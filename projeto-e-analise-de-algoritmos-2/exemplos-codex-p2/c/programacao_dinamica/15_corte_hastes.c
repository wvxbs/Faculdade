#include <limits.h>
#include <stdio.h>
#include <string.h>

#define MAX_TAMANHO 1000

int corte_haste_recursivo(int precos[], int tamanho) {
    if (tamanho == 0) {
        return 0;
    }

    int melhor_receita = INT_MIN;

    /* Tenta todos os tamanhos possiveis para o primeiro pedaco. */
    for (int primeiro_corte = 1; primeiro_corte <= tamanho; primeiro_corte++) {
        int receita = precos[primeiro_corte] +
                      corte_haste_recursivo(precos, tamanho - primeiro_corte);

        if (receita > melhor_receita) {
            melhor_receita = receita;
        }
    }

    return melhor_receita;
}

int corte_haste_top_down_aux(int precos[], int tamanho, int memo[]) {
    if (tamanho == 0) {
        return 0;
    }

    if (memo[tamanho] != -1) {
        return memo[tamanho];
    }

    /* memo[tamanho] guarda a melhor receita para uma haste desse tamanho. */
    int melhor_receita = INT_MIN;

    for (int primeiro_corte = 1; primeiro_corte <= tamanho; primeiro_corte++) {
        int receita = precos[primeiro_corte] +
                      corte_haste_top_down_aux(precos, tamanho - primeiro_corte, memo);

        if (receita > melhor_receita) {
            melhor_receita = receita;
        }
    }

    memo[tamanho] = melhor_receita;
    return memo[tamanho];
}

int corte_haste_top_down(int precos[], int tamanho) {
    int memo[MAX_TAMANHO + 1];
    memset(memo, -1, sizeof(memo));
    return corte_haste_top_down_aux(precos, tamanho, memo);
}

int corte_haste_bottom_up(int precos[], int tamanho, int primeiro_corte[]) {
    int melhor_receita[MAX_TAMANHO + 1];
    melhor_receita[0] = 0;

    for (int comprimento = 1; comprimento <= tamanho; comprimento++) {
        /* Resolve hastes menores antes de usar suas respostas. */
        melhor_receita[comprimento] = INT_MIN;

        for (int corte = 1; corte <= comprimento; corte++) {
            int receita = precos[corte] + melhor_receita[comprimento - corte];

            if (receita > melhor_receita[comprimento]) {
                melhor_receita[comprimento] = receita;
                /* Guarda o primeiro corte para imprimir a solucao depois. */
                primeiro_corte[comprimento] = corte;
            }
        }
    }

    return melhor_receita[tamanho];
}

void imprimir_cortes(int tamanho, int primeiro_corte[]) {
    while (tamanho > 0) {
        printf("%d ", primeiro_corte[tamanho]);
        tamanho -= primeiro_corte[tamanho];
    }
    printf("\n");
}

int main(void) {
    int tamanho;
    int precos[MAX_TAMANHO + 1];
    int primeiro_corte[MAX_TAMANHO + 1];

    printf("Tamanho da haste: ");
    scanf("%d", &tamanho);

    printf("Precos de 1 ate %d: ", tamanho);
    for (int comprimento = 1; comprimento <= tamanho; comprimento++) {
        scanf("%d", &precos[comprimento]);
    }

    printf("Recursiva: %d\n", corte_haste_recursivo(precos, tamanho));
    printf("Top-down: %d\n", corte_haste_top_down(precos, tamanho));
    printf("Bottom-up: %d\n", corte_haste_bottom_up(precos, tamanho, primeiro_corte));
    printf("Cortes escolhidos: ");
    imprimir_cortes(tamanho, primeiro_corte);

    return 0;
}
