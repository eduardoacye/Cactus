;;; *title* Programa del factorial
;;; *author* Eduardo Acuña Yeomans
;;; *about* La clásica función factorial.
;;; $$n!=n*(n-1)*(n-1)*...*2*1$$

;;; *contract* factorial : numero -> numero
;;; *description* Return n! = n(n-1)...1 .
(define (factorial n)
  (if (= n 0)
      1
      (* n (factorial (- n 1)))))
