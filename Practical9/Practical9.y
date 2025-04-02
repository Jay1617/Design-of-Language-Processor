%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex();
%}

%token I T B A  // Removed 'E' from token list

%%
S  : I E T S Sp  { printf("Valid string\n"); exit(0); }
   | A           { printf("Valid string\n"); exit(0); };
Sp : 'e' S       | /* epsilon */;
E  : B;   // 'E' is a non-terminal, NOT a token
%%

void yyerror(const char *s) {
    printf("Invalid string\n");
    exit(1);
}

int main() {
    printf("Enter input string: ");
    yyparse();
    return 0;
}
