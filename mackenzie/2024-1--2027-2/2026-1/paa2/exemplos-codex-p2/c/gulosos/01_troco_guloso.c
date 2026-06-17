#include <math.h>
#include <stdio.h>

void decompor_valor(double valor) {
    /* Trabalhar em centavos evita erros com ponto flutuante. */
    int centavos_restantes = (int) round(valor * 100.0);
    int notas[] = {10000, 5000, 2000, 1000, 500, 200};
    int moedas[] = {100, 50, 25, 10, 5, 1};

    /* O guloso sempre pega primeiro a maior nota que ainda cabe. */
    printf("NOTAS:\n");
    for (int posicao = 0; posicao < 6; posicao++) {
        int quantidade = centavos_restantes / notas[posicao];
        centavos_restantes %= notas[posicao];
        printf("%d nota(s) de R$ %.2f\n", quantidade, notas[posicao] / 100.0);
    }

    /* Depois das notas, o mesmo raciocinio vale para as moedas. */
    printf("MOEDAS:\n");
    for (int posicao = 0; posicao < 6; posicao++) {
        int quantidade = centavos_restantes / moedas[posicao];
        centavos_restantes %= moedas[posicao];
        printf("%d moeda(s) de R$ %.2f\n", quantidade, moedas[posicao] / 100.0);
    }
}

int main(void) {
    double valor;

    printf("Valor: ");
    scanf("%lf", &valor);

    decompor_valor(valor);
    return 0;
}
