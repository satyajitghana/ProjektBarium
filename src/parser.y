%{
    #include <iostream>
    #include <memory>

    extern int yylex();
    extern int yyparse();

    void yyerror(const char *s) { std::cerr << "Error " << s << std::endl; }
%}

// tokens are stored in yytype of the below union
%union {
    // std::unique_ptr
    int ival;
    int token;
    // std::unique_ptr<std::string> string;
}

/* terminal symbols */
%token <ival> INT
%token <token> TPLUS TMINUS TMUL TDIV

/* operator precedence */
%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%
program : INT TPLUS INT {  std::cout << ($1 + $3) << std::endl; }
        ;

%%