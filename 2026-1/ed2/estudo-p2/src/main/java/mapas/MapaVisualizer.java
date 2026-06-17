package com.mackenzie.maps;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.TreeMap;
import java.util.concurrent.ConcurrentHashMap;
import java.util.Hashtable;

public class MapaVisualizer {

    public static void testarTodosMapas() {

        System.out.println("### 4. COMPORTAMENTO DOS MAPAS NATIVOS DO JAVA ###\n");

        testarHashMap();
        testarLinkedHashMap();
        testarTreeMap();
        testarConcurrentHashMap();
        testarHashtable();
    }

    // ======================================================
    // HASHMAP
    // ======================================================

    private static void testarHashMap() {

        System.out.println("==================================================");
        System.out.println("HASHMAP");
        System.out.println("==================================================");

        System.out.println("-> Estrutura rápida");
        System.out.println("-> NÃO mantém ordem");
        System.out.println("-> Usa Tabela Hash\n");

        Map<String, Integer> notas = new HashMap<>();

        System.out.println("Inserindo elementos...");

        notas.put("Carlos", 7);
        notas.put("Ana", 10);
        notas.put("Bruno", 8);
        notas.put("Daniel", 9);

        imprimirMapa(notas);

        System.out.println("\nBuscando Ana:");
        System.out.println("Resultado: " + notas.get("Ana"));

        System.out.println("\nAtualizando Bruno...");
        notas.put("Bruno", 100);

        imprimirMapa(notas);

        System.out.println("\nContainsKey(Ana):");
        System.out.println(notas.containsKey("Ana"));

        System.out.println("\nRemovendo Daniel...");
        notas.remove("Daniel");

        imprimirMapa(notas);

        System.out.println("\nTamanho:");
        System.out.println(notas.size());

        System.out.println("\nComplexidade média:");
        System.out.println("put/get/remove -> O(1)\n");
    }

    // ======================================================
    // LINKED HASH MAP
    // ======================================================

    private static void testarLinkedHashMap() {

        System.out.println("==================================================");
        System.out.println("LINKEDHASHMAP");
        System.out.println("==================================================");

        System.out.println("-> Mantém ORDEM DE INSERÇÃO");
        System.out.println("-> Hash + Lista Ligada\n");

        Map<String, Integer> fila = new LinkedHashMap<>();

        fila.put("Carlos", 1);
        fila.put("Ana", 2);
        fila.put("Bruno", 3);
        fila.put("Daniel", 4);

        System.out.println("Ordem preservada:");

        imprimirMapa(fila);

        System.out.println("\nObserve:");
        System.out.println("Carlos entrou primeiro");
        System.out.println("Ana entrou segundo");
        System.out.println("A ordem é preservada.\n");
    }

    // ======================================================
    // TREE MAP
    // ======================================================

    private static void testarTreeMap() {

        System.out.println("==================================================");
        System.out.println("TREEMAP");
        System.out.println("==================================================");

        System.out.println("-> Mantém ordem ALFABÉTICA");
        System.out.println("-> Usa Árvore Rubro-Negra");
        System.out.println("-> Complexidade O(log n)\n");

        Map<String, Integer> alunos = new TreeMap<>();

        System.out.println("Inserindo fora de ordem...\n");

        alunos.put("Carlos", 7);
        alunos.put("Ana", 10);
        alunos.put("Bruno", 8);
        alunos.put("Daniel", 9);

        System.out.println("Resultado ordenado:");

        imprimirMapa(alunos);

        System.out.println("\nObserve:");
        System.out.println("Mesmo inserindo bagunçado,");
        System.out.println("o TreeMap organiza automaticamente.\n");
    }

    // ======================================================
    // CONCURRENT HASH MAP
    // ======================================================

    private static void testarConcurrentHashMap() {

        System.out.println("==================================================");
        System.out.println("CONCURRENTHASHMAP");
        System.out.println("==================================================");

        System.out.println("-> Seguro para múltiplas threads");
        System.out.println("-> Muito usado em servidores\n");

        Map<String, Integer> acessos =
                new ConcurrentHashMap<>();

        acessos.put("Usuário1", 10);
        acessos.put("Usuário2", 20);

        imprimirMapa(acessos);

        System.out.println("\nEstrutura thread-safe moderna.\n");
    }

    // ======================================================
    // HASHTABLE
    // ======================================================

    private static void testarHashtable() {

        System.out.println("==================================================");
        System.out.println("HASHTABLE");
        System.out.println("==================================================");

        System.out.println("-> Estrutura LEGADA");
        System.out.println("-> Métodos synchronized");
        System.out.println("-> Não aceita null\n");

        Hashtable<String, Integer> tabela =
                new Hashtable<>();

        tabela.put("João", 10);
        tabela.put("Maria", 20);

        imprimirMapa(tabela);

        System.out.println("\nHashtable é mais antiga");
        System.out.println("ConcurrentHashMap é preferido hoje.\n");
    }

    // ======================================================
    // MÉTODO AUXILIAR
    // ======================================================

    private static void imprimirMapa(Map<String, Integer> mapa) {

        System.out.println("----------------------------------");

        for (Map.Entry<String, Integer> entrada : mapa.entrySet()) {

            System.out.println(
                    entrada.getKey()
                            + " -> "
                            + entrada.getValue()
            );
        }

        System.out.println("----------------------------------");
    }
}