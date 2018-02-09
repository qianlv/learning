#lang planet neil/sicp
(define (double x) (+ x x))
(define (halve x) (/ x 2))

(define (multiply a b)
  (define (iter a b product)
    (cond ((= b 0) product)
          ((even? b) (iter (double a) (halve b) product))
          (else (iter (double a) (- (halve b) 0.5) (+ product a)))))
  (iter a b 0))
