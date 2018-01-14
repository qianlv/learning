#lang planet neil/sicp
(define (smallest-divisor n) (find-divisior n 2))
(define (square x) (* x x))
(define (divides? a b)
  (= (remainder b a) 0))
(define (find-divisior n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? test-divisor n) test-divisor)
        (else (find-divisior n (+ test-divisor 1)))))

