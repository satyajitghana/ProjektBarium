%{
    #include <string>

    extern "C" int yywrap() { return 1; }
    
    #define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
    #define TOKEN(t) (yylval.token = t)
%}

%option noyywrap

%%

[ \n\t]

"extern"    return TOKEN(TEXTERN);

%%
