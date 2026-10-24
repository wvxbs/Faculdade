processar_arquivo(NomeArquivo, ListaFinal) :- 
    open(NomeArquivo, read, Stream),
    ler_conteudo(Stream, ListaFinal),
    close(Stream).

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