;follow actual  structure, all start with define

(define (isList a) (if (list? a) a 'param_passed_is_not_list)) ;rule 24 ; rule 33

(define (carList a) (car a)) ;rule 26

(define (PositiveNumber a) (and (number? a) (<= 0 a))) ;rule 28 

(define (NotList a) (not (list? a))) ; rule 30 

(define (isSymbol a) (symbol? a)) ; rule 32

(define (isZero a) (zero? a)) ;rule 34

(define(isString a) (string? a)) ;rule 36

(define(Sub a b) (- a b)) ;rule 38

(define(Mult a b) (* a b)) ;rule 40

(define(EqaulTo a b) (= a b)) ; rule 42

(define(LessThan a b) ( < a b));rule 44

(define(LessThanEqual a b) ( <= a b )) ;rule 46

(define(DisplayZ a) (display a));rule 48

