#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int inicio;
    int termino;
    int nome;
} Atividade;

int comparar_por_termino(const void *primeiro, const void *segundo) {
    Atividade *atividade_a = (Atividade *) primeiro;
    Atividade *atividade_b = (Atividade *) segundo;
    return atividade_a->termino - atividade_b->termino;
}

void seleciona_atividades_guloso(Atividade atividades[], int quantidade) {
    /* Terminar cedo deixa mais espaco para as proximas atividades. */
    qsort(atividades, quantidade, sizeof(Atividade), comparar_por_termino);

    int ultimo_termino = -1;

    for (int posicao = 0; posicao < quantidade; posicao++) {
        /* A atividade so entra se nao conflitar com a ultima escolhida. */
        if (atividades[posicao].inicio >= ultimo_termino) {
            printf("Atividade %d [%d, %d]\n",
                   atividades[posicao].nome,
                   atividades[posicao].inicio,
                   atividades[posicao].termino);
            ultimo_termino = atividades[posicao].termino;
        }
    }
}

int main(void) {
    int quantidade;
    Atividade atividades[1000];

    printf("Quantidade de atividades: ");
    scanf("%d", &quantidade);

    for (int posicao = 0; posicao < quantidade; posicao++) {
        atividades[posicao].nome = posicao + 1;
        printf("Inicio e termino da atividade %d: ", posicao + 1);
        scanf("%d %d", &atividades[posicao].inicio, &atividades[posicao].termino);
    }

    seleciona_atividades_guloso(atividades, quantidade);
    return 0;
}
