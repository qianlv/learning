#lang planet neil/sicp
(define (smallest-divisor n) (find-divisior n 2))
(define (square x) (* x x))
(define (divides? a b)
  (= (remainder b a) 0))
(define (find-divisior n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? test-divisor n) test-divisor)
        (else (find-divisior n (+ test-divisor 1)))))

(define (prime? n)
  (= n (smallest-divisor n)))

(define (timed-prime-test n)
  (newline)
  (display n)
  (start-prime-test n (runtime)))
(define (start-prime-test n start-time)
  (if (prime? n)
      (report-prime (- (runtime) start-time))))
(define (report-prime elapsed-time)
  (display " *** ")
  (display elapsed-time))

(define (search-for-primes first last)
  (define (search-iter cur last)
    (if (<= cur last) (timed-prime-test cur))
    (if (<= cur last) (search-iter (+ cur 2) last)))
  (if (even? first)
      (search-iter (+ first 1) last)
      (search-iter first last)))
      
  