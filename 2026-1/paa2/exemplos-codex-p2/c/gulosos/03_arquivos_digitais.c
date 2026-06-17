#include <stdio.h>
#include <stdlib.h>

int comparar_inteiros(const void *primeiro, const void *segundo) {
    return (*(int *) primeiro) - (*(int *) segundo);
}

int contar_arquivos_copiados(int tamanhos[], int quantidade_arquivos, int capacidade) {
    /* Arquivos menores primeiro maximizam a quantidade copiada. */
    qsort(tamanhos, quantidade_arquivos, sizeof(int), comparar_inteiros);

    int espaco_usado = 0;
    int arquivos_copiados = 0;

    for (int posicao = 0; posicao < quantidade_arquivos; posicao++) {
        /* Enquanto couber, copiamos; o primeiro que nao couber encerra. */
        if (espaco_usado + tamanhos[posicao] <= capacidade) {
            espaco_usado += tamanhos[posicao];
            arquivos_copiados++;
        } else {
            break;
        }
    }

    return arquivos_copiados;
}

int main(void) {
    int quantidade_arquivos, capacidade;
    int tamanhos[1000];

    printf("Quantidade de arquivos e capacidade: ");
    scanf("%d %d", &quantidade_arquivos, &capacidade);

    printf("Tamanhos dos arquivos: ");
    for (int posicao = 0; posicao < quantidade_arquivos; posicao++) {
        scanf("%d", &tamanhos[posicao]);
    }

    printf("Maior quantidade copiada: %d\n",
           contar_arquivos_copiados(tamanhos, quantidade_arquivos, capacidade));

    return 0;
}
