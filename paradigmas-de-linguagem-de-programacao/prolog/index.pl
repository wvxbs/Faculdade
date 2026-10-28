s2l([], L, L).
s2l(L, [], L).
s2l([A | As], [B | Bs], [C | Cs]):-
	C is A + B,
	s2l(As, Bs, Cs).

membro(E, [E | _]).
membro(E, [_ | X]):-
	membro(E, X).

tri([], []).
tri([A | As], [A, A, A | X]):-
	tri(As, X).

poselt(E, L, Pos):- poselt(E, L, 1, Pos).
poselt(E, [E | _], I, I).
poselt(E, [_ |X], I, R):- 
	I2 is I + 1,
	poselt(E, X, I2, R).

swap(I, J, L, R):-
	pegarNElemento(I, L, Ei),
	pegarNElemento(J, L, Ej),
	porElemento(Ei, J, L, Lx).
	porElemento(Ej, I, Lx, R).

porElemento(E, 1, [_|X], [E|X]).
porElemento(E, N, [A|As], [A|X]):-
	N2 is N-1, 
	porElemento(E, N2, As, X).

pegarNElemento(1, [A |_], A].
pegarNElemento(N, [_ | X], R) :- 
	N2 is N-1,
	pegarNElemento(N2, X, R).


deletaDuplicadoEmSequencia([], []).
deletaDuplicadoEmSequencia([A, A | As], [A|Y]):-
	deletaDuplicadoEmSequencia([A|As], [A|Y]).
deletaDuplicadoEmSequencia([A|As], [A|Y]).

menorDaLista([A|X], R):- 
	menorDaLista(X, A, R).

menorDaLista([], Ac, Ac).

menorDaLista([A|X], M, R) :- 
	A < M, 
	menorDaLista(X, A, R).
menorDaLista([_|X], M, R) :- 
	menorDaLista(X, M, R).
