#lang planet neil/sicp
(define (cube x) (* x x x))
(define (p x) (- (* 3 x) (* 4 (cube x))))
(define (sine angle)
  (if (not (> (abs angle) 0.1))
      angle
      (p (sine (/ angle 3.0)))))

; a:
; (sine 12.15) --> (p (p (p (p (p (sine (/ 12.15 81)))))))
; 5 times
; b:
; (<= (/ a 0.1) (pow 3 a)) --> (ceiling (/ (log (/ a 0.1)) (log 3)))
; O(log(a))
