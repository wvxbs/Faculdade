    l0([a, b, c, a, b, c, a, y, y, y, d, a, d, x, x, x, b]).
    l1([a, b, c, a, b, c, a]).

    frequenciaMaisFrequente(L, R) :-
        quantif(L, Lq),
        mergeSort(Lq, Lord),
        agrupa(Lord,Grupos),
        maiorTamanho(Grupos, [(_,R)|_]).

    quantos(_, [], 0).
    quantos(E, [E|X], N) :-
        quantos(E, X, T),
        N is T + 1.
    quantos(E, [_|X], N) :-
        quantos(E, X, N).

    maisAparece([A|As], R) :-
        quantos(A, [A|As], N),
        maisAparece(As, [A|As], A, N, R).
    maisAparece([], _, E, _, E).
    maisAparece([A|As], Lac, N, R) :-
        quantos(A, Lac, M),
        M > N,
        maisAparece(As, Lac, A, M, R).
    maisAparece([_|As], Lac, N, R) :-
        maisAparece(As, Lac, N, R).

    split([], [], []).
    split([E], [E], []).
    split([A, B|X], [A|As], [B|Bs]) :-
        split(X, As, Bs).

    agrupa([],[]).
    agrupa([D|Ds], R) :- 
        agrupa(Ds, [D], R).
    agrupa([], Lac, [Lac]).
    agrupa([(A,N)|Ds],[(B,N)|Lac],R):-
        !,
        agrupa(Ds,[(A,N),(B,N)|Lac],R).
    agrupa([(A,N)|Ds],Lac,[Lac|R]):-
        agrupa(Ds,[(A,N)],R).

    deletaDuplicados([], []).
    deletaDuplicados([A|As], R) :-
        member(A, As),
        !,
        deletaDuplicados(As, R).
    deletaDuplicados([A|As], [A|R]) :-
        deletaDuplicados(As, R).

    quantif(L, R) :-
        deletaDuplicados(L, X),
        quantif(X,L,R).
    quantif([],_,[]).
    quantif([A|As], Lor, [(A, N)|R]) :-
        quantos(A, Lor, N),
        quantif(As, Lor, R).

    intercala([], R, R).
    intercala(R, [], R).
    intercala([(A, M)|X], [(B, N)|Y], [(A, M)|Z]) :-
        M =< N,
        intercala(X, [(B, N)|Y], Z).
    intercala([(A, M)|X], [(B, N)|Y], [(B, N)|Z]) :-
        M > N,
        intercala([(A, M)|X], Y, Z).

    mergeSort([], []).
    mergeSort([A], [A]).
    mergeSort([A,B|L], R) :-
        split([A,B|L], L1, L2),
        mergeSort(L1, R1),
        mergeSort(L2, R2),
        intercala(R1, R2, R).

    maiorTamanho([L|Ls], R) :-
        tamanho(L, N),
        maiorTamanho(Ls,L,N,R).

    maiorTamanho([],Melhor,_,Melhor).
    maiorTamanho([L|Ls],Atual,NAtual, R):-
        tamanho(L,N),
        (N > NAtual ->
            maiorTamanho(Ls,L,N,R)
        ;
            maiorTamanho(Ls, Atual, NAtual, R)
        ).

    tamanho([], 0).
    tamanho([_|Ls], N) :-
        tamanho(Ls, M),
        N is M + 1.