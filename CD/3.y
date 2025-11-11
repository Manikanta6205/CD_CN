%{
#include <stdio.h>
#include <stdlib.h>
int flag = 0;
void yyerror(const char *s);
int yylex(void);
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%
ArithmeticExpression:
    E { printf("Result = %d\n", $$); return 0; }
;

E:
      E '+' E   { $$ = $1 + $3; }
    | E '-' E   { $$ = $1 - $3; }
    | E '*' E   { $$ = $1 * $3; }
    | E '/' E   { $$ = $1 / $3; }
    | E '%' E   { $$ = $1 % $3; }
    | '(' E ')' { $$ = $2; }
    | NUMBER    { $$ = $1; }
;
%%

int main(void) {
    printf("Enter any arithmetic expression (+, -, *, /, %% and parentheses):\n");
    yyparse();
    if (flag == 0)
        printf("Entered arithmetic expression is Valid\n");
    return 0;
}

void yyerror(const char *s) {
    (void)s;
    printf("Entered arithmetic expression is Invalid\n");
    flag = 1;
}
