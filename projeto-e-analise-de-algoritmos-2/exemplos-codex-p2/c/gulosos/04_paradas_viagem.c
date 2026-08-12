#include <stdio.h>

int menor_numero_paradas(int postos[], int quantidade_postos, int autonomia, int distancia_destino) {
    int posicao_atual = 0;
    int proximo_posto = 0;
    int paradas = 0;

    while (posicao_atual + autonomia < distancia_destino) {
        /* Procuramos o posto mais distante dentro da autonomia atual. */
        int melhor_alcance = posicao_atual;

        while (proximo_posto < quantidade_postos &&
               postos[proximo_posto] <= posicao_atual + autonomia) {
            melhor_alcance = postos[proximo_posto];
            proximo_posto++;
        }

        /* Se nenhum posto novo foi alcancado, a viagem e impossivel. */
        if (melhor_alcance == posicao_atual) {
            return -1;
        }

        printf("Parar no km %d\n", melhor_alcance);
        posicao_atual = melhor_alcance;
        paradas++;
    }

    return paradas;
}

int main(void) {
    int quantidade_postos, autonomia, distancia_destino;
    int postos[1000];

    printf("Quantidade de postos, autonomia e distancia destino: ");
    scanf("%d %d %d", &quantidade_postos, &autonomia, &distancia_destino);

    printf("Distancias dos postos: ");
    for (int posicao = 0; posicao < quantidade_postos; posicao++) {
        scanf("%d", &postos[posicao]);
    }

    int paradas = menor_numero_paradas(postos, quantidade_postos, autonomia, distancia_destino);
    printf("Menor numero de paradas: %d\n", paradas);

    return 0;
}
