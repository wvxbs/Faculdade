#include <stdio.h>

void calcular_selos(int taxa) {
    /* Comecamos com o maior numero possivel de selos de 5. */
    int selos_de_5 = taxa / 5;

    while (selos_de_5 >= 0) {
        int restante = taxa - 5 * selos_de_5;

        /* Se o restante fecha com selos de 3, achamos o menor total. */
        if (restante % 3 == 0) {
            int selos_de_3 = restante / 3;
            printf("Selos de 5 centavos: %d\n", selos_de_5);
            printf("Selos de 3 centavos: %d\n", selos_de_3);
            printf("Total de selos: %d\n", selos_de_5 + selos_de_3);
            return;
        }

        /* Se nao fechou, trocamos um selo de 5 por espaco para selos de 3. */
        selos_de_5--;
    }

    printf("Nao existe combinacao para essa taxa.\n");
}

int main(void) {
    int taxa;

    printf("Taxa em centavos: ");
    scanf("%d", &taxa);

    calcular_selos(taxa);
    return 0;
}
