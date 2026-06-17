#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double peso;
    double valor;
    double fracao;
    int nome;
} Objeto;

int comparar_por_densidade(const void *primeiro, const void *segundo) {
    Objeto *objeto_a = (Objeto *) primeiro;
    Objeto *objeto_b = (Objeto *) segundo;
    double densidade_a = objeto_a->valor / objeto_a->peso;
    double densidade_b = objeto_b->valor / objeto_b->peso;

    if (densidade_a < densidade_b) return 1;
    if (densidade_a > densidade_b) return -1;
    return 0;
}

double mochila_fracionaria(Objeto objetos[], int quantidade, double capacidade) {
    /* Melhor custo-beneficio primeiro: maior valor por unidade de peso. */
    qsort(objetos, quantidade, sizeof(Objeto), comparar_por_densidade);

    double valor_total = 0.0;

    for (int posicao = 0; posicao < quantidade; posicao++) {
        objetos[posicao].fracao = 0.0;

        if (capacidade <= 0.0) {
            continue;
        }

        /* Pega o item inteiro se couber; senao pega so a fracao restante. */
        if (objetos[posicao].peso <= capacidade) {
            objetos[posicao].fracao = 1.0;
            capacidade -= objetos[posicao].peso;
            valor_total += objetos[posicao].valor;
        } else {
            objetos[posicao].fracao = capacidade / objetos[posicao].peso;
            valor_total += objetos[posicao].valor * objetos[posicao].fracao;
            capacidade = 0.0;
        }
    }

    return valor_total;
}

int main(void) {
    int quantidade;
    double capacidade;
    Objeto objetos[1000];

    printf("Quantidade de objetos e capacidade: ");
    scanf("%d %lf", &quantidade, &capacidade);

    for (int posicao = 0; posicao < quantidade; posicao++) {
        objetos[posicao].nome = posicao + 1;
        printf("Peso e valor do objeto %d: ", posicao + 1);
        scanf("%lf %lf", &objetos[posicao].peso, &objetos[posicao].valor);
    }

    double valor_total = mochila_fracionaria(objetos, quantidade, capacidade);

    printf("Valor total: %.2f\n", valor_total);
    for (int posicao = 0; posicao < quantidade; posicao++) {
        printf("Objeto %d: %.2f%%\n", objetos[posicao].nome, objetos[posicao].fracao * 100.0);
    }

    return 0;
}
