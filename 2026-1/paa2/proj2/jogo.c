/*
    Integrantes do projeto:

    Gabriel Ferreira
    RA: 10442043

    Gian Lucca Campanha Ribeiro
    RA: 10438361

    Pedro Henrique Esperança de Oliveira
    RA: 10403152
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 20
#define MAX_STR   100

/*Vetores Globais da fase atual*/
char   nomes[MAX_ITENS][MAX_STR];
char   tipos [MAX_ITENS][MAX_STR];
double pesos[MAX_ITENS];
double valores[MAX_ITENS];
double valores_aj[MAX_ITENS];
double razao[MAX_ITENS];
int    n;
double capacidade;
char   regra[MAX_STR];
char   nome_fase[MAX_STR];


void ordenar() {
    int i, j;
    for (i = 1; i < n; i++) {
        double r = razao[i],  p = pesos[i];
        double v = valores[i], va = valores_aj[i];
        char   nm[MAX_STR],   tp[MAX_STR];
        strcpy(nm, nomes[i]);
        strcpy(tp, tipos[i]);

        j = i - 1;
        while (j >= 0 && razao[j] < r) {
            razao[j+1]      = razao[j];
            pesos[j+1]      = pesos[j];
            valores[j+1]    = valores[j];
            valores_aj[j+1] = valores_aj[j];
            strcpy(nomes[j+1], nomes[j]);
            strcpy(tipos[j+1], tipos[j]);
            j--;
        }
        razao[j+1]      = r;
        pesos[j+1]      = p;
        valores[j+1]    = v;
        valores_aj[j+1] = va;
        strcpy(nomes[j+1], nm);
        strcpy(tipos[j+1], tp);
    }
}


void aplicar_regra() {
    int i;

    if (strcmp(regra, "MAGICOS_VALOR_DOBRADO") == 0) {
        for (i = 0; i < n; i++) {
            valores_aj[i] = (strcmp(tipos[i], "magico") == 0)
                            ? valores[i] * 2.0 : valores[i];
            razao[i] = valores_aj[i] / pesos[i];
        }
    }
    else if (strcmp(regra, "TECNOLOGICOS_INTEIROS") == 0) {
        for (i = 0; i < n; i++) {
            valores_aj[i] = valores[i];
            razao[i]      = valores[i] / pesos[i];
        }
    }
    else if (strcmp(regra, "SOBREVIVENCIA_DESVALORIZADA") == 0) {
        for (i = 0; i < n; i++) {
            valores_aj[i] = (strcmp(tipos[i], "sobrevivencia") == 0)
                            ? valores[i] * 0.8 : valores[i];
            razao[i] = valores_aj[i] / pesos[i];
        }
    }
    else if (strcmp(regra, "TRES_MELHORES_VALOR_PESO") == 0) {
        for (i = 0; i < n; i++) {
            valores_aj[i] = valores[i];
            razao[i]      = valores[i] / pesos[i];
        }
        ordenar();
        if (n > 3) n = 3;  /* descarta os demais */
    }
}


double *mochila_fracionaria() {
    double *x = (double *) calloc(n, sizeof(double));
    double  W = capacidade;
    int     i = 0;

    while (i < n && W > 1e-9) {
        /* Regra 2: tecnologico que nao cabe inteiro e ignorado */
        if (strcmp(regra, "TECNOLOGICOS_INTEIROS") == 0 &&
            strcmp(tipos[i], "tecnologico") == 0 &&
            pesos[i] > W) {
            i++;
            continue;
        }

        if (pesos[i] <= W) {
            x[i]  = 1.0;
            W    -= pesos[i];
        } else {
            x[i] = W / pesos[i];
            W    = 0.0;
        }
        i++;
    }
    return x;
}


double gravar_fase(FILE *saida) {
    int    i;
    double lucro = 0.0;

    fprintf(saida, "\n--- FASE: %s ---\n", nome_fase);
    fprintf(saida, "Capacidade da mochila: %.2f kg\n", capacidade);

    if      (strcmp(regra,"MAGICOS_VALOR_DOBRADO")      == 0)
        fprintf(saida, "Regra aplicada: Itens magicos com valor dobrado\n");
    else if (strcmp(regra,"TECNOLOGICOS_INTEIROS")       == 0)
        fprintf(saida, "Regra aplicada: Itens tecnologicos nao podem ser fracionados\n");
    else if (strcmp(regra,"SOBREVIVENCIA_DESVALORIZADA") == 0)
        fprintf(saida, "Regra aplicada: Itens de sobrevivencia perdem 20%% do valor\n");
    else if (strcmp(regra,"TRES_MELHORES_VALOR_PESO")    == 0)
        fprintf(saida, "Regra aplicada: Apenas os tres itens com maior valor/peso podem ser escolhidos\n");

    double *x = mochila_fracionaria();

    for (i = 0; i < n; i++) {
        if (x[i] < 1e-9) continue;
        double val  = valores_aj[i] * x[i];
        double peso = pesos[i]      * x[i];
        lucro += val;
        if (x[i] == 1.0)
            fprintf(saida, "Pegou (inteiro) %s (%.2fkg, R$ %.2f)\n",
                    nomes[i], peso, val);
        else
            fprintf(saida, "Pegou (fracionado) %s (%.2fkg, R$ %.2f)\n",
                    nomes[i], peso, val);
    }
    fprintf(saida, "Lucro da fase: R$ %.2f\n", lucro);

    free(x);
    return lucro;
}


void processar(const char *entrada, const char *saida) {
    FILE *fin  = fopen(entrada, "r");
    FILE *fout = fopen(saida,   "w");
    if (!fin || !fout) { printf("Erro ao abrir arquivos.\n"); return; }

    char   linha[256];
    double lucro_total = 0.0;
    int    tem_fase    = 0;

    while (fgets(linha, sizeof(linha), fin)) {
        /* remove \n */
        linha[strcspn(linha, "\r\n")] = '\0';
        if (strlen(linha) == 0) continue;

        if (strncmp(linha, "FASE:", 5) == 0) {
            if (tem_fase) {
                if (strcmp(regra, "TRES_MELHORES_VALOR_PESO") != 0)
                    ordenar();
                lucro_total += gravar_fase(fout);
            }
            strcpy(nome_fase, linha + 6);
            n = 0; tem_fase = 1;

        } else if (strncmp(linha, "CAPACIDADE:", 11) == 0) {
            capacidade = atof(linha + 12);

        } else if (strncmp(linha, "REGRA:", 6) == 0) {
            strcpy(regra, linha + 7);

        } else if (strncmp(linha, "ITEM:", 5) == 0) {
            char *tok = strtok(linha + 6, ",");
            /* remove espaco inicial do nome */
            while (*tok == ' ') tok++;
            strcpy(nomes[n], tok);

            tok = strtok(NULL, ","); pesos[n]   = atof(tok);
            tok = strtok(NULL, ","); valores[n]  = atof(tok);
            tok = strtok(NULL, ",");
            while (*tok == ' ') tok++;
            tok[strcspn(tok, "\r\n")] = '\0';
            strcpy(tipos[n], tok);

            valores_aj[n] = valores[n];
            razao[n]      = valores[n] / pesos[n];
            n++;
            aplicar_regra();
        }
    }

    /* processa a ultima fase */
    if (tem_fase) {
        if (strcmp(regra, "TRES_MELHORES_VALOR_PESO") != 0)
            ordenar();
        lucro_total += gravar_fase(fout);
    }

    fprintf(fout, "\n==============================\n");
    fprintf(fout, "LUCRO TOTAL: R$ %.2f\n", lucro_total);
    fprintf(fout, "==============================\n");

    fclose(fin);
    fclose(fout);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s entrada_jogo.txt saida_jogo.txt\n", argv[0]);
        return 1;
    }
    processar(argv[1], argv[2]);
    printf("Resultado gravado em: %s\n", argv[2]);
    return 0;
}