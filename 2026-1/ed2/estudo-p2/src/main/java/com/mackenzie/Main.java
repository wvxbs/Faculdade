package com.mackenzie;

// ======================================================
// IMPORTS DAS ESTRUTURAS PERSONALIZADAS
// ======================================================

import com.mackenzie.hash.Hash;
import com.mackenzie.hash.HashSondagemLinear;
import com.mackenzie.arvoreb.NoArvoreB;

// ======================================================
// IMPORTS DOS MAPAS NATIVOS
// ======================================================

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.TreeMap;
import java.util.Hashtable;
import java.util.concurrent.ConcurrentHashMap;

public class Main {

    public static void main(String[] args) {

        cabecalho();

        testarHashEncadeamento();

        testarHashSondagemLinear();

        testarEstruturaArvoreB();

        testarHashMap();

        testarLinkedHashMap();

        testarTreeMap();

        testarConcurrentHashMap();

        testarHashtable();

        resumoFinal();
    }

    // ======================================================
    // CABEÇALHO
    // ======================================================

    private static void cabecalho() {

        System.out.println("==================================================");
        System.out.println("🎓 REVISÃO COMPLETA P2 - ESTRUTURAS DE DADOS 🎓");
        System.out.println("==================================================");

        System.out.println("\nO objetivo desse programa é:");
        System.out.println("✔ visualizar TODAS as estruturas");
        System.out.println("✔ entender diferenças");
        System.out.println("✔ ver pegadinhas de prova");
        System.out.println("✔ decorar termos importantes");
        System.out.println("✔ entender COMO PENSAR\n");
    }

    // ======================================================
    // HASH COM ENCADEAMENTO
    // ======================================================

    private static void testarHashEncadeamento() {

        linha();

        System.out.println("### 1. HASH COM ENCADEAMENTO ###\n");

        System.out.println("TERMOS IMPORTANTES:");
        System.out.println("- Bucket");
        System.out.println("- Colisão");
        System.out.println("- Encadeamento");
        System.out.println("- Lista ligada");
        System.out.println("- Função hash\n");

        System.out.println("IDEIA:");
        System.out.println("Quando ocorre colisão,");
        System.out.println("os elementos ficam numa LISTA.\n");

        System.out.println("VISUAL:\n");

        System.out.println("Índice 4:");
        System.out.println("João -> Ana -> Carlos\n");

        Hash<String, String> tabela = new Hash<>();

        tabela.put("123", "Alice");
        tabela.put("456", "Bruno");
        tabela.put("789", "Carlos");

        System.out.println("Inserimos:");
        System.out.println("123 -> Alice");
        System.out.println("456 -> Bruno");
        System.out.println("789 -> Carlos\n");

        System.out.println("Buscando chave 456:");
        System.out.println("Resultado: " + tabela.get("456"));

        System.out.println("\nAtualizando chave 456...");

        tabela.put("456", "Bruno Silva");

        System.out.println("Nova busca:");
        System.out.println("456 -> " + tabela.get("456"));

        System.out.println("\nPEGADINHA:");
        System.out.println("CHAVES NÃO REPETEM.");
        System.out.println("put() sobrescreve o valor.\n");

        System.out.println("Removendo chave 123...");
        tabela.remove("123");

        System.out.println("Buscando removido:");
        System.out.println(tabela.get("123"));

        System.out.println("\nCOMPLEXIDADE:");
        System.out.println("Média -> O(1)");
        System.out.println("Pior caso -> O(n)");

        System.out.println("\nPEGADINHA DE PROVA:");
        System.out.println("Muitas colisões degradam");
        System.out.println("a performance.\n");

        System.out.println("JAVA MODERNO:");
        System.out.println("Após 8 colisões:");
        System.out.println("Lista -> Árvore Rubro-Negra");
        System.out.println("O(n) -> O(log n)");
    }

    // ======================================================
    // HASH COM SONDAGEM LINEAR
    // ======================================================

    private static void testarHashSondagemLinear() {

        linha();

        System.out.println("### 2. HASH COM SONDAGEM LINEAR ###\n");

        System.out.println("TERMOS IMPORTANTES:");
        System.out.println("- Endereçamento aberto");
        System.out.println("- Sondagem linear");
        System.out.println("- Overflow");
        System.out.println("- Fator de carga\n");

        System.out.println("IDEIA:");
        System.out.println("Se houver colisão,");
        System.out.println("procura a próxima posição livre.\n");

        System.out.println("VISUAL:\n");

        System.out.println("posição 4 ocupada");
        System.out.println("↓");
        System.out.println("vai para posição 5\n");

        HashSondagemLinear<Integer, String> tabela =
                new HashSondagemLinear<>(7);

        tabela.put(15, "Notebook");
        tabela.put(22, "Mouse");
        tabela.put(8, "Teclado");

        System.out.println("Inserimos:");
        System.out.println("15 -> Notebook");
        System.out.println("22 -> Mouse");
        System.out.println("8 -> Teclado\n");

        System.out.println("Buscando 22:");
        System.out.println(tabela.get(22));

        System.out.println("\nBuscando 8:");
        System.out.println(tabela.get(8));

        System.out.println("\nBuscando inexistente:");
        System.out.println(tabela.get(99));

        System.out.println("\nPEGADINHA:");
        System.out.println("Se a tabela encher:");
        System.out.println("→ OVERFLOW");

        System.out.println("\nFATOR DE CARGA:");
        System.out.println("quantidade elementos / tamanho");

        System.out.println("\nExemplo:");
        System.out.println("3 elementos / tabela 7");
        System.out.println("3/7 = 0.42");

        System.out.println("\nQuanto maior o fator:");
        System.out.println("mais colisões.");
    }

    // ======================================================
    // ÁRVORE B
    // ======================================================

    private static void testarEstruturaArvoreB() {

        linha();

        System.out.println("### 3. ÁRVORE B ###\n");

        System.out.println("TERMOS IMPORTANTES:");
        System.out.println("- Nó");
        System.out.println("- Ordem");
        System.out.println("- Balanceamento");
        System.out.println("- Divisão de nós");
        System.out.println("- Filho\n");

        System.out.println("IDEIA:");
        System.out.println("Árvore B mantém tudo");
        System.out.println("balanceado automaticamente.\n");

        int ordem = 3;

        NoArvoreB raiz =
                new NoArvoreB(ordem, true);

        System.out.println("Árvore criada!");
        System.out.println("Ordem: " + ordem);

        System.out.println("\nCapacidade máxima de filhos:");
        System.out.println(raiz.filhos.length);

        System.out.println("\nCapacidade máxima de chaves:");
        System.out.println(raiz.chaves.length);

        System.out.println("\nVisual:\n");

        System.out.println("             [30]");
        System.out.println("            /    \\");
        System.out.println("      [10 20]  [40 50]\n");

        System.out.println("PEGADINHA:");
        System.out.println("ORDEM NÃO é");
        System.out.println("quantidade de chaves.");

        System.out.println("\nOrdem 3:");
        System.out.println("máximo 3 filhos");
        System.out.println("máximo 2 chaves");

        System.out.println("\nMUITO COBRADO:");
        System.out.println("Árvore B é balanceada.");

        System.out.println("\nUSADA EM:");
        System.out.println("- Bancos");
        System.out.println("- Sistemas de arquivos");
        System.out.println("- Índices");
    }

    // ======================================================
    // HASHMAP
    // ======================================================

    private static void testarHashMap() {

        linha();

        System.out.println("### 4. HASHMAP ###\n");

        System.out.println("O MAIS COBRADO DA PROVA.\n");

        System.out.println("CARACTERÍSTICAS:");
        System.out.println("- Muito rápido");
        System.out.println("- NÃO mantém ordem");
        System.out.println("- Usa tabela hash");
        System.out.println("- Complexidade O(1)\n");

        Map<String, Integer> mapa =
                new HashMap<>();

        mapa.put("Carlos", 7);
        mapa.put("Ana", 10);
        mapa.put("Bruno", 8);
        mapa.put("Daniel", 9);

        System.out.println("Inserimos:");
        imprimirMapa(mapa);

        System.out.println("\nPEGADINHA:");
        System.out.println("A ordem pode mudar.");
        System.out.println("HashMap NÃO ordena.");

        System.out.println("\nBuscando Ana:");
        System.out.println(mapa.get("Ana"));

        System.out.println("\ncontainsKey(Ana):");
        System.out.println(mapa.containsKey("Ana"));

        System.out.println("\ncontainsKey(Pedro):");
        System.out.println(mapa.containsKey("Pedro"));

        System.out.println("\nAtualizando Bruno:");

        mapa.put("Bruno", 100);

        imprimirMapa(mapa);

        System.out.println("\nPEGADINHA:");
        System.out.println("put() sobrescreve.");

        System.out.println("\nNULL:");
        System.out.println("Aceita 1 chave null");
        System.out.println("Aceita vários valores null");
    }

    // ======================================================
    // LINKED HASH MAP
    // ======================================================

    private static void testarLinkedHashMap() {

        linha();

        System.out.println("### 5. LINKEDHASHMAP ###\n");

        System.out.println("CARACTERÍSTICAS:");
        System.out.println("- Mantém ordem de inserção");
        System.out.println("- Hash + Lista ligada");
        System.out.println("- O(1)\n");

        Map<String, Integer> mapa =
                new LinkedHashMap<>();

        mapa.put("Carlos", 1);
        mapa.put("Ana", 2);
        mapa.put("Bruno", 3);

        imprimirMapa(mapa);

        System.out.println("\nOBSERVE:");
        System.out.println("Carlos entrou primeiro");
        System.out.println("Ana entrou segundo");
        System.out.println("Bruno entrou terceiro");

        System.out.println("\nPEGADINHA:");
        System.out.println("NÃO é ordem alfabética.");
        System.out.println("É ordem de INSERÇÃO.");
    }

    // ======================================================
    // TREEMAP
    // ======================================================

    private static void testarTreeMap() {

        linha();

        System.out.println("### 6. TREEMAP ###\n");

        System.out.println("CARACTERÍSTICAS:");
        System.out.println("- Ordem automática");
        System.out.println("- Árvore Rubro-Negra");
        System.out.println("- O(log n)\n");

        Map<String, Integer> mapa =
                new TreeMap<>();

        System.out.println("Inserindo fora de ordem...\n");

        mapa.put("Carlos", 7);
        mapa.put("Ana", 10);
        mapa.put("Bruno", 8);

        imprimirMapa(mapa);

        System.out.println("\nOBSERVE:");
        System.out.println("TreeMap ordena sozinho.");

        System.out.println("\nPEGADINHA:");
        System.out.println("NÃO aceita null key.");

        System.out.println("\nEXEMPLO QUE DARIA ERRO:");
        System.out.println("mapa.put(null, 10)");

        System.out.println("\nUSAR QUANDO:");
        System.out.println("- ordem alfabética");
        System.out.println("- ordem crescente");
    }

    // ======================================================
    // CONCURRENT HASH MAP
    // ======================================================

    private static void testarConcurrentHashMap() {

        linha();

        System.out.println("### 7. CONCURRENTHASHMAP ###\n");

        System.out.println("CARACTERÍSTICAS:");
        System.out.println("- Thread-safe");
        System.out.println("- Alta performance");
        System.out.println("- Concorrência moderna\n");

        Map<String, Integer> mapa =
                new ConcurrentHashMap<>();

        mapa.put("Thread1", 100);
        mapa.put("Thread2", 200);

        imprimirMapa(mapa);

        System.out.println("\nPROBLEMA QUE ELE RESOLVE:");

        System.out.println("\nThread 1 escreve");
        System.out.println("Thread 2 remove");
        System.out.println("Thread 3 lê");

        System.out.println("\nSem proteção:");
        System.out.println("dados podem corromper.");

        System.out.println("\nPEGADINHA:");
        System.out.println("ConcurrentHashMap");
        System.out.println("é o substituto moderno");
        System.out.println("do Hashtable.");
    }

    // ======================================================
    // HASHTABLE
    // ======================================================

    private static void testarHashtable() {

        linha();

        System.out.println("### 8. HASHTABLE ###\n");

        System.out.println("CARACTERÍSTICAS:");
        System.out.println("- Estrutura antiga");
        System.out.println("- synchronized");
        System.out.println("- Thread-safe\n");

        Hashtable<String, Integer> tabela =
                new Hashtable<>();

        tabela.put("João", 10);
        tabela.put("Maria", 20);

        imprimirMapa(tabela);

        System.out.println("\nPEGADINHA MUITO COBRADA:");
        System.out.println("Hashtable NÃO aceita null.");

        System.out.println("\nERRADO:");
        System.out.println("tabela.put(null, 10)");

        System.out.println("\nERRADO:");
        System.out.println("tabela.put(\"João\", null)");

        System.out.println("\nPROBLEMA:");
        System.out.println("Muito sincronizado");
        System.out.println("→ mais lento.");
    }

    // ======================================================
    // IMPRIMIR MAPA
    // ======================================================

    private static void imprimirMapa(Map<String, Integer> mapa) {

        System.out.println("--------------------------------");

        for (Map.Entry<String, Integer> entrada :
                mapa.entrySet()) {

            System.out.println(
                    entrada.getKey()
                            + " -> "
                            + entrada.getValue()
            );
        }

        System.out.println("--------------------------------");
    }

    // ======================================================
    // LINHA VISUAL
    // ======================================================

    private static void linha() {

        System.out.println("\n==================================================");
    }

    // ======================================================
    // RESUMO FINAL
    // ======================================================

    private static void resumoFinal() {

        linha();

        System.out.println("RESUMO DEFINITIVO DA PROVA\n");

        System.out.println("HashMap:");
        System.out.println("rápido e bagunçado\n");

        System.out.println("TreeMap:");
        System.out.println("ordenado\n");

        System.out.println("LinkedHashMap:");
        System.out.println("ordem de inserção\n");

        System.out.println("ConcurrentHashMap:");
        System.out.println("threads modernas\n");

        System.out.println("Hashtable:");
        System.out.println("legado sincronizado\n");

        System.out.println("Hash Encadeamento:");
        System.out.println("colisão -> lista\n");

        System.out.println("Sondagem Linear:");
        System.out.println("colisão -> próxima posição\n");

        System.out.println("Árvore B:");
        System.out.println("balanceamento automático\n");

        System.out.println("==================================================");
        System.out.println("✅ FIM DA REVISÃO");
        System.out.println("==================================================");
    }
}