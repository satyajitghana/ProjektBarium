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
    LPAREN  "("
    RPAREN  ")"
    COMMA   ","

%token  <std::unique_ptr<identifier>>   IDENT       "identifier"
%token  <std::unique_ptr<decimal>>      DECIMAL     "decimal"
%token  <std::unique_ptr<fraction>>     FRACTION    "fraction"
%token  <std::unique_ptr<stringlit>>    STRINGLIT   "stringlit"
%nterm  <std::unique_ptr<expression>>   expr
%nterm  <std::unique_ptr<expression>>   literals
%nterm  <std::unique_ptr<expression>>   binop_expr
%nterm  <std::unique_ptr<block>>        stmts
%nterm  <std::unique_ptr<block>>        program
%nterm  <std::unique_ptr<statement>>    stmt
%nterm  <std::unique_ptr<std::vector<std::unique_ptr<expression>>>> call_args

%printer { yyo << $$; } <*>;

%start program;

%code {
    #define DEBUG_PARSER
    // #undef DEBUG_PARSER
}

%%

%left "+" "-";
%left "*" "/";

program     : stmts {

                #ifdef DEBUG_PARSER
                std::cout << "program: " << cnt++ << "\n";
                #endif

                std::cout << $1.get() << '\n';

                program_block = std::move($1);

                std::cout << program_block.get() << '\n';

                }
            ;

stmts[block]       : stmt {

                #ifdef DEBUG_PARSER
                std::cout << "stmt: " << cnt++ << "\n";
                #endif

                $block = std::make_unique<block>();

                $block->statements.emplace_back(std::move($1));

                }
            | stmts[meow] stmt {

                #ifdef DEBUG_PARSER
                std::cout << "stmts stmt: " << cnt++ << "\n";
                #endif

                $meow->statements.emplace_back(std::move($2));

                // i added this because i std::move everytime and this moves the$block also
                // so i std::move back $meow to block to retain the address of main block
                // it was becoming null before, added null check in main.cpp as well
                // - shadowleaf

                $block = std::move($meow);

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

                $$ = std::move($1);
                
                }
            | "stringlit" {
                
                #ifdef DEBUG_PARSER
                std::cout << "stringlit: " << cnt++ << "\n";
                #endif

                $$ = std::move($1);

            }
            ;

expr        : "identifier" "=" expr {

                // assignment
                #ifdef DEBUG_PARSER
                std::cout << "identifier = expr: " << cnt++ << "\n";
                #endif

                $$ = std::make_unique<assignment>(std::move($1), std::move($3));

                }

            | "identifier" "(" call_args ")" {
                // function call
                #ifdef DEBUG_PARSER
                std::cout << "identifier(call_args): " << cnt++ << "\n";
                #endif

                $$ = std::make_unique<function_call>(std::move($1), std::move($3));

                }
            | "identifier" {
                // just an identifier
                #ifdef DEBUG_PARSER
                std::cout << "identifier: " << cnt++ << "\n";
                #endif

                }

            | literals {

                // literal, either decimal or fractional
                #ifdef DEBUG_PARSER
                std::cout << "literals: " << cnt++ << "\n";
                #endif

                $$ = std::move($1);

                }
            | binop_expr {

                // some binary operation
                #ifdef DEBUG_PARSER
                std::cout << "binop_expr: " << cnt++ << "\n";
                #endif

                $$ = std::move($1);

                }
            | "(" expr ")" { $$ = std::move($2); }
            ;

call_args   : /*blank*/ {
                #ifdef DEBUG_PARSER
                std::cout << "call_args<blank>: " << cnt++ << "\n";
                #endif
                $$ = std::make_unique<std::vector<std::unique_ptr<expression>>>();
                }
            | expr {
                #ifdef DEBUG_PARSER
                std::cout << "call_args: " << cnt++ << "\n";
                #endif
                $$ = std::make_unique<std::vector<std::unique_ptr<expression>>>();
                $$->push_back(std::move($1));

                }
            | call_args "," expr {
            
                #ifdef DEBUG_PARSER
                std::cout << "call_args, args: " << cnt++ << "\n";
                #endif
                $1->push_back(std::move($3));

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