/*
   Revisao rapida de Prolog para prova.

   Como usar no SWI-Prolog:
   ?- [revisao_prolog_prova].
   ?- maior([7,1,3,9,2], R).
   ?- quick([7,1,3,9,2], R).
*/

lista_exemplo([7,1,3,3,9,2,1,5,3,0]).

/*
   Padrao mental:
   [A|As] = A eh o primeiro elemento, As eh o resto da lista.
   Exemplo: [7,1,3] vira A = 7 e As = [1,3].
*/


/* basicos de lista */

% Verdadeiro se E aparece na lista.
membro(E, [E|_]).
membro(E, [_|As]) :-
    membro(E, As).

% concatena(Lista1, Lista2, Resultado).
concatena([], L, L).
concatena([A|As], L, [A|R]) :-
    concatena(As, L, R).

% Conta quantos elementos ha na lista.
comprimento([], 0).
comprimento([_|As], R) :-
    comprimento(As, T),
    R is T + 1.

% Soma todos os numeros da lista.
soma([], 0).
soma([A|As], R) :-
    soma(As, T),
    R is A + T.


/* maior e menor */

% Usa A como "maior ate agora" e percorre o resto As.
maior([A|As], R) :-
    maior(As, A, R).

maior([], M, M).
maior([A|As], M, R) :-
    A > M,
    maior(As, A, R).
maior([A|As], M, R) :-
    A =< M,
    maior(As, M, R).

% Mesma ideia do maior, mas guardando o menor visto ate agora.
menor([A|As], R) :-
    menor(As, A, R).

menor([], M, M).
menor([A|As], M, R) :-
    A < M,
    menor(As, A, R).
menor([A|As], M, R) :-
    A >= M,
    menor(As, M, R).


/* inverter lista */

% Acc eh o acumulador: vai recebendo os elementos na frente.
inverte(L, R) :-
    inverte(L, [], R).

inverte([], Acc, Acc).
inverte([A|As], Acc, R) :-
    inverte(As, [A|Acc], R).


/* contar ocorrencias e elemento mais recorrente */

% Se a cabeca eh o elemento procurado, conta 1 e continua no resto.
conta(_, [], 0).
conta(E, [E|As], R) :-
    conta(E, As, T),
    R is T + 1.
conta(E, [A|As], R) :-
    E \= A,
    conta(E, As, R).

% Guarda o elemento campeao ate agora e sua quantidade.
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


/* remover uma ocorrencia */

% Remove apenas a primeira ocorrencia encontrada.
remove_um(E, [E|As], As).
remove_um(E, [A|As], [A|R]) :-
    E \= A,
    remove_um(E, As, R).


/* selection sort */

% Acha o menor, coloca na frente, remove esse menor e ordena o resto.
selection([], []).
selection(L, [M|R]) :-
    menor(L, M),
    remove_um(M, L, L2),
    selection(L2, R).


/* insertion sort */

% Ordena o resto e depois insere A no lugar certo.
insertion([], []).
insertion([A|As], R) :-
    insertion(As, Ord),
    insere_ord(A, Ord, R).

insere_ord(E, [], [E]).
% Se E deve vir antes de A, a lista final comeca com E.
insere_ord(E, [A|As], [E,A|As]) :-
    E =< A.
% Caso contrario, mantem A na frente e tenta inserir E no resto.
insere_ord(E, [A|As], [A|R]) :-
    E > A,
    insere_ord(E, As, R).


/* bubble sort */

% Repetimos passadas; cada passada empurra o maior para o final.
bubble([], []).
bubble(L, R) :-
    bubble_passes(L, L, R).

bubble_passes([], Acc, Acc).
bubble_passes([_|As], Acc, R) :-
    leva_maior(Acc, Acc2),
    bubble_passes(As, Acc2, R).

leva_maior([], []).
leva_maior([A], [A]).
% Se B < A, troca os vizinhos: B vem antes e A continua "andando".
leva_maior([A,B|As], [B|R]) :-
    B < A,
    leva_maior([A|As], R).
leva_maior([A,B|As], [A|R]) :-
    A =< B,
    leva_maior([B|As], R).


/* quick sort */

% P eh o pivo. Separa menores/maiores, ordena os lados e junta tudo.
quick([], []).
quick([P|As], R) :-
    particiona(P, As, Menores, Maiores),
    quick(Menores, RMenores),
    quick(Maiores, RMaiores),
    append(RMenores, [P|RMaiores], R).

% Particiona o resto da lista em dois grupos em relacao ao pivo.
particiona(_, [], [], []).
particiona(P, [A|As], [A|Menores], Maiores) :-
    A =< P,
    particiona(P, As, Menores, Maiores).
particiona(P, [A|As], Menores, [A|Maiores]) :-
    A > P,
    particiona(P, As, Menores, Maiores).


/* merge sort */

% Divide, ordena cada metade, depois intercala.
merge_sort([], []).
merge_sort([A], [A]).
merge_sort(L, R) :-
    divide(L, L1, L2),
    merge_sort(L1, R1),
    merge_sort(L2, R2),
    intercala(R1, R2, R).

divide([], [], []).
divide([A], [A], []).
% Divide alternando elementos: A vai para L1, B vai para L2.
divide([A,B|As], [A|R1], [B|R2]) :-
    divide(As, R1, R2).

intercala([], L, L).
intercala(L, [], L).
% Menor cabeca vai primeiro no resultado.
intercala([A|As], [B|Bs], [A|R]) :-
    A =< B,
    intercala(As, [B|Bs], R).
intercala([A|As], [B|Bs], [B|R]) :-
    A > B,
    intercala([A|As], Bs, R).


/* run-length encoding: util para frequencia/Huffman */

% Transforma [a,a,a,b,b] em [(a,3),(b,2)].
rle([], []).
rle([E|Es], R) :-
    rle(Es, E, 1, R).

rle([], E, N, [(E,N)]).
% Mesmo elemento: aumenta o contador.
rle([E|As], E, N, R) :-
    N2 is N + 1,
    rle(As, E, N2, R).
% Elemento mudou: fecha o par antigo e comeca novo contador.
rle([A|As], E, N, [(E,N)|R]) :-
    A \= E,
    rle(As, A, 1, R).

% Decodifica [(a,3),(b,2)] de volta para [a,a,a,b,b].
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


/* consultas prontas:

?- lista_exemplo(L), maior(L, R).
?- lista_exemplo(L), menor(L, R).
?- lista_exemplo(L), inverte(L, R).
?- lista_exemplo(L), conta(3, L, R).
?- lista_exemplo(L), mais_recorrente(L, R).
?- lista_exemplo(L), selection(L, R).
?- lista_exemplo(L), insertion(L, R).
?- lista_exemplo(L), bubble(L, R).
?- lista_exemplo(L), quick(L, R).
?- lista_exemplo(L), merge_sort(L, R).
?- rle([a,a,a,b,b,c,a,a], R).
?- rld([(a,3),(b,2),(c,1)], R).

*/
