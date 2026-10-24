;; =============================================================================
;; ESTUDO P1 - LISP E CÁLCULO LAMBDA
;; =============================================================================

(format t "~%=== 1. SIMULAÇÃO DE CÁLCULO LAMBDA EM LISP ===~%")

;; Booleanos de Church
(defvar T-church (lambda (x) (lambda (y) x)))
(defvar F-church (lambda (x) (lambda (y) y)))

;; Operadores Lógicos de Church
(defvar AND-church (lambda (x) (lambda (y) (funcall (funcall x y) F-church))))
(defvar NOT-church (lambda (x) (funcall (funcall x F-church) T-church)))

;; Números de Church
(defvar ZERO (lambda (s) (lambda (z) z)))
(defvar UM   (lambda (s) (lambda (z) (funcall s z))))
(defvar DOIS (lambda (s) (lambda (z) (funcall s (funcall s z)))))

;; Auxiliar para converter Número de Church para inteiro Lisp (para visualizar)
(defun church->int (n)
  (funcall (funcall n (lambda (x) (+ 1 x))) 0))

;; Testando Cálculo Lambda
(let ((res-and (funcall (funcall AND-church T-church) F-church)))
  (format t "Church AND (T, F) escolhe primeiro(T) ou segundo(F)? -> ~a~%"
          (if (eq res-and T-church) "VERDADEIRO" "FALSO")))

(format t "Church NUMERO 2 convertido para int: ~a~%" (church->int DOIS))


;; =============================================================================
;; 2. RECURSÃO E MANIPULAÇÃO DE LISTAS EM LISP
;; =============================================================================

(format t "~%=== 2. ALGORITMOS DE LISTAS EM LISP ===~%")

;; Somar elementos
(defun somar-lista (lst)
  (if (null lst)
      0
      (+ (car lst) (somar-lista (cdr lst)))))

;; Filtrar Pares
(defun filtrar-pares (lst)
  (cond ((null lst) nil)
        ((evenp (car lst)) (cons (car lst) (filtrar-pares (cdr lst))))
        (t (filtrar-pares (cdr lst)))))

;; Insertion Sort Funcional
(defun inserir-ordenado (n lst)
  (cond ((null lst) (list n))
        ((<= n (car lst)) (cons n lst))
        (t (cons (car lst) (inserir-ordenado n (cdr lst))))))

(defun insertion-sort (lst)
  (if (null lst)
      nil
      (inserir-ordenado (car lst) (insertion-sort (cdr lst)))))

;; Bateria de Testes Rápidos
(let ((minha-lista '(5 2 9 1 8 4)))
  (format t "Lista Original:  ~a~%" minha-lista)
  (format t "Soma da Lista:   ~a~%" (somar-lista minha-lista))
  (format t "Apenas Pares:    ~a~%" (filtrar-pares minha-lista))
  (format t "Lista Ordenada:  ~a~%" (insertion-sort minha-lista)))