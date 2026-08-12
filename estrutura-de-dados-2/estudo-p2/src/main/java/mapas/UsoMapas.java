package com.mackenzie.mapas;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.TreeMap;

public class UsoMapasJava {
    
    public static void main(String[] args) {
        System.out.println("=== 1. HASHMAP (Sem Ordem Garantida) ===");
        // Rápido, mas bagunça a ordem de entrada.
        Map<String, Integer> hashMap = new HashMap<>();
        inserirDados(hashMap);
        imprimirMapa(hashMap);

        System.out.println("\n=== 2. LINKEDHASHMAP (Ordem de Inserção) ===");
        // Mantém exatamente a ordem em que você chamou o "put".
        Map<String, Integer> linkedMap = new LinkedHashMap<>();
        inserirDados(linkedMap);
        imprimirMapa(linkedMap);

        System.out.println("\n=== 3. TREEMAP (Ordem Natural / Alfabética) ===");
        // Ordena as chaves automaticamente (A-Z ou 0-9).
        Map<String, Integer> treeMap = new TreeMap<>();
        inserirDados(treeMap);
        imprimirMapa(treeMap);
    }

    private static void inserirDados(Map<String, Integer> mapa) {
        mapa.put("Zebra", 100);
        mapa.put("Cachorro", 50);
        mapa.put("Abelha", 10);
        mapa.put("Gato", 30);
    }

    private static void imprimirMapa(Map<String, Integer> mapa) {
        // Como iterar sobre um Mapa (pode cair na prova!)
        for (Map.Entry<String, Integer> entrada : mapa.entrySet()) {
            System.out.println(entrada.getKey() + " -> " + entrada.getValue());
        }
    }
}