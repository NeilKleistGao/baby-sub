# baby-sub
A more simple simple-sub algorithm implementation in C++

## Syntax
```
exp -> var | (exp exp) | lamb = exp | let var = exp in exp | lit | (exp)
var -> \w+
lamb -> \var
lit -> true | false | [0-9]+
```