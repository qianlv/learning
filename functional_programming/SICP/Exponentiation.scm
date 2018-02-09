#lang planet neil/sicp
; space O(n), time O(n)
(define (expt b n)
  (if (= n 0)
      1
      (* b (expt b (- n 1)))))

; space O(1), time O(n)
(define (expt-another b n)
  (expt-iter b n 1))
(define (expt-iter b counter product)
  (if (= counter 0)
      product
      (expt-iter b
                 (- counter 1)
                 (* b product))))

; fast
(define (fast-expt b n)
  (define (square x) (* x x))
  (cond ((= n 0) 1)
        ((even? n) (square (fast-expt b (/ n 2))))
        (else (* b (fast-expt b (- n 1))))))