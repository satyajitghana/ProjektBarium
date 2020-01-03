/* auxiliary declarations */
%{
    #include <iostream>
    #include <string>
    #include <cstdio>

    #include "parser.hpp"

    extern "C" int yywrap() { return 1; }
%}

/* %option noyywrap */

/* regular definitions */
NUMBER      [0-9]+

/* rules */
%%
[ \n\t]             ; /* ignore white spaces, newline, tabs */
{NUMBER}            { yylval.ival = atoi(yytext); return INT; }
"+"                 { return TPLUS; }
%%

