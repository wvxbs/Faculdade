/*
 * Fatorial de 0 é 1. Nunca pense: a cláusula de cima evita que a de baixo
 * rode. Precisamos especificar que o N tem que ser maior que 0 para evitar
 * não terminação.
 */
fatorial(0, 1).
fatorial(N, F) :-
	N > 0,
	N1 is N - 1,
	fatorial(N1, F1),
	F is N * F1.


tamanho([], 0).
tamanho([_|R], T) :-
	tamanho(R, T1),
	T is T1 + 1.


soma([], 0).
soma([E|R], S) :-
	soma(R, S1),
	S is E + S1.


listas_soma(L1, [], L1) :- !.
listas_soma([], L2, L2) :- !.
listas_soma([E1|R1], [E2|R2], [S|R]) :-
	S is E1 + E2,
	listas_soma(R1, R2, R).


membro(E, [E|_]).
membro(E, [_|R]) :-
	membro(E, R).


interseccao([], _, []).
interseccao([E|R], L, I) :-
	membro(E, L), !,
	I = [E|I1],
	interseccao(R, L, I1).
interseccao([_|R], L, I) :-
	interseccao(R, L, I).


mesmo_tamanho([], []).
mesmo_tamanho([_|A], [_|B]) :-
	mesmo_tamanho(A, B).


duplica([], []).
duplica([A|As], [A,A|X]) :-
	duplica(As, X).


deletar_primeiro(_, [], []).
deletar_primeiro(E, [E|X], X) :- !.
deletar_primeiro(E, [A|As], [A|X]) :-
	E \= A,
	deletar_primeiro(E, As, X).


deletar_todos(_, [], []).
deletar_todos(E, [E|X], Xs) :-
	deletar_todos(E, X, Xs).
deletar_todos(E, [A|As], [A|X]) :-
	E  \= A,
	deletar_todos(E, As, X).


deletar_duplicados([], []).
deletar_duplicados([E|Es], [E|R]) :-
	deletar_todos(E, Es, L1),
	deletar_duplicados(L1, R).


menor([E], E).
menor([E|Es], M) :-
	menor(Es, M1),
	( E < M1 -> M = E
	; 	    M = M1
	).


menores(_, [], []).
menores(E, [A|As], R) :-
	A < E, !,
	R = [A|Rs],
	menores(E, As, Rs).
menores(E, [_|As], R) :-
	menores(E, As, R).


nprimeiros(0, _, []) :- !.
nprimeiros(N, [], []) :-
	N > 0, !.
nprimeiros(N, [A|As], [A|X]) :-
	N > 0,
	N1 is N - 1,
	nprimeiros(N1, As, X).

onde(E, [E|_], N) :- !, N = 1.
onde(E, [_|Es], N) :- onde(E, Es, N1), N is N1 + 1.


ate(_, [], []).
ate(E, [E|_], R) :- !, R = [E].
ate(E, [A|As], [A|R]) :- ate(E, As, R), !.


apos(_, [], []).
apos(E, [E|X], R) :- !, R = X.
apos(E, [_|X], R) :- apos(E, X, R).

natural(0, []) :- !.
natural(N, R) :-
	N > 0,
	N1 is N - 1,
	natural(N1, R1),
	append(R1, [N1], R).


l1([90,7,1,2,3,3,2,1,54,0,32,43,4,5,27]).

lrle([a,a,a,a,a,b,b,b,b,c,c,c,d,a,a,a,a,a,a]).

lrld([(a,5),(b,4),(c,3),(d,1),(a,6)]).


/* selsort */


selsort([],[]).
selsort(L,[A|R]) :-
    imen(L,Im),
    swap(1,Im,L,[A|Lnew]),
    selsort(Lnew,R).

swap(I,J,L,R) :-
    peg(I,L,Ei),
    peg(J,L,Ej),
    poe(Ei,J,L,Temp),
    poe(Ej,I,Temp,R).

peg(1,[A|_],A).
peg(N,[_|X],R) :- N2 is N-1, peg(N2,X,R).

poe(E,1,[_|X],[E|X]).
poe(E,N,[A|As],[A|X]) :- N2 is N-1, poe(E,N2,As,X).

imen([A|As],R) :- imen(As,A,1,1,R).

imen([],_,_,Im,Im).
imen([A|As],M,I,Im,R) :-
    A < M,
    I2 is I+1,
    imen(As,A,I2,I2,R).
imen([_|X],M,I,Im,R) :- I2 is I+1, imen(X,M,I2,Im,R).


/* bubble */

bubble([],[]).
bubble(L,R) :- bubble(L,L,R).

bubble([],Lac,Lac).
bubble([_|X],Lac,R) :- levmai(Lac,Lac2), bubble(X,Lac2,R).


levmai([],[]).
levmai([A],[A]).
levmai([A,B|X],[B|Y]) :- B < A, levmai([A|X],Y).
levmai([A|X],[A|Y]) :- levmai(X,Y).


/* insertion */

isort([],[]).
isort(L,R) :- isort(L,[],R).

isort([],Lac,Lac).
isort([A|As],Lac,R) :- insere(A,Lac,Lac2), isort(As,Lac2,R).


insere(E,[],[E]).
insere(E,[A|As],[E,A|As]) :- E =< A.
insere(E,[A|As],[A|X]) :- insere(E,As,X).


/* qsort */

qs([],[]).
qs([A],[A]).
qs([P|L],R) :-
    partit(P,L,Lmen,Lmai),
    qs(Lmen,Rmen),
    qs(Lmai,Rmai),
    append(Rmen,[P|Rmai],R).

partit(_,[],[],[]).
partit(P,[A|As],[A|X],Y) :- A =< P, partit(P,As,X,Y).
partit(P,[A|As],X,[A|Y]) :- partit(P,As,X,Y).


/* msort */

ms([],[]).
ms([A],[A]).
ms(L,R) :- split(L,L1,L2), ms(L1,R1), ms(L2,R2), inter(R1,R2,R).

inter([],L,L).
inter(L,[],L).
inter([A|As],[B|Bs],[A|X]) :- A =< B, inter(As,[B|Bs],X).
inter([A|As],[B|Bs],[B|X]) :- inter([A|As],Bs,X).

split([],[],[]).
split([A],[A],[]).
split([A,B|X],[A|As],[B|Bs]) :- split(X,As,Bs).


/* rle (run length encoding) */

rld([],[]).
rld([(E,N)|X],R) :- rpt(E,N,L), rld(X,T), append(L,T,R).

rpt(_,0,[]).
rpt(E,N,[E|X]) :- N2 is N-1, rpt(E,N2,X).



rle([],[]).
rle([E|Es],R) :- rle(Es,E,1,R).

rle([],E,N,[(E,N)]).
rle([E|X],E,N,R) :- N2 is N+1, rle(X,E,N2,R).
rle([A|As],E,N,[(E,N)|X]) :- rle(As,A,1,X).

