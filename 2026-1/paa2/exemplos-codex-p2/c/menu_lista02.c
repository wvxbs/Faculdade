#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int numero;
    const char *titulo;
    const char *arquivo_executavel;
} Exercicio;

void mostrar_exercicios(Exercicio exercicios[], int quantidade) {
    printf("\nLista 02 - escolha um exercicio\n\n");

    for (int posicao = 0; posicao < quantidade; posicao++) {
        printf("%2d. %s\n", exercicios[posicao].numero, exercicios[posicao].titulo);
    }

    printf("\n 0. Sair\n\n");
}

const char *buscar_arquivo_executavel(Exercicio exercicios[], int quantidade, int numero) {
    for (int posicao = 0; posicao < quantidade; posicao++) {
        if (exercicios[posicao].numero == numero) {
            return exercicios[posicao].arquivo_executavel;
        }
    }

    return NULL;
}

void descobrir_pasta_do_menu(char caminho_menu[], char pasta_menu[]) {
    strcpy(pasta_menu, caminho_menu);

    char *ultima_barra = strrchr(pasta_menu, '/');

    if (ultima_barra == NULL) {
        strcpy(pasta_menu, ".");
    } else {
        *ultima_barra = '\0';
    }
}

int main(int quantidade_argumentos, char *argumentos[]) {
    (void) quantidade_argumentos;

    Exercicio exercicios[] = {
        {1, "Problema do troco - guloso", "01_troco_guloso"},
        {2, "Problema dos selos", "02_selos"},
        {3, "Arquivos digitais", "03_arquivos_digitais"},
        {4, "Menor numero de paradas em viagem", "04_paradas_viagem"},
        {5, "Mochila fracionaria", "05_mochila_fracionaria"},
        {6, "Dieta", "06_dieta"},
        {7, "Selecao de atividades", "07_selecao_atividades"},
        {8, "Subindo as escadas", "08_subindo_escadas"},
        {9, "Quadrados perfeitos", "09_quadrados_perfeitos"},
        {10, "Subsequencia crescente mais longa", "10_lis"},
        {11, "Troco - programacao dinamica", "11_troco_pd"},
        {12, "Mochila 0/1", "12_mochila_01"},
        {13, "Multiplicacao de matrizes", "13_multiplicacao_matrizes"},
        {14, "Subsequencia comum maxima", "14_lcs"},
        {15, "Corte das hastes de aco", "15_corte_hastes"}
    };

    int quantidade = sizeof(exercicios) / sizeof(exercicios[0]);
    int escolha;
    char entrada[16];
    char pasta_menu[512];
    char caminho_executavel[1024];

    setvbuf(stdout, NULL, _IONBF, 0);
    descobrir_pasta_do_menu(argumentos[0], pasta_menu);

    mostrar_exercicios(exercicios, quantidade);
    printf("Digite o numero do exercicio: ");

    int tamanho = 0;
    char caractere = '\0';

    /* Le so a linha da escolha; o resto da entrada fica para o exercicio. */
    while (tamanho < 15 && read(STDIN_FILENO, &caractere, 1) == 1 && caractere != '\n') {
        entrada[tamanho] = caractere;
        tamanho++;
    }
    entrada[tamanho] = '\0';

    if (sscanf(entrada, "%d", &escolha) != 1) {
        printf("Entrada invalida.\n");
        return 1;
    }

    if (escolha == 0) {
        printf("Ate mais.\n");
        return 0;
    }

    const char *arquivo_executavel = buscar_arquivo_executavel(exercicios, quantidade, escolha);

    if (arquivo_executavel == NULL) {
        printf("Exercicio inexistente. Escolha um numero de 1 a 15.\n");
        return 1;
    }

    snprintf(caminho_executavel, sizeof(caminho_executavel), "%s/%s", pasta_menu, arquivo_executavel);

    printf("\nExecutando exercicio %d...\n\n", escolha);
    execl(caminho_executavel, caminho_executavel, (char *) NULL);
    perror("Erro ao abrir exercicio");
    return 1;
}
