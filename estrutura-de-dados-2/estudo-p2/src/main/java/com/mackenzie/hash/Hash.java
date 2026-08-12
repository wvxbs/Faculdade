package com.mackenzie.hash;

/**
 * Uma implementação simples e fundamental de uma Tabela Hash
 * usando encadeamento (Lista Encadeada) para resolução de colisões.
 * Ótimo para entender o conceito para a P2.
 */
public class Hash<K, V> {
    // Tamanho padrão do array inicial da tabela
    private static final int DEFAULT_CAPACITY = 16;
    // O array que armazena as cabeças das listas encadeadas
    private Node<K, V>[] table;
    // Número de pares chave-valor na tabela
    private int size;

    /**
     * Nó para a lista encadeada.
     */
    private static class Node<K, V> {
        final K key;
        V value;
        Node<K, V> next;

        Node(K key, V value, Node<K, V> next) {
            this.key = key;
            this.value = value;
            this.next = next;
        }
    }

    /**
     * Construtor padrão. Cria uma tabela com capacidade padrão.
     */
    @SuppressWarnings("unchecked")
    public Hash() {
        table = (Node<K, V>[]) new Node[DEFAULT_CAPACITY];
        size = 0;
    }

    /**
     * Função hash fundamental. Calcula um índice no array com base no hashCode da chave.
     * k.hashCode() & 0x7FFFFFFF converte o hashCode para um número positivo.
     * % table.length distribui o hash dentro do tamanho do array.
     */
    private int hash(K k) {
        if (k == null) return 0;
        return (k.hashCode() & 0x7FFFFFFF) % table.length;
    }

    /**
     * Associa um valor a uma chave na tabela.
     * Se a chave já existir, o valor é atualizado.
     */
    public void put(K key, V value) {
        int index = hash(key);
        
        // Percorre a lista encadeada no índice calculado
        for (Node<K, V> x = table[index]; x != null; x = x.next) {
            // Se a chave for encontrada, atualiza o valor
            if (key.equals(x.key)) {
                x.value = value;
                return;
            }
        }
        
        // Se a chave não for encontrada, insere um novo nó no INÍCIO da lista
        // (Isso é mais eficiente e fácil de implementar)
        table[index] = new Node<>(key, value, table[index]);
        size++;
    }

    /**
     * Retorna o valor associado à chave, ou null se a chave não estiver na tabela.
     */
    public V get(K key) {
        int index = hash(key);
        
        // Percorre a lista encadeada no índice calculado
        for (Node<K, V> x = table[index]; x != null; x = x.next) {
            // Se a chave for encontrada, retorna o valor
            if (key.equals(x.key)) {
                return x.value;
            }
        }
        return null; // Chave não encontrada
    }

    /**
     * Remove o par chave-valor da tabela associado à chave.
     */
    public void remove(K key) {
        int index = hash(key);
        Node<K, V> dummy = new Node<>(null, null, table[index]); // Nó auxiliar para simplificar a remoção
        Node<K, V> prev = dummy;
        
        // Percorre a lista encadeada
        while (prev.next != null) {
            if (key.equals(prev.next.key)) {
                // Chave encontrada, "pula" o nó para removê-lo
                prev.next = prev.next.next;
                size--;
                break;
            }
            prev = prev.next;
        }
        table[index] = dummy.next; // Atualiza o array com o início correto da lista
    }

    /**
     * Retorna o número de pares chave-valor na tabela.
     */
    public int size() {
        return size;
    }

    /**
     * Retorna true se a tabela estiver vazia.
     */
    public boolean isEmpty() {
        return size == 0;
    }
    
    // Método para teste rápido
    public static void main(String[] args) {
        Hash<String, Integer> map = new Hash<>();
        map.put("um", 1);
        map.put("dois", 2);
        map.put("três", 3);
        map.put("um", 100); // Testa a atualização de chave existente

        System.out.println("Tamanho: " + map.size()); // Esperado: 3
        System.out.println("Chave 'um': " + map.get("um")); // Esperado: 100
        System.out.println("Chave 'dois': " + map.get("dois")); // Esperado: 2

        map.remove("dois");
        System.out.println("Tamanho após remoção: " + map.size()); // Esperado: 2
        System.out.println("Chave 'dois' após remoção: " + map.get("dois")); // Esperado: null
    }
}