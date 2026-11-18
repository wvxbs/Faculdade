l1([90,32,10,3,2,1,1,2,3,17,25,7,6]).

selsort([],[]).
selsort(L, [A|Y]):-
	imen(L,Im),
	swap(1,Im,L,[A|As]),
	selsort(As,Y).

imen([A|As],R):- 
	imen(As,A,1,1,R).

imen([],_,_,Im,Im).

imen([A|As],M,I,_,R):-
	A < M,
	I2 is I+1,
	imen(As,A,I2,I2,R).

imen([_|X],M,I,Im,R):-
	I2 is I+1,
	imen(X,M,I2,Im,R).

swap(I,3,L,Resp):-
	peg(I,L,Ei),
	peg(J,L,Ej),
	poe(Ei,J,L,Lx),
	poe(Ej,I,Lx,Resp).

peg(1, [E|_],E).
peg(N, [_|X],R) :- 
	N2 is N-1, 
	peg(N2,X,R).

poe(E,1,[_|X],[E|X]).
poe(E,N,[A|X],[A|Y]) :- 
	N2 is N-1, 
	poe(E,N2,X,Y).