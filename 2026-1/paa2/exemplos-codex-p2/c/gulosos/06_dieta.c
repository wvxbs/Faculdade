#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double calorias;
    double proteinas;
    double fracao;
    int nome;
} Alimento;

int comparar_por_proteina_caloria(const void *primeiro, const void *segundo) {
    Alimento *alimento_a = (Alimento *) primeiro;
    Alimento *alimento_b = (Alimento *) segundo;
    double razao_a = alimento_a->proteinas / alimento_a->calorias;
    double razao_b = alimento_b->proteinas / alimento_b->calorias;

    if (razao_a < razao_b) return 1;
    if (razao_a > razao_b) return -1;
    return 0;
}

double montar_dieta(Alimento alimentos[], int quantidade, double limite_calorias) {
    /* Priorizamos os alimentos com mais proteina por caloria. */
    qsort(alimentos, quantidade, sizeof(Alimento), comparar_por_proteina_caloria);

    double proteinas_totais = 0.0;

    for (int posicao = 0; posicao < quantidade; posicao++) {
        alimentos[posicao].fracao = 0.0;

        if (limite_calorias <= 0.0) {
            continue;
        }

        /* Usa o pote inteiro se couber; se nao, usa a fracao possivel. */
        if (alimentos[posicao].calorias <= limite_calorias) {
            alimentos[posicao].fracao = 1.0;
            limite_calorias -= alimentos[posicao].calorias;
            proteinas_totais += alimentos[posicao].proteinas;
        } else {
            alimentos[posicao].fracao = limite_calorias / alimentos[posicao].calorias;
            proteinas_totais += alimentos[posicao].proteinas * alimentos[posicao].fracao;
            limite_calorias = 0.0;
        }
    }

    return proteinas_totais;
}

int main(void) {
    int quantidade;
    double limite_calorias;
    Alimento alimentos[1000];

    printf("Quantidade de alimentos e limite de calorias: ");
    scanf("%d %lf", &quantidade, &limite_calorias);

    for (int posicao = 0; posicao < quantidade; posicao++) {
        alimentos[posicao].nome = posicao + 1;
        printf("Calorias e proteinas do alimento %d: ", posicao + 1);
        scanf("%lf %lf", &alimentos[posicao].calorias, &alimentos[posicao].proteinas);
    }

    double proteinas = montar_dieta(alimentos, quantidade, limite_calorias);

    printf("Proteinas totais: %.2f\n", proteinas);
    for (int posicao = 0; posicao < quantidade; posicao++) {
        printf("Alimento %d: %.2f%%\n", alimentos[posicao].nome, alimentos[posicao].fracao * 100.0);
    }

    return 0;
}
