package com.mackenzie.hash;

/**
 * Tabela Hash usando Endereçamento Aberto (Sondagem Linear).
 * Todos os elementos são armazenados no próprio array.
 */
public class HashSondagemLinear<K, V> {
    private K[] chaves;
    private V[] valores;
    private int capacidade;
    private int tamanho;

    @SuppressWarnings("unchecked")
    public HashSondagemLinear(int capacidade) {
        this.capacidade = capacidade;
        this.tamanho = 0;
        chaves = (K[]) new Object[capacidade];
        valores = (V[]) new Object[capacidade];
    }

    private int hash(K chave) {
        return (chave.hashCode() & 0x7FFFFFFF) % capacidade;
    }

    public void put(K chave, V valor) {
        if (tamanho >= capacidade / 2) {
            // Em uma implementação real, faríamos o Rehashing aqui (dobrar o array)
            System.out.println("Aviso: Tabela ficando cheia!");
        }

        int i;
        // O loop avança até encontrar um espaço vazio (null) ou a própria chave
        for (i = hash(chave); chaves[i] != null; i = (i + 1) % capacidade) {
            if (chaves[i].equals(chave)) {
                valores[i] = valor; // Atualiza se a chave já existir
                return;
            }
        }
        
        // Achou um espaço vazio (null)
        chaves[i] = chave;
        valores[i] = valor;
        tamanho++;
    }

    public V get(K chave) {
        // O loop busca a chave e para se encontrar um espaço vazio (null)
        for (int i = hash(chave); chaves[i] != null; i = (i + 1) % capacidade) {
            if (chaves[i].equals(chave)) {
                return valores[i]; // Achou!
            }
        }
        return null; // Não achou
    }
}