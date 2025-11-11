%{
#include <stdio.h>
%}

/* Definitions of token patterns */
DIGIT      [0-9]+
ID         [a-zA-Z_][a-zA-Z0-9_]*
KEYWORD    (if|else|while)
WS         [ \t\n]+

%%
{KEYWORD}      { printf("Keyword: %s\n", yytext); }
{ID}           { printf("Identifier: %s\n", yytext); }
{DIGIT}        { printf("Number: %s\n", yytext); }
"+"|"-"|"*"|"/" { printf("Operator: %s\n", yytext); }
{WS}           { /* ignore whitespace */ }
.              { printf("Unknown character: %s\n", yytext); }
%%

int main(int argc, char **argv) {
    yylex(); // Start lexical analysis
    return 0;
}

int yywrap() {
    return 1;
}
