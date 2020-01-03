#include <iostream>

extern int yylex();
extern int yyparse();

int main(int argc, char* argv[]) {
    // while (true) {
    //     std::cerr << "bison> ";
    // }
    // yylex();
    yyparse();

    return 0;
}
