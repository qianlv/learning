#lang planet neil/sicp
(define (exp b n)
  (exp-iter 1 b n))
(define (exp-iter a b n)
  (define (square x) (* x x))
  (cond ((= n 0) a)
        ((even? n) (exp-iter a (square b) (/ n 2)))
        (else (exp-iter (* a b) b (- n 1)))))