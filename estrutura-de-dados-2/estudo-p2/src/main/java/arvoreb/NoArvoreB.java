package com.mackenzie.arvoreb;

/**
 * Estrutura conceitual de uma página (Nó) de uma Árvore B.
 * Digamos que seja uma Árvore B de ordem M.
 */
public class NoArvoreB {
    int m;                 // Ordem da árvore (número máximo de filhos)
    int numChavesAtuais;   // Quantas chaves este nó tem no momento
    int[] chaves;          // Array para guardar os dados/chaves (tamanho M - 1)
    NoArvoreB[] filhos;    // Array de ponteiros para os filhos (tamanho M)
    boolean ehFolha;       // True se for um nó folha (nível mais baixo), False se for nó interno

    // Construtor
    public NoArvoreB(int ordem, boolean ehFolha) {
        this.m = ordem;
        this.ehFolha = ehFolha;
        this.numChavesAtuais = 0;
        
        // A regra de ouro: max filhos = M, max chaves = M - 1
        this.chaves = new int[m - 1];
        this.filhos = new NoArvoreB[m];
    }
}