%{
    #include <string>
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror

    #include "driver.hpp"
    #include "parser.hpp"
    #include "ast_structures.hpp"
%}

%option noyywrap nounput noinput batch

%{
    yy::parser::symbol_type make_DECIMAL(const std::string& s, const yy::parser::location_type& loc);
    yy::parser::symbol_type make_FRACTION(const std::string& s, const yy::parser::location_type& loc);
    yy::parser::symbol_type make_IDENT(const std::string& s, const yy::parser::location_type& loc);
%}

ident       [a-zA-Z_][a-zA-Z_0-9]*
num         [0-9]
blank       [ \t\r]

%{
    // runs each time a pattern is matched
    #define YY_USER_ACTION  loc.columns(yyleng);
%}

%%

%{
    yy::location& loc = drv.location;
    loc.step();
%}

{blank}+            { loc.step(); }
\n+                 { loc.lines(yyleng); loc.step(); }
"+"                 { return yy::parser::make_PLUS(loc); } 
"-"                 { return yy::parser::make_MINUS(loc); }
"*"                 { return yy::parser::make_MUL(loc); }   
"/"                 { return yy::parser::make_DIV(loc); }
"="                 { return yy::parser::make_ASSIGN(loc); }
{num}+\.{num}*      { return make_FRACTION(yytext, loc); }
-?{num}+            { return make_DECIMAL(yytext, loc); }
{ident}             { return make_IDENT(yytext, loc); }
"("                 { return yy::parser::make_LPAREN(loc); }
")"                 { return yy::parser::make_RPAREN(loc); }
","                 { return yy::parser::make_COMMA(loc); }
\"(\\.|[^"\\])*\"   { return yy::parser::make_STRINGLIT(std::make_unique<stringlit>(yytext), loc); }
#.*                 /* single line comment */
.                   { throw yy::parser::syntax_error
                      (loc, "invalid character: " + std::string(yytext));
                    }
<<EOF>>             { return yy::parser::make_END(loc); }

%%

yy::parser::symbol_type make_DECIMAL(const std::string& s, const yy::parser::location_type& loc) {
  std::unique_ptr<decimal> temp = std::make_unique<decimal>(std::strtoll(yytext, NULL, 10));
  return yy::parser::make_DECIMAL(std::move(temp), loc);
}

yy::parser::symbol_type make_FRACTION(const std::string& s, const yy::parser::location_type& loc) {
  std::unique_ptr<fraction> temp = std::make_unique<fraction>(std::strtold(yytext, NULL));
  return yy::parser::make_FRACTION(std::move(temp), loc);
}

yy::parser::symbol_type make_IDENT(const std::string& s, const yy::parser::location_type& loc) {
  std::unique_ptr<identifier> temp = std::make_unique<identifier>(s);
  return yy::parser::make_IDENT(std::move(temp), loc);
}

void driver::scan_begin() {
  if (file.empty() || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen(file.c_str(), "r"))) {
      std::cerr << "cannot open " << file << ": " << strerror(errno) << '\n';
      exit (EXIT_FAILURE);
    }
}

void driver::scan_end() {
  fclose(yyin);
}