# Revisao de Prolog para a prova

Este documento acompanha o arquivo `revisao_prolog_prova.pl`.

Use assim no SWI-Prolog:

```prolog
?- [revisao_prolog_prova].
```

A ideia principal: em Prolog voce descreve relacoes. Em vez de escrever um `for`, voce costuma escrever um caso base e uma regra recursiva.

## Padrao mental de listas

```prolog
[A|As]
```

Explicacao:

`A` e o primeiro elemento da lista. `As` e o resto.

Exemplo:

```prolog
[7,1,3] = [A|As].
```

Resultado:

```prolog
A = 7,
As = [1,3].
```

Esse e o equivalente mental de:

```c
A = lista[0];
As = lista[1...];
```

## Lista de exemplo

```prolog
lista_exemplo([7,1,3,3,9,2,1,5,3,0]).
```

Explicacao:

Esse predicado so guarda uma lista pronta para testes. Ele permite fazer consultas sem redigitar a lista toda.

Exemplo:

```prolog
?- lista_exemplo(L).
```

## Membro

```prolog
membro(E, [E|_]).
membro(E, [_|As]) :-
    membro(E, As).
```

Explicacao:

A primeira regra diz: `E` e membro se ele esta na cabeca da lista.

A segunda regra diz: se ele nao esta necessariamente na cabeca, ignore a cabeca e procure no resto `As`.

O `_` significa "nao me importo com esse valor".

Exemplo:

```prolog
?- membro(3, [7,1,3]).
true.
```

## Concatenar listas

```prolog
concatena([], L, L).
concatena([A|As], L, [A|R]) :-
    concatena(As, L, R).
```

Explicacao:

Concatenar lista vazia com `L` da `L`.

No caso recursivo, a cabeca `A` da primeira lista tambem sera a cabeca do resultado. Depois o Prolog concatena o resto `As` com `L`.

Exemplo:

```prolog
?- concatena([1,2], [3,4], R).
R = [1,2,3,4].
```

## Comprimento

```prolog
comprimento([], 0).
comprimento([_|As], R) :-
    comprimento(As, T),
    R is T + 1.
```

Explicacao:

Lista vazia tem tamanho `0`.

Para uma lista nao vazia, calcula o tamanho do resto `As` e soma `1`.

Importante: `is` avalia conta matematica. Sem `is`, Prolog nao calcula.

Exemplo:

```prolog
?- comprimento([a,b,c], R).
R = 3.
```

## Soma

```prolog
soma([], 0).
soma([A|As], R) :-
    soma(As, T),
    R is A + T.
```

Explicacao:

Lista vazia soma `0`.

Em uma lista `[A|As]`, soma primeiro o resto e depois adiciona a cabeca `A`.

Exemplo:

```prolog
?- soma([10,20,5], R).
R = 35.
```

## Maior elemento

```prolog
maior([A|As], R) :-
    maior(As, A, R).

maior([], M, M).
maior([A|As], M, R) :-
    A > M,
    maior(As, A, R).
maior([A|As], M, R) :-
    A =< M,
    maior(As, M, R).
```

Explicacao:

A versao principal pega o primeiro elemento `A` e usa como "maior ate agora".

Depois a auxiliar `maior(Lista, MaiorAtual, Resultado)` percorre o resto:

- se `A > M`, atualiza o maior;
- se `A =< M`, mantem o maior atual;
- quando a lista acaba, o maior atual e a resposta.

Exemplo:

```prolog
?- maior([7,1,3,9,2], R).
R = 9.
```

## Menor elemento

```prolog
menor([A|As], R) :-
    menor(As, A, R).

menor([], M, M).
menor([A|As], M, R) :-
    A < M,
    menor(As, A, R).
menor([A|As], M, R) :-
    A >= M,
    menor(As, M, R).
```

Explicacao:

E o mesmo padrao do maior elemento, mas invertendo as comparacoes.

O predicado carrega o menor valor visto ate agora.

Exemplo:

```prolog
?- menor([7,1,3,9,2], R).
R = 1.
```

## Inverter lista

```prolog
inverte(L, R) :-
    inverte(L, [], R).

inverte([], Acc, Acc).
inverte([A|As], Acc, R) :-
    inverte(As, [A|Acc], R).
```

Explicacao:

`Acc` e o acumulador. Ele guarda a lista invertida ate o momento.

Cada elemento `A` e colocado na frente do acumulador:

```prolog
[A|Acc]
```

Exemplo mental:

```prolog
inverte([1,2,3], [], R)
inverte([2,3], [1], R)
inverte([3], [2,1], R)
inverte([], [3,2,1], R)
```

Exemplo:

```prolog
?- inverte([1,2,3], R).
R = [3,2,1].
```

## Contar ocorrencias

```prolog
conta(_, [], 0).
conta(E, [E|As], R) :-
    conta(E, As, T),
    R is T + 1.
conta(E, [A|As], R) :-
    E \= A,
    conta(E, As, R).
```

Explicacao:

Se a lista acabou, a quantidade e `0`.

Se a cabeca e o elemento procurado, conta no resto e soma `1`.

Se a cabeca e diferente, ignora a cabeca e continua no resto.

`E \= A` significa que `E` e `A` nao unificam, ou seja, sao diferentes nesse contexto.

Exemplo:

```prolog
?- conta(3, [7,3,1,3,3], R).
R = 3.
```

## Elemento mais recorrente

```prolog
mais_recorrente([A|As], Elem) :-
    conta(A, [A|As], N),
    mais_recorrente(As, A, N, Elem).

mais_recorrente([], ElemAtual, _, ElemAtual).
mais_recorrente([A|As], _ElemAtual, NAtual, Elem) :-
    conta(A, [A|As], N),
    N > NAtual,
    mais_recorrente(As, A, N, Elem).
mais_recorrente([A|As], ElemAtual, NAtual, Elem) :-
    conta(A, [A|As], N),
    N =< NAtual,
    mais_recorrente(As, ElemAtual, NAtual, Elem).
```

Explicacao:

O predicado guarda duas coisas:

- o elemento campeao ate agora;
- a frequencia desse elemento.

Para cada novo elemento `A`, ele chama `conta` para descobrir quantas vezes `A` aparece. Se a frequencia for maior que a atual, troca o campeao.

Nao e a versao mais eficiente, mas e boa para entender e para prova.

Exemplo:

```prolog
?- mais_recorrente([7,1,3,3,9,2,1,5,3,0], R).
R = 3.
```

## Remover uma ocorrencia

```prolog
remove_um(E, [E|As], As).
remove_um(E, [A|As], [A|R]) :-
    E \= A,
    remove_um(E, As, R).
```

Explicacao:

Se o elemento a remover esta na cabeca, o resultado e o resto da lista.

Se a cabeca e diferente, mantem a cabeca `A` no resultado e tenta remover no resto.

Exemplo:

```prolog
?- remove_um(3, [7,3,1,3], R).
R = [7,1,3].
```

## Selection sort

```prolog
selection([], []).
selection(L, [M|R]) :-
    menor(L, M),
    remove_um(M, L, L2),
    selection(L2, R).
```

Explicacao:

Selection sort faz isto:

1. acha o menor elemento da lista;
2. coloca esse menor na frente;
3. remove uma ocorrencia dele da lista original;
4. ordena o resto.

Em Prolog, `[M|R]` significa que o resultado comeca com o menor `M`, e o restante ordenado e `R`.

Exemplo:

```prolog
?- selection([7,1,3,2], R).
R = [1,2,3,7].
```

## Insertion sort

```prolog
insertion([], []).
insertion([A|As], R) :-
    insertion(As, Ord),
    insere_ord(A, Ord, R).

insere_ord(E, [], [E]).
insere_ord(E, [A|As], [E,A|As]) :-
    E =< A.
insere_ord(E, [A|As], [A|R]) :-
    E > A,
    insere_ord(E, As, R).
```

Explicacao:

Insertion sort ordena o resto da lista e depois insere a cabeca no lugar certo.

`insere_ord` tem tres casos:

- inserir em lista vazia;
- se `E =< A`, `E` entra antes de `A`;
- se `E > A`, mantem `A` e tenta inserir `E` no resto.

Exemplo:

```prolog
?- insertion([7,1,3,2], R).
R = [1,2,3,7].
```

## Bubble sort

```prolog
bubble([], []).
bubble(L, R) :-
    bubble_passes(L, L, R).

bubble_passes([], Acc, Acc).
bubble_passes([_|As], Acc, R) :-
    leva_maior(Acc, Acc2),
    bubble_passes(As, Acc2, R).

leva_maior([], []).
leva_maior([A], [A]).
leva_maior([A,B|As], [B|R]) :-
    B < A,
    leva_maior([A|As], R).
leva_maior([A,B|As], [A|R]) :-
    A =< B,
    leva_maior([B|As], R).
```

Explicacao:

Bubble sort compara vizinhos e empurra o maior para o final.

`leva_maior` faz uma passada:

- se `B < A`, os dois estao fora de ordem, entao troca;
- se `A =< B`, mantem `A` antes de `B`.

`bubble_passes` repete essa passada varias vezes.

Exemplo:

```prolog
?- bubble([7,1,3,2], R).
R = [1,2,3,7].
```

## Quick sort

```prolog
quick([], []).
quick([P|As], R) :-
    particiona(P, As, Menores, Maiores),
    quick(Menores, RMenores),
    quick(Maiores, RMaiores),
    append(RMenores, [P|RMaiores], R).

particiona(_, [], [], []).
particiona(P, [A|As], [A|Menores], Maiores) :-
    A =< P,
    particiona(P, As, Menores, Maiores).
particiona(P, [A|As], Menores, [A|Maiores]) :-
    A > P,
    particiona(P, As, Menores, Maiores).
```

Explicacao:

Quick sort escolhe um pivo `P`, separa a lista em dois lados, ordena os lados e junta:

```prolog
menores + [pivo] + maiores
```

`particiona` coloca elementos `=< P` na lista `Menores`, e elementos `> P` na lista `Maiores`.

Exemplo:

```prolog
?- quick([7,1,3,2], R).
R = [1,2,3,7].
```

## Merge sort

```prolog
merge_sort([], []).
merge_sort([A], [A]).
merge_sort(L, R) :-
    divide(L, L1, L2),
    merge_sort(L1, R1),
    merge_sort(L2, R2),
    intercala(R1, R2, R).

divide([], [], []).
divide([A], [A], []).
divide([A,B|As], [A|R1], [B|R2]) :-
    divide(As, R1, R2).

intercala([], L, L).
intercala(L, [], L).
intercala([A|As], [B|Bs], [A|R]) :-
    A =< B,
    intercala(As, [B|Bs], R).
intercala([A|As], [B|Bs], [B|R]) :-
    A > B,
    intercala([A|As], Bs, R).
```

Explicacao:

Merge sort:

1. divide a lista em duas;
2. ordena cada metade;
3. intercala as duas metades ordenadas.

`divide` alterna elementos entre as duas listas.

`intercala` compara as cabecas das duas listas. A menor cabeca vai primeiro no resultado.

Exemplo:

```prolog
?- merge_sort([7,1,3,2], R).
R = [1,2,3,7].
```

## Run-length encoding

```prolog
rle([], []).
rle([E|Es], R) :-
    rle(Es, E, 1, R).

rle([], E, N, [(E,N)]).
rle([E|As], E, N, R) :-
    N2 is N + 1,
    rle(As, E, N2, R).
rle([A|As], E, N, [(E,N)|R]) :-
    A \= E,
    rle(As, A, 1, R).
```

Explicacao:

RLE compacta sequencias repetidas.

Exemplo:

```prolog
[a,a,a,b,b,c]
```

vira:

```prolog
[(a,3),(b,2),(c,1)]
```

O predicado guarda:

- o elemento atual `E`;
- a contagem atual `N`;
- o resto da lista a processar.

Se o proximo elemento tambem e `E`, aumenta a contagem. Se muda, fecha o par `(E,N)` e comeca outro.

Exemplo:

```prolog
?- rle([a,a,a,b,b,c], R).
R = [(a,3),(b,2),(c,1)].
```

## Run-length decoding

```prolog
rld([], []).
rld([(E,N)|As], R) :-
    repete(E, N, L),
    rld(As, T),
    append(L, T, R).

repete(_, 0, []).
repete(E, N, [E|R]) :-
    N > 0,
    N2 is N - 1,
    repete(E, N2, R).
```

Explicacao:

`rld` faz o caminho inverso do `rle`.

Para cada par `(E,N)`, o predicado `repete` cria uma lista com `E` repetido `N` vezes. Depois `append` junta essa lista com a decodificacao do resto.

Exemplo:

```prolog
?- rld([(a,3),(b,2),(c,1)], R).
R = [a,a,a,b,b,c].
```

## Huffman

O projeto de Huffman pedido pelo professor tem uma ideia central: transformar um texto em frequencias, construir uma arvore e usar essa arvore para gerar codigos menores para caracteres mais frequentes.

O fluxo geral e:

```text
texto -> lista de caracteres -> ordenacao -> frequencias -> arvore -> tabela de codigos -> texto codificado
```

O pedaco que conversa diretamente com o codigo deste arquivo e a parte de frequencias.

Se voce tiver uma lista de caracteres ja agrupada:

```prolog
[a,a,a,b,b,c]
```

o `rle` gera:

```prolog
[(a,3),(b,2),(c,1)]
```

Isso e praticamente uma tabela de frequencia.

Para Huffman de verdade, antes do `rle` voce normalmente ordenaria os caracteres para que iguais fiquem juntos:

```prolog
quick([b,a,c,a,b,a], Ordenado),
rle(Ordenado, Frequencias).
```

Resultado esperado:

```prolog
Ordenado = [a,a,a,b,b,c],
Frequencias = [(a,3),(b,2),(c,1)].
```

Depois disso, a ideia da arvore de Huffman e:

1. ordenar os simbolos por frequencia;
2. pegar os dois menores;
3. juntar em uma arvore nova cuja frequencia e a soma;
4. recolocar essa arvore na lista;
5. repetir ate sobrar uma arvore.

Representacao possivel em Prolog:

```prolog
folha(a, 3)
folha(b, 2)
folha(c, 1)
no(3, folha(c,1), folha(b,2))
```

Aqui `folha(Simbolo, Frequencia)` representa um caractere. `no(FrequenciaTotal, Esquerda, Direita)` representa um galho da arvore.

Por que isso combina com Prolog? Porque uma arvore e naturalmente definida por recursao:

```prolog
codigo(folha(S, _), S, []).
codigo(no(_, Esq, _), S, [0|R]) :-
    codigo(Esq, S, R).
codigo(no(_, _, Dir), S, [1|R]) :-
    codigo(Dir, S, R).
```

Leitura:

- se chegou na folha do simbolo, o codigo acabou;
- se foi para a esquerda, adiciona `0`;
- se foi para a direita, adiciona `1`.

Nao precisa decorar uma implementacao completa de Huffman para a prova se o foco for listas, mas entenda que Huffman usa os mesmos blocos: ordenar, contar, trabalhar com pares e recursao.

## POO vs Prolog

POO e Prolog pensam de jeitos bem diferentes.

Em POO, voce modela o mundo com objetos que tem estado e comportamento.

Exemplo em Java:

```java
class Pessoa {
    private String nome;

    public Pessoa(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return nome;
    }
}
```

Aqui existe um objeto com estado interno: `nome`.

Em Prolog, voce modela fatos e regras:

```prolog
pessoa(ana).
pessoa(bruno).
mae(ana, bruno).
```

Voce nao chama metodo em objeto. Voce pergunta se uma relacao e verdadeira:

```prolog
?- mae(ana, bruno).
true.
```

Comparacao rapida:

| Ideia | POO/Java | Prolog |
|---|---|---|
| Unidade principal | classe/objeto | fato/regra |
| Foco | como objetos mudam e se comportam | quais relacoes sao verdadeiras |
| Controle | `if`, `for`, `while`, chamada de metodo | unificacao, recursao, backtracking |
| Estado | comum, via atributos | evitado; prefere relacoes imutaveis |
| Exemplo de pergunta | `obj.metodo()` | `?- predicado(X).` |

Exemplo com ordenacao:

Em Java ou C, voce pensa:

```text
percorra a lista, compare elementos, troque posicoes
```

Em Prolog, voce pensa:

```text
uma lista ordenada e formada pelo menor elemento na frente e pelo resto ordenado
```

Por isso `selection` fica assim:

```prolog
selection([], []).
selection(L, [M|R]) :-
    menor(L, M),
    remove_um(M, L, L2),
    selection(L2, R).
```

Em POO, Huffman provavelmente viraria classes:

```text
Node
Leaf
HuffmanTree
Encoder
```

Em Prolog, Huffman vira termos e regras:

```prolog
folha(a, 3).
no(5, folha(a,3), folha(b,2)).
```

Resumo para fixar:

POO pergunta: "quem e o objeto e que metodo ele executa?"

Prolog pergunta: "que relacao precisa ser verdadeira para essa resposta existir?"

