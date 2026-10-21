s2l([], L, L).
s2l(L, [], L).
s2l([A | As], [B | Bs], [C | Cs]):-
	C is A + B,
	s2l(As, Bs, Cs).

membro(E, [E | _]).
membro(E, [_ | X]):-
	membro(E, X).
