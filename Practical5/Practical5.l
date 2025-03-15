%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;
%}

DIGIT      [0-9]
LETTER     [a-zA-Z_]
ID         {LETTER}({LETTER}|{DIGIT})*
KEYWORDS   "int"|"char"|"return"|"if"|"else"|"for"|"while"|"break"
OPERATORS  "="|"+"|"-"|"*"|"/"|"<"|">"|"=="|"!="
PUNCTUATION "[{}();,]"
COMMENT    "//".*|"/*"(.|\n)*"*/"

%%  
{KEYWORDS}    { fprintf(fp, "Keyword: %s\n", yytext); }
{ID}          { fprintf(fp, "Identifier: %s\n", yytext); }
{DIGIT}+      { fprintf(fp, "Constant: %s\n", yytext); }
{OPERATORS}   { fprintf(fp, "Operator: %s\n", yytext); }
{PUNCTUATION} { fprintf(fp, "Punctuation: %s\n", yytext); }
{COMMENT}     { fprintf(fp, "Comment: %s\n", yytext); }
\"(\\.|[^\\"])*\" { fprintf(fp, "String: %s\n", yytext); }
[ \t\n]+      { /* Ignore whitespace */ }
.             { fprintf(fp, "Unknown: %s\n", yytext); }

%%

int main() {
    FILE *inputFile = fopen("test.c", "r");
    if (!inputFile) {
        printf("Error: Unable to open test.c\n");
        return 1;
    }

    fp = fopen("tokens.txt", "w");
    if (!fp) {
        printf("Error: Unable to create tokens.txt\n");
        return 1;
    }

    yyin = inputFile;
    yylex();

    fclose(inputFile);
    fclose(fp);

    printf("Lexical analysis completed. Check tokens.txt for output.\n");
    return 0;
}

int yywrap() {
    return 1;
}
