(defun menor* (lst atual)
  (if (null lst)
      atual
      (menor* (cdr lst)
              (min atual (car lst)))))

(defun menor (lst)
  (if (null lst)
      nil
      (menor* (cdr lst) (car lst))))