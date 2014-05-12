;;; *title* Exercise 2.34
;;; *author* Eduardo Acuña Yeomans
;;; *about* Exercise from the \emph{Sequences as Conventional Interfaces}
;;; section of Structure and Interpretation of Computer Programs.

;;; *description* Evaluating a polynomial in $x$ at a given value of $x$ can
;;; be formulated as an accumulation. We evaluate the polynomial
;;; 
;;; $$a_{n}x^{n}+a_{n-1}x^{n-1}+ \dots +a_{1}x + a_{0}$$
;;;
;;; using a well-known algorithm called Horner's rule, which structures the
;;; computation as
;;; 
;;; $$( \dots (a_{n}x + a_{n-1})x + \dots + a_{1})x+a_{0}$$
;;; 
;;; In other words, we start with $a_{n}$, multiply by $x$, add $a_{n-1}$,
;;; multiply by $x$ and so on until we reach $a_{0}$. Fill in the following
;;; template to produce a procedure that evaluates a polynomial using
;;; Horner's rule. Assume that the coefficients of the polynomial are
;;; arranged in a sequence, from $a_{0}$ through $a_{n}$.
;;; 
;;; \begin{verbatim}
;;; (define (horner-eval x coefficient-sequence)
;;;   (accumulate (lambda (this-coeff higher-terms) <??>)
;;;               0
;;;               coefficient-sequence))
;;; \end{verbatim}
;;;
;;; For example, to compute $1+3x+5x^{3}+x^{5}$ at $x=2$ you would evaluate
;;; \texttt{]=> (horner-eval 2 (list 1 3 0 5 0 1))}

(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
	  (accumulate op initial (cdr sequence)))))

;;; *contract* horner-eval : number , list -> number
;;; *description* Return the evaluation of the polynomial with the coefficients
;;; given by the \texttt{coefficient-sequence} at a given number \texttt{x}
;;; using Horner's rule.
(define (horner-eval x coefficient-sequence)
  (accumulate (lambda (this-coeff higher-terms)
		(+ this-coeff (* x higher-terms)))
	      0
	      coefficient-sequence))
