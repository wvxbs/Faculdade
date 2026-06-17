
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













