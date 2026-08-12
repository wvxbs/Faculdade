#include <stdio.h>

int contar_formas_escada(int degraus) {
    if (degraus <= 2) {
        return degraus;
    }

    int formas_penultimo = 1;
    int formas_ultimo = 2;

    /* Cada degrau pode vir de um passo de 1 ou de um passo de 2. */
    for (int altura = 3; altura <= degraus; altura++) {
        int formas_atual = formas_penultimo + formas_ultimo;
        formas_penultimo = formas_ultimo;
        formas_ultimo = formas_atual;
    }

    return formas_ultimo;
}

int main(void) {
    int degraus;

    printf("Numero de degraus: ");
    scanf("%d", &degraus);

    printf("Maneiras distintas: %d\n", contar_formas_escada(degraus));
    return 0;
}
