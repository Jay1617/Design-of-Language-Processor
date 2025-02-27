%{
#include <stdio.h>
%}

DIGIT      [0-9]
LETTER     [a-zA-Z_]
ID         {LETTER}({LETTER}|{DIGIT})*
KEYWORDS   "int"|"char"|"return"|"if"|"else"|"for"|"while"|"break"
OPERATORS  "="|"+"|"-"|"*"|"/"|"<"|">"|"=="|"!="
PUNCTUATION "[{}();,]"
COMMENT    "//".*|"/*"(.|\n)*"*/"

%%
{KEYWORDS}    { printf("Keyword: %s\n", yytext); }
{ID}          { printf("Identifier: %s\n", yytext); }
{DIGIT}+      { printf("Constant: %s\n", yytext); }
{OPERATORS}   { printf("Operator: %s\n", yytext); }
{PUNCTUATION} { printf("Punctuation: %s\n", yytext); }
{COMMENT}     { printf("Comment: %s\n", yytext); }
\"(\\.|[^\\"])*\" { printf("String: %s\n", yytext); }
[ \t\n]+      { /* Ignore whitespace */ }
.             { printf("Unknown: %s\n", yytext); }

%%
int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
