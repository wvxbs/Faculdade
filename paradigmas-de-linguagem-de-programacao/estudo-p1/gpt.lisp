;;;; =========================
;;;; LISTAS
;;;; =========================

(defun primeiro (lst)
  (car lst))

(defun resto (lst)
  (cdr lst))

(defun adicionar-frente (x lst)
  (cons x lst))

;; Recursao

(defun tamanho (lst)
    (if (null lst)
        0
        (+ 1 (tamanho (cdr lst)))))

(defun somar-lista (lst)
    (if (null lst)
        0
        (+ (car lst) (somar-lista (cdr lst)))))

(defun dobrar (lst)
  (if (null lst)
      nil
      (cons (* 2 (car lst))
            (dobrar (cdr lst)))))

(defun filtrar-pares (lst)
  (cond
    ((null lst)
     nil)

    ((evenp (car lst))
     (cons (car lst)
           (filtrar-pares (cdr lst))))

    (t
     (filtrar-pares (cdr lst)))))

(defun imprime-lista-when (lst)
  (when lst
    (print (car lst))
    (imprime-lista (cdr lst))))

(defun imprime-lista-if (lst)
  (if (null lst)
      nil
      (progn
        (print (car lst))
        (imprime-lista (cdr lst)))))

(defun maior-elemento (lst)
  (cond ((null lst) nil)
        ((null (cdr lst)) (car lst)) ;; Lista de 1 elemento: ele é o maior
        (t (let ((maior-do-resto (maior-elemento (cdr lst))))
             (if (> (car lst) maior-do-resto)
                 (car lst)
                 maior-do-resto)))))

(defun menor-elemento (lst)
  (cond ((null lst) nil)
        ((null (cdr lst)) (car lst))
        (t (let ((menor-do-resto (menor-elemento (cdr lst))))
             (if (< (car lst) menor-do-resto)
                 (car lst)
                 menor-do-resto)))))

;; Auxiliar 1: conta quantas vezes N aparece na lista
(defun contar-ocorrencias (n lst)
  (cond ((null lst) 0)
        ((equal n (car lst)) (+ 1 (contar-ocorrencias n (cdr lst))))
        (t (contar-ocorrencias n (cdr lst)))))

;; Auxiliar 2: compara frequência do primeiro elemento com o mais frequente do resto
(defun mais-frequente (lst)
  (cond ((null lst) nil)
        ((null (cdr lst)) (car lst))
        (t (let* ((freq-cabeca (contar-ocorrencias (car lst) lst))
                  (mais-freq-resto (mais-frequente (cdr lst)))
                  (freq-resto (contar-ocorrencias mais-freq-resto lst)))
             (if (>= freq-cabeca freq-resto)
                 (car lst)
                 mais-freq-resto)))))