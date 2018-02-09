#lang planet neil/sicp
(define (double x) (+ x x))
(define (halve x) (/ x 2))
; recursive
(define (multiply-recursive a b)
  (cond ((= b 0) 0)
        ((even? b) (double (multiply-recursive a (/ b 2))))
        (else (+ a (multiply-recursive a (- b 1))))))
        
; tail recursive
(define (multiply a b)
  (iter a b 0))
(define (iter a b product)
  (cond ((= b 0) product)
        ((even? b) (iter (+ a a) (/ b 2) product))
        (else (iter a (- b 1) (+ product a)))))