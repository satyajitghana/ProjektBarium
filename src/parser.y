%skeleton "lalr1.cc"
%require "3.5"
%language "c++"

%defines 

// variant will make sure we can use our non-trivial types
%define api.value.type variant
%define api.token.constructor
%define parse.assert

// this will be added to the parser.cpp file, cyclic-dependecy is resolved by using
// forward declaration of the driver class
%code requires {
    #include <string>
    #include <memory>
    #include <typeinfo>

    class driver;

    #include "ast_structures.hpp"

    static int cnt = 0;
}

// parsing context
%param { driver& drv }

// for location tracking
%locations

// because we'll be using the driver class methods
%code {
    #include "driver.hpp"

    std::shared_ptr<block> program_block;
}

// to make sure there are no conflicts prepend TOK_
%define api.token.prefix{TOK_}
%token 
    END  0  "end of file"
    ASSIGN  "="
    PLUS    "+"
    MINUS   "-"
    MUL     "*"
    DIV     "/"

%token  <std::unique_ptr<identifier>>   IDENT       "identifier"
%token  <std::unique_ptr<decimal>>      DECIMAL     "decimal"
%token  <std::unique_ptr<fraction>>     FRACTION    "fraction" 
%nterm  <std::unique_ptr<expression>>   expr
%nterm  <std::unique_ptr<expression>>   literals
%nterm  <std::unique_ptr<expression>>   binop_expr
%nterm  <std::unique_ptr<block>>        stmts
%nterm  <std::unique_ptr<block>>        program
%nterm  <std::unique_ptr<statement>>    stmt

%printer { yyo << $$; } <*>;

%start program;

%code {
    #define DEBUG_PARSER
    #undef DEBUG_PARSER
}

%%

%left "+" "-";
%left "*" "/";

program     : stmts {

                #ifdef DEBUG_PARSER
                std::cout << "program: " << cnt++ << "\n";
                #endif

                program_block = std::move($1);

                }
            ;

stmts       : stmt {

                #ifdef DEBUG_PARSER
                std::cout << "stmts: " << cnt++ << "\n";
                #endif

                $$ = std::make_unique<block>();
                $$->statements.emplace_back(std::move($1));

                }
            | stmts stmt {

                #ifdef DEBUG_PARSER
                std::cout << "stmts stmt: " << cnt++ << "\n";
                #endif

                $1->statements.emplace_back(std::move($2));

                }
            ;

stmt        : expr {
                #ifdef DEBUG_PARSER
                std::cout << "expr: " << cnt++ << "\n";
                #endif

                $$ = std::make_unique<expr_statement>(std::move($1));

                }
            ;

literals    : "decimal"  {

                #ifdef DEBUG_PARSER
                std::cout<< "decimal: " << cnt++ << "\n"; 
                #endif
                
                $$ = std::move($1);
                
                }
            | "fraction" {

                
                }
            ;

expr        : "identifier" "=" expr {

                #ifdef DEBUG_PARSER
                std::cout << "identifier = expr: " << cnt++ << "\n";
                #endif

                // $$ = std::make_unique<expression>();
                $$ = std::make_unique<assignment>(std::move($1), std::move($3));

                }
            | literals {

                #ifdef DEBUG_PARSER
                std::cout << "literals: " << cnt++ << "\n";
                #endif

                $$ = std::move($1);

                }
            | binop_expr {
                #ifdef DEBUG_PARSER
                std::cout << "binop_expr: " << cnt++ << "\n";
                #endif

                $$ = std::move($1);

                }
            ;

binop_expr  : expr "+" expr {

                #ifdef DEBUG_PARSER
                std::cout << "expr + expr: " << cnt++ << "\n";
                #endif

                $$ = std::make_unique<binary_operator>('+', std::move($1), std::move($3));

                }
            | expr "-" expr {
                $$ = std::make_unique<expression>();
                }
            | expr "*" expr {
                $$ = std::make_unique<expression>();
                }
            | expr "/" expr {
                $$ = std::make_unique<expression>();
                }
            ;

/* testing out a grammar */
/*
program     : expr { std::cout << "expr: " << cnt++ << "\n"; }
            ;

expr        : "decimal" { std::cout<< "decimal: " << cnt++ << "\n"; $$ = std::move($1); }
            | expr "+" expr { std::cout << "expr + expr: " << cnt++ << "\n"; $$ = std::make_unique<binary_operator>('+', std::move($1), std::move($3)); }
            ;
*/
%%

void yy::parser::error (const location_type& l, const std::string& m) {
  std::cerr << l << ": " << m << '\n';
}