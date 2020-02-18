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
    AND     "and"
    OR      "or"
    NOT     "not"
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
%nterm  <std::unique_ptr<expression>>   unaryop_expr
%nterm  <std::unique_ptr<block>>        stmts
%nterm  <std::unique_ptr<block>>        program
%nterm  <std::unique_ptr<statement>>    stmt
%nterm  <std::unique_ptr<std::vector<std::unique_ptr<expression>>>> call_args
%nterm  <std::unique_ptr<variable_declaration>> var_decl

%printer { yyo << $$; } <*>;

%start program;

%code {
    #define DEBUG_PARSER
    // #undef DEBUG_PARSER
}

%%

// left associativity

%left "+" "-";
%left "*" "/";

// program consists of statements

program     : stmts {

                #ifdef DEBUG_PARSER
                std::cout << "program: " << cnt++ << "\n";
                #endif

                std::cout << $1.get() << '\n';

                program_block = std::move($1);

                std::cout << program_block.get() << '\n';

                }
            ;


// statements can consist of single or multiple statements

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

// statement can be an expression or an variable declaration

stmt        : expr {
                #ifdef DEBUG_PARSER
                std::cout << "expr: " << cnt++ << "\n";
                #endif

                $$ = std::make_unique<expr_statement>(std::move($1));

                }
            | var_decl {

                #ifdef DEBUG_PARSER
                std::cout << "var_decl: " << cnt++ << "\n";
                #endif

                $$ = std::move($1);
            }
            ;

// variable declaration and/or assignment

var_decl    : "identifier" "identifier" {
                #ifdef DEBUG_PARSER
                std::cout << "var_decl ident ident: " << cnt++ << "\n";
                #endif
                $$ = std::make_unique<variable_declaration>(std::move($1), std::move($2));
            }    
            | "identifier" "identifier" "=" expr {
                #ifdef DEBUG_PARSER
                std::cout << "var_decl ident ident = expr: " << cnt++ << "\n";
                #endif
                $$ = std::make_unique<variable_declaration>(std::move($1), std::move($2), std::move($4));
            }
            ;

// all the literals, like integers, fractions and string literals

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

// all the expression statements

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
                std::cout << $1->name << '\n';
                #endif

                $$ = std::make_unique<function_call>(std::move($1), std::move($3));

                }
            | "identifier" {
                // just an identifier
                #ifdef DEBUG_PARSER
                std::cout << "identifier: " << cnt++ << "\n";
                #endif


                $$ = std::move($1);

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
            | unaryop_expr {
                // a boolean expression
                #ifdef DEBUG_PARSER
                std::cout << "uparyop_expr: " << cnt++ << '\n';
                #endif

                $$ = std::move($1);
            }
            | "(" expr ")" { $$ = std::move($2); }
            ;

// call arguments of a function
// can be blank

call_args[args_list]   : /*blank*/ {
                #ifdef DEBUG_PARSER
                std::cout << "call_args<blank>: " << cnt++ << "\n";
                #endif
                $args_list = std::make_unique<std::vector<std::unique_ptr<expression>>>();
                }
            | expr {
                #ifdef DEBUG_PARSER
                std::cout << "call_args: " << cnt++ << "\n";
                #endif
                $args_list = std::make_unique<std::vector<std::unique_ptr<expression>>>();
                $args_list->push_back(std::move($1));

                }
            | call_args[arg] "," expr {
            
                #ifdef DEBUG_PARSER
                std::cout << "call_args, args: " << cnt++ << "\n";
                #endif
                $arg->push_back(std::move($3));

                $args_list = std::move($arg);

                }
            ;

// binary operators

binop_expr  : expr "and" expr {

                $$ = std::make_unique<binary_operator>('&', std::move($1), std::move($3));

                }
            | expr "or" expr {

                $$ = std::make_unique<binary_operator>('|', std::move($1), std::move($3));

                }
            | expr "+" expr {

                #ifdef DEBUG_PARSER
                std::cout << "expr + expr: " << cnt++ << "\n";
                #endif

                $$ = std::make_unique<binary_operator>('+', std::move($1), std::move($3));

                }
            | expr "-" expr {
                $$ = std::make_unique<binary_operator>('-', std::move($1), std::move($3));
                }
            | expr "*" expr {
                $$ = std::make_unique<binary_operator>('*', std::move($1), std::move($3));
                }
            | expr "/" expr {
                $$ = std::make_unique<binary_operator>('/', std::move($1), std::move($3));
                }
            ;

// unary operations

unaryop_expr    : "not" expr {
                    $$ = std::make_unique<unary_operator>('!', std::move($2));
                    }
                ;

// // boolean expression

// boolean_expr    : expr "and" expr {

//                     }
//                 | expr "or" expr {

//                     }
//                 | expr "xor" expr {

//                     }

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