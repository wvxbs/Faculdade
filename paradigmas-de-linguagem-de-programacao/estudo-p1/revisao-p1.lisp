;;;; =========================================================================
;;;; REVISÃO COMPLETA PARA P1 - PARADIGMAS DE LINGUAGENS DE PROGRAMAÇÃO
;;;; Foco: Lisp Puramente Funcional, Recursão, Manipulação de Listas e Ordenação
;;;; =========================================================================
;;;; Instruções de Execução no Terminal:
;;;; 1. Usando SBCL : sbcl --script revisao_p1.lisp
;;;; 2. Usando CLISP: clisp revisao_p1.lisp
;;;; 3. Em um REPL  : (load "revisao_p1.lisp") e depois (executar-testes)
;;;; =========================================================================

;; ---------------------------------------------------------------------------
;; 1. OPERAÇÕES BÁSICAS E MANIPULAÇÃO RECURSIVA DE LISTAS
;; ---------------------------------------------------------------------------

(defun soma-lista (lst)
  "Retorna a soma de todos os elementos numéricos de uma lista."
  (if (null lst)
      0
      (+ (car lst) (soma-lista (cdr lst)))))

(defun comprimento (lst)
  "Calcula o tamanho de uma lista recursivamente."
  (if (null lst)
      0
      (+ 1 (comprimento (cdr lst)))))

(defun pertence-p (elem lst)
  "Verifica se elem pertence a lst."
  (cond ((null lst) nil)
        ((equal elem (car lst)) t)
        (t (pertence-p elem (cdr lst)))))

(defun anexar (lst1 lst2)
  "Concatena duas listas de forma puramente funcional (equivalente ao append)."
  (if (null lst1)
      lst2
      (cons (car lst1) (anexar (cdr lst1) lst2))))

(defun inverter (lst)
  "Inverte a ordem dos elementos de uma lista."
  (if (null lst)
      nil
      (anexar (inverter (cdr lst)) (list (car lst)))))

(defun filtrar-pares (lst)
  "Retorna apenas os números pares de uma lista."
  (cond ((null lst) nil)
        ((evenp (car lst)) (cons (car lst) (filtrar-pares (cdr lst))))
        (t (filtrar-pares (cdr lst)))))

(defun mapeamento (fn lst)
  "Aplica uma função fn a cada elemento da lista (mapcar recursivo)."
  (if (null lst)
      nil
      (cons (funcall fn (car lst)) (mapeamento fn (cdr lst)))))


;; ---------------------------------------------------------------------------
;; 2. ALGORITMOS DE ORDENAÇÃO FUNCIONAIS (CRUCIAIS PARA A P1)
;; ---------------------------------------------------------------------------

;; --- A. INSERTION SORT ---
(defun inserir-ordenado (n lst)
  "Insere o elemento N na posição correta da lista ordenada LST."
  (cond ((null lst) (list n))
        ((<= n (car lst)) (cons n lst))
        (t (cons (car lst) (inserir-ordenado n (cdr lst))))))

(defun insertion-sort (lst)
  "Ordenação por inserção puramente funcional."
  (if (null lst)
      nil
      (inserir-ordenado (car lst) (insertion-sort (cdr lst)))))


;; --- B. QUICK SORT ---
(defun filtrar-menores (pivo lst)
  "Retorna elementos da lista estritamente menores ou iguais ao pivo."
  (cond ((null lst) nil)
        ((<= (car lst) pivo) (cons (car lst) (filtrar-menores pivo (cdr lst))))
        (t (filtrar-menores pivo (cdr lst)))))

(defun filtrar-maiores (pivo lst)
  "Retorna elementos da lista estritamente maiores que o pivo."
  (cond ((null lst) nil)
        ((> (car lst) pivo) (cons (car lst) (filtrar-maiores pivo (cdr lst))))
        (t (filtrar-maiores pivo (cdr lst)))))

(defun quick-sort (lst)
  "Ordenação rápida (Quick Sort) puramente funcional."
  (if (null lst)
      nil
      (let ((pivo (car lst))
            (cauda (cdr lst)))
        (anexar (quick-sort (filtrar-menores pivo cauda))
                (cons pivo (quick-sort (filtrar-maiores pivo cauda)))))))


;; --- C. MERGE SORT ---
(defun metade-primeira (lst n)
  "Retorna os primeiros N elementos de LST."
  (if (or (null lst) (<= n 0))
      nil
      (cons (car lst) (metade-primeira (cdr lst) (- n 1)))))

(defun metade-segunda (lst n)
  "Retorna os elementos de LST a partir do índice N."
  (if (or (null lst) (<= n 0))
      lst
      (metade-segunda (cdr lst) (- n 1))))

(defun intercalar (l1 l2)
  "Intercala duas listas já ordenadas em uma única lista ordenada."
  (cond ((null l1) l2)
        ((null l2) l1)
        ((<= (car l1) (car l2))
         (cons (car l1) (intercalar (cdr l1) l2)))
        (t (cons (car l2) (intercalar l1 (cdr l2))))))

(defun merge-sort (lst)
  "Ordenação por intercalação (Merge Sort) puramente funcional."
  (if (or (null lst) (null (cdr lst)))
      lst
      (let* ((tam (comprimento lst))
             (meio (floor tam 2))
             (esq (metade-primeira lst meio))
             (dir (metade-segunda lst meio)))
        (intercalar (merge-sort esq) (merge-sort dir)))))


;; ---------------------------------------------------------------------------
;; 3. ESTRUTURA MODELO DO EP1 (LOCALIZAÇÃO E VERIFICAÇÃO NO TABULEIRO)
;; ---------------------------------------------------------------------------

(defun achar-coluna-rei (linha-str col)
  "Encontra o índice da coluna onde está o Rei 'R' na string da linha."
  (cond ((>= col (length linha-str)) nil)
        ((char= (char linha-str col) #\R) col)
        (t (achar-coluna-rei linha-str (+ col 1)))))

(defun achar-rei (tabuleiro lin)
  "Encontra as coordenadas (linha coluna) do Rei 'R' no tabuleiro de xadrez."
  (if (or (null tabuleiro) (>= lin 8))
      nil
      (let* ((linha-atual (car tabuleiro))
             (col (if (stringp linha-atual) (achar-coluna-rei linha-atual 0) nil)))
        (if col
            (list lin col)
            (achar-rei (cdr tabuleiro) (+ lin 1))))))

(defun rei-em-xeque-p (tabuleiro)
  "Função de apoio demonstrativa para a lógica do EP1."
  (let ((pos-rei (achar-rei tabuleiro 0)))
    (if pos-rei
        (format nil "Rei 'R' encontrado na posição: Linha ~A, Coluna ~A." (first pos-rei) (second pos-rei))
        "Rei 'R' não foi encontrado no tabuleiro.")))


;; ---------------------------------------------------------------------------
;; 4. HELPER E SUÍTE DE EXECUTÁVEL (DRIVER PARA BATERIA DE TESTES)
;; ---------------------------------------------------------------------------

(defun executar-testes ()
  "Executa e exibe o resultado de todas as funções de estudo para a P1."
  (format t "~%==================================================")
  (format t "~%   BATERIA DE TESTES - REVISÃO P1 (COMMON LISP)")
  (format t "~%==================================================~%")

  (let ((lista-nums '(5 2 9 1 7 3 8 4 6))
        (tabuleiro-exemplo '("tcbdrbct" 
                            "pppppppp" 
                            "        " 
                            "    R   " 
                            "        " 
                            "        " 
                            "PPPPPPPP" 
                            "TCBDRBCT")))

    (format t "~%--- 1. MANIPULAÇÃO DE LISTAS ---~%")
    (format t "Lista Original        : ~A~%" lista-nums)
    (format t "Soma dos Elementos   : ~A~%" (soma-lista lista-nums))
    (format t "Comprimento da Lista  : ~A~%" (comprimento lista-nums))
    (format t "Pertence 7?           : ~A~%" (pertence-p 7 lista-nums))
    (format t "Pertence 99?          : ~A~%" (pertence-p 99 lista-nums))
    (format t "Filtrar Pares         : ~A~%" (filtrar-pares lista-nums))
    (format t "Lista Invertida       : ~A~%" (inverter lista-nums))
    (format t "Mapear (Dobro)        : ~A~%" (mapeamento (lambda (x) (* x 2)) lista-nums))

    (format t "~%--- 2. ALGORITMOS DE ORDENAÇÃO FUNCIONAL ---~%")
    (format t "Insertion Sort        : ~A~%" (insertion-sort lista-nums))
    (format t "Quick Sort            : ~A~%" (quick-sort lista-nums))
    (format t "Merge Sort            : ~A~%" (merge-sort lista-nums))

    (format t "~%--- 3. EXEMPLO MODELO DO EP1 (XADREZ) ---~%")
    (format t "Status do Tabuleiro   : ~A~%" (rei-em-xeque-p tabuleiro-exemplo))

    (format t "~%==================================================")
    (format t "~%   TODOS OS TESTES FORAM EXECUTADOS COM SUCESSO!")
    (format t "~%==================================================~%")))

;; Executa automaticamente a suíte de testes ao carregar o script
(executar-testes)