%{
    #include <iostream>
    #include <memory>
    #include "AST/ASTIdent.hpp"
    #include "AST/ASTBlock.hpp"
    #include "AST/ASTExpr.hpp"
    #include "AST/ASTStmt.hpp"
    #include "AST/ASTAssignment.hpp"
    #include "AST/ASTBinaryOp.hpp"
    #include "AST/ASTDecimal.hpp"
    #include "AST/ASTFraction.hpp"

    using namespace barium;

    extern int yylex();
    extern int yyparse();

    void yyerror(const char *s) { std::cerr << "Error " << s << std::endl; }

    std::unique_ptr<ASTBlock> programBlock; // root of the AST
%}

// tokens are stored in yytype of the below union
%union {
    int token;
    std::unique_ptr<std::string> string;
    std::unique_ptr<barium::ASTBlock> block; 
    std::unique_ptr<barium::ASTExpr> expr;
    std::unique_ptr<barium::ASTStmt> stmt;
}

/* terminal symbols */
%token <token> TPLUS TMINUS TMUL TDIV
%token <string> TIDENT TDECIMAL TFRACTION
%token <token> TEQ

/* non-terminals */
%type <ident> ident
%type <block> stmts
%type <expr> expr numeric
%type <stmt> stmt


/* operator precedence */
%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%
program : stmts { programBlock = std::move($1); }
        ;

stmts   : stmt { $$ = std::make_unique<ASTBlock>(); $$->statements.push_back($<stmt>1); }
        | stmts stmt { $1->statements.push_back($<stmt>2); }
        ;

stmt    : expr { $$ = std::make_unique<ASTExpr>(std::move($1)); }
        ;

numeric : TDECIMAL  { $$ = std::make_unique<ASTDecimal>(atol($1->c_str())); }
        | TFRACTION { $$ = std::make_unique<ASTFraction>(atof($1->c_str())); }
        ;

expr    : numeric
        | expr TPLUS expr { $$ = std::make_unique<ASTBinaryOp>(std::move($1), $2, std::move($2)) }
        ;

%%