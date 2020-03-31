%skeleton "lalr1.cc"
%require "3.5"
%language "c++"

%defines 

// variant will make sure we can use our non-trivial types
%define api.value.type variant
%define api.token.constructor
%define parse.assert

// this will be added to the parser.cpp file, cyclic-dependecy is resolved by using
// forward declaration of the driver class, this is added verbatim
// if you want to declare any variables do not do in this requires section
%code requires {
    #include <string>
    #include <memory>
    #include <typeinfo>

    class driver;

    #include "ast/ast_structures.hpp"
    // love you c++ gods, g++ gave me much help in debugging
    // <3
    #include "visitor/visitor.hpp"
    #include "visitor/visitor_pprint.hpp"
    #include "external/loguru.hpp"

    static int cnt = 0;
}

// parsing context
%param { driver& drv }

// for location tracking
%locations
%verbose

// because we'll be using the driver class methods
%code {
    #include "driver/driver.hpp"

    std::shared_ptr<block> program_block;

    visitor_pprint v_pprint;
}

// to make sure there are no conflicts prepend TOK_
%define api.token.prefix{TOK_}
%token 
    END  0  "end of file"
    AND     "and"
    OR      "or"
    NOT     "not"
    FOR     "for"
    IN      "in"
    RANGE   "range"
    IF      "if"
    ELSE    "else"
    ASSIGN  "="
    PLUS    "+"
    MINUS   "-"
    MUL     "*"
    DIV     "/"
    LPAREN  "("
    RPAREN  ")"
    LBRACE  "{"
    RBRACE  "}"
    LBRACKET "["
    RBRACKET "]"
    COMMA   ","
    GRT     ">"
    GRTEQ   ">="
    LES     "<"
    LESEQ   "<="
    NOTEQ   "!="
    EQUAL   "=="

%token  <std::unique_ptr<identifier>>   IDENT       "identifier"
%token  <std::unique_ptr<decimal>>      DECIMAL     "decimal"
%token  <std::unique_ptr<fraction>>     FRACTION    "fraction"
%token  <std::unique_ptr<stringlit>>    STRINGLIT   "stringlit"
%nterm  <std::unique_ptr<identifier>>   identifier // add this for verbosity
%nterm  <std::unique_ptr<expression>>   expr
%nterm  <std::unique_ptr<expression>>   literals
%nterm  <std::unique_ptr<expression>>   binop_expr
%nterm  <std::unique_ptr<expression>>   unaryop_expr
%nterm  <std::unique_ptr<expression>>   compare_expr
%nterm  <std::unique_ptr<block>>        stmts
%nterm  <std::unique_ptr<block>>        program
%nterm  <std::unique_ptr<block>>        block
%nterm  <std::unique_ptr<statement>>    stmt
%nterm  <std::unique_ptr<statement>>    conditional
%nterm  <std::unique_ptr<statement>>    for_loop
%nterm  <std::unique_ptr<statement>>    for_range
%nterm  <std::unique_ptr<std::vector<std::unique_ptr<expression>>>> call_args
%nterm  <std::unique_ptr<variable_declaration>> var_decl
%nterm  <std::unique_ptr<array_access>> array_access

%printer { yyo << $$; } <*>;

%start program;

%code {
    #define DEBUG_PARSER
    #undef DEBUG_PARSER
}

%%

// left associativity

%left "+" "-";
%left "*" "/";

// program consists of statements

program     : stmts {

                program_block = std::move($1);
                program_block->accept(v_pprint);

                }
            ;


// statements can consist of single or multiple statements

stmts[block]       : stmt {

                $block = std::make_unique<block>();

                $block->statements.emplace_back(std::move($1));
                $$->accept(v_pprint);

                }
            | stmts[meow] stmt {

                $meow->statements.emplace_back(std::move($2));

                // i added this because i std::move everytime and this moves the $block also
                // so i std::move back $meow to block to retain the address of main block
                // it was becoming null before, added null check in main.cpp as well
                // - shadowleaf

                $block = std::move($meow);

                }
            ;

// statement can be an expression or an variable declaration

stmt        : expr {
                $$ = std::make_unique<expr_statement>(std::move($1));
                $$->accept(v_pprint);
                }
            | var_decl {
                $$ = std::move($1);
                }
            | conditional {
                $$ = std::move($1);
                 }
            | for_loop {
                $$ = std::move($1);
                $$->accept(v_pprint);
                }
            | for_range {
                $$ = std::move($1);
                $$->accept(v_pprint);    
            }
            
            ;

// for loops

for_loop    : "for" "(" expr "," expr "," expr ")" block {
                $$ = std::make_unique<for_loop>(std::move($3), std::move($5), std::move($7), std::move($9));
            }
            ;

for_range   : "for" identifier "in" "range" "decimal" block {
                $$ = std::make_unique<for_range>(std::move($2), std::move($5), std::move($6));
            }
            ;

// a block

block       : "{" stmts "}" {
                    $$ = std::move($2);
                    $$->accept(v_pprint);
                    }
            ;

// conditional statement

conditional     : "if" expr block "else" block {
                    $$ = std::make_unique<conditional>(std::move($2), std::move($3), std::move($5));
                    $$->accept(v_pprint);
                    }
                | "if" expr block {
                    $$ = std::make_unique<conditional>(std::move($2), std::move($3));
                    $$->accept(v_pprint);
                }
                ;

// variable declaration and/or assignment

var_decl    : "identifier" "identifier" {
                $$ = std::make_unique<variable_declaration>(std::move($1), std::move($2));
                $$->accept(v_pprint);
            }    
            | "identifier" "identifier" "=" expr {
                $$ = std::make_unique<variable_declaration>(std::move($1), std::move($2), std::move($4));
                $$->accept(v_pprint);
            }
            ;

// all the literals, like integers, fractions and string literals

literals    : "decimal"  {
                
                $$ = std::move($1);
                // LOG_S(INFO) << "found decimal at " << @1.begin.line << "." << @1.begin.column;
                $$->accept(v_pprint);
                
                }
            | "fraction" {

                $$ = std::move($1);
                $$->accept(v_pprint);
                
                }
            | "stringlit" {

                $$ = std::move($1);
                $$->accept(v_pprint);

            }
            ;

// all the expression statements

expr        : identifier "=" expr {

                $$ = std::make_unique<assignment>(std::move($1), std::move($3));
                $$->accept(v_pprint);

                }

            | identifier "(" call_args ")" {
                // function call

                $$ = std::make_unique<function_call>(std::move($1), std::move($3));
                $$->accept(v_pprint);

                }
            | identifier {
                // just an identifier

                $$ = std::move($1);
                $$->accept(v_pprint);

                }

            | literals {

                // literal, either decimal or fractional

                $$ = std::move($1);

                }
            | binop_expr {

                // some binary operation (numeric, not boolean)

                $$ = std::move($1);
                $$->accept(v_pprint);
                }
            | unaryop_expr {
                // a and or not, unary boolean expression

                $$ = std::move($1);
                }
            | compare_expr {
                // a comparison expression

                $$ = std::move($1);
                }
            | array_access {
                // accessing an element of array

                $$ = std::move($1);
                }
            | "(" expr ")" { 
                $$ = std::move($2);
                $$->accept(v_pprint);
                }
            ;

identifier  : "identifier" { $$ = std::move($1); $$->accept(v_pprint); }

// call arguments of a function
// can be blank

call_args[args_list]   : /*blank*/ {
                $args_list = std::make_unique<std::vector<std::unique_ptr<expression>>>();
                }
            | expr {
                $args_list = std::make_unique<std::vector<std::unique_ptr<expression>>>();
                $args_list->push_back(std::move($1));
                }
            | call_args[arg] "," expr {
                $arg->push_back(std::move($3));
                $args_list = std::move($arg);
                }
            ;

// array access for arr[0], arr[<some expr that evaluate to decimal>]
// or for the future can also be arr['string'] for maps
array_access    : identifier "[" expr "]" {
                    $$ = std::make_unique<array_access>(std::move($1), std::move($3));
                    $$->accept(v_pprint);
                    }
                | array_access "[" expr "]" {
                    $$ = std::make_unique<array_access>(std::move($1), std::move($3));
                    $$->accept(v_pprint);
                }
                ;

// binary operators

binop_expr  : expr "and" expr {

                $$ = std::make_unique<binary_operator>('&', std::move($1), std::move($3), @$);
                $$->accept(v_pprint);

                }
            | expr "or" expr {

                $$ = std::make_unique<binary_operator>('|', std::move($1), std::move($3), @$);
                $$->accept(v_pprint);

                }
            | expr "+" expr {
                $$ = std::make_unique<binary_operator>('+', std::move($1), std::move($3), @$);
                $$->accept(v_pprint);

                }
            | expr "-" expr {
                $$ = std::make_unique<binary_operator>('-', std::move($1), std::move($3), @$);
                $$->accept(v_pprint);
                }
            | expr "*" expr {
                $$ = std::make_unique<binary_operator>('*', std::move($1), std::move($3), @$);
                $$->accept(v_pprint);
                }
            | expr "/" expr {
                $$ = std::make_unique<binary_operator>('/', std::move($1), std::move($3), @$);
                $$->accept(v_pprint);
                }
            ;

// binary boolean comparison operators
compare_expr    :   expr ">" expr {
                        $$ = std::make_unique<comp_operator>(">", std::move($1), std::move($3));
                        $$->accept(v_pprint);
                    }
                |   expr ">=" expr {
                        $$ = std::make_unique<comp_operator>(">=", std::move($1), std::move($3));
                        $$->accept(v_pprint);
                    }
                |   expr "<" expr {

                        $$ = std::make_unique<comp_operator>("<", std::move($1), std::move($3));
                        $$->accept(v_pprint);
                    }
                |   expr "<=" expr {

                        $$ = std::make_unique<comp_operator>("<=", std::move($1), std::move($3));
                        $$->accept(v_pprint);
                    }
                |   expr "==" expr {

                        $$ = std::make_unique<comp_operator>("==", std::move($1), std::move($3));
                        $$->accept(v_pprint);
                    }
                |   expr "!=" expr {

                        $$ = std::make_unique<comp_operator>("!=", std::move($1), std::move($3));
                        $$->accept(v_pprint);
                }
                ;

// unary operations

unaryop_expr    : "not" expr {
                    $$ = std::make_unique<unary_operator>('!', std::move($2), @$);
                    $$->accept(v_pprint);
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