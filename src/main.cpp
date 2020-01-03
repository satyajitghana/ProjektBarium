#include <iostream>

extern int yylex();
extern int yyparse();

#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>

#include "codegen_context.hpp"

int main(int argc, char* argv[]) {
    // yyparse();
    llvm::InitializeNativeTarget();
	llvm::InitializeNativeTargetAsmPrinter();
	llvm::InitializeNativeTargetAsmParser();

    codegen_ctx::InitializeModule();

    return 0;
}
