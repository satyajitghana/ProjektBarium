/* auxiliary declarations */
%{
    #include <iostream>
    #include <string>
    #include <cstdio>
    #include <memory>

    #include "parser.hpp"

    extern "C" int yywrap() { return 1; }

    #define SAVE_TOKEN  yylval.string = std::make_unique<std::string>(yytext, yyleng)
    #define TOKEN(t)    (yylval.token = t)
%}

/* %option noyywrap */

/* regular definitions */
NUMBER      [0-9]+

/* rules */
%%
[ \n\t]             ; /* ignore white spaces, newline, tabs */
[a-zA-Z_][a-zA-Z0-9_]*      { SAVE_TOKEN; return TOKEN(TIDENT) }
{NUMBER}\.{NUMBER}          { SAVE_TOKEN; return TOKEN(TFRACTION); }
{NUMBER}                    { SAVE_TOKEN; return TOKEN(TDECIMAL); }
"="                         { return TOKEN(TEQ); }
"+"                         { return TOKEN(TPLUS); }

.                           { std::cerr << "unknown token" << "\n"; yyterminate(); }
%%

