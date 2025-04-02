%{
#include "y.tab.h"
%}

%%
i   return I;
t   return T;
e   return 'e';
b   return B;
a   return A;
[ \t\n] ;  // Ignore spaces and newlines
.   { yyerror("Invalid string"); }
%%

int yywrap() { return 1; }
