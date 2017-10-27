#lang planet neil/sicp
(define (pascal-triangle row col)
  (cond ((and (= row 0) (= col 0)) 1)
        ((or (< col 0) (< row 0) (> col row)) 0)
        (else (+ (pascal-triangle (- row 1) (- col 1))
                 (pascal-triangle (- row 1) col)))))
