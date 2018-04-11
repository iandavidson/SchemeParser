;follow actual  structure, all start with define


(define (isSymbol a) (symbol? a)) ; rule 32

(define (isZero a) (zero? a)) ;rule 34

(define(isString a) (string? a)) ;rule 36

(define(Sub a b) (- a b)) ;rule 38

(define(Mult a b) (* a b)) ;rule 40

(define(EqaulTo a b) (= a b)) ; rule 42

(define(LessThan a b) ( < a b));rule 44

(define(LessThanEqual a b) ( <= a b )) ;rule 46

(define(DisplayZ a) (display a));rule 48

