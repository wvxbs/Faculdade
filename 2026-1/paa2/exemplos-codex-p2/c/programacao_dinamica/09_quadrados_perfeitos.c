#include <limits.h>
#include <stdio.h>

int menor_quantidade_quadrados(int numero) {
    int minimo[10001];
    minimo[0] = 0;

    for (int valor = 1; valor <= numero; valor++) {
        /* minimo[valor] guarda a melhor resposta para esse valor. */
        minimo[valor] = INT_MAX;

        for (int base = 1; base * base <= valor; base++) {
            int quadrado = base * base;
            /* Testa usar este quadrado como a ultima parcela da soma. */
            int candidato = minimo[valor - quadrado] + 1;

            if (candidato < minimo[valor]) {
                minimo[valor] = candidato;
            }
        }
    }

    return minimo[numero];
}

int main(void) {
    int numero;

    printf("Numero: ");
    scanf("%d", &numero);

    printf("Menor quantidade: %d\n", menor_quantidade_quadrados(numero));
    return 0;
}
