/*
   EP2 - Codificacao de Huffman em Prolog
   Aluno: Gabriel Ferreira
   RA: 10442043
*/

:- initialization(main, main).

main :-
    current_prolog_flag(huffman_modo_lote, true),
    !.
main :-
    codificar_arquivo('in', 'out').

codificar_arquivo(Entrada, Saida) :-
    processar_arquivo(Entrada, Texto),
    frequencias(Texto, Frequencias),
    arvore_huffman(Frequencias, Arvore),
    tabela_codigos(Arvore, Tabela),
    codificar_texto(Texto, Tabela, Bits),
    escrever_bits(Saida, Bits).

processar_arquivo(NomeArquivo, ListaFinal) :-
    setup_call_cleanup(
        open(NomeArquivo, read, Stream),
        ler_conteudo(Stream, ListaFinal),
        close(Stream)
    ).

ler_conteudo(Stream, Lista) :-
    get_char(Stream, C),
    processa_char(C, Stream, Lista).

processa_char(end_of_file, _, []) :- !.
processa_char(C, Stream, [C | Resto]) :-
    eh_valido(C),
    !,
    ler_conteudo(Stream, Resto).
processa_char(_, Stream, Resto) :-
    ler_conteudo(Stream, Resto).

eh_valido(C) :- C @>= 'a', C @=< 'z'.
eh_valido(C) :- C @>= 'A', C @=< 'Z'.
eh_valido(C) :- C @>= '0', C @=< '9'.

frequencias(Texto, Frequencias) :-
    msort(Texto, Ordenado),
    contar_ordenado(Ordenado, Frequencias).

contar_ordenado([], []).
contar_ordenado([C | Cs], [freq(C, N) | Frequencias]) :-
    contar_iguais(Cs, C, 1, N, Resto),
    contar_ordenado(Resto, Frequencias).

contar_iguais([C | Cs], C, Acumulado, N, Resto) :-
    !,
    Proximo is Acumulado + 1,
    contar_iguais(Cs, C, Proximo, N, Resto).
contar_iguais(Resto, _, N, N, Resto).

arvore_huffman([], vazia) :- !.
arvore_huffman(Frequencias, Arvore) :-
    frequencias_para_fila(Frequencias, Fila),
    construir_arvore(Fila, Arvore).

frequencias_para_fila(Frequencias, FilaOrdenada) :-
    maplist(freq_para_no, Frequencias, Fila),
    predsort(comparar_nos, Fila, FilaOrdenada).

freq_para_no(freq(C, N), no(N, folha(C))).

construir_arvore([no(_, Arvore)], Arvore).
construir_arvore([no(P1, A1), no(P2, A2) | Resto], Arvore) :-
    Peso is P1 + P2,
    inserir_ordenado(no(Peso, galho(A1, A2)), Resto, NovaFila),
    construir_arvore(NovaFila, Arvore).

inserir_ordenado(No, [], [No]).
inserir_ordenado(No, [Atual | Resto], [No, Atual | Resto]) :-
    comparar_nos(<, No, Atual),
    !.
inserir_ordenado(No, [Atual | Resto], [Atual | NovaFila]) :-
    inserir_ordenado(No, Resto, NovaFila).

comparar_nos(Ordem, no(PesoA, ArvoreA), no(PesoB, ArvoreB)) :-
    compare(ComparacaoPeso, PesoA, PesoB),
    desempatar_nos(ComparacaoPeso, ArvoreA, ArvoreB, Ordem).

desempatar_nos(=, ArvoreA, ArvoreB, Ordem) :-
    !,
    compare(Ordem, ArvoreA, ArvoreB).
desempatar_nos(Ordem, _, _, Ordem).

tabela_codigos(vazia, []) :- !.
tabela_codigos(folha(C), [codigo(C, [0])]) :- !.
tabela_codigos(Arvore, Tabela) :-
    gerar_codigos(Arvore, [], Tabela).

gerar_codigos(folha(C), PrefixoInvertido, [codigo(C, Codigo)]) :-
    reverse(PrefixoInvertido, Codigo).
gerar_codigos(galho(Esq, Dir), Prefixo, Tabela) :-
    gerar_codigos(Esq, [0 | Prefixo], TabelaEsq),
    gerar_codigos(Dir, [1 | Prefixo], TabelaDir),
    append(TabelaEsq, TabelaDir, Tabela).

codificar_texto([], _, []).
codificar_texto([C | Cs], Tabela, Bits) :-
    memberchk(codigo(C, Codigo), Tabela),
    codificar_texto(Cs, Tabela, RestoBits),
    append(Codigo, RestoBits, Bits).

escrever_bits(Saida, Bits) :-
    setup_call_cleanup(
        open(Saida, write, Stream),
        escrever_bits_stream(Bits, Stream),
        close(Stream)
    ).

escrever_bits_stream([], _).
escrever_bits_stream([Bit | Bits], Stream) :-
    write(Stream, Bit),
    escrever_bits_stream(Bits, Stream).
