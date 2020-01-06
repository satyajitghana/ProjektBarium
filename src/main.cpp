#include <iostream>
#include <memory>

#include "driver.hpp"
#include "ast_structures.hpp"
#include "code_generator.hpp"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/Support/TargetSelect.h"

extern std::shared_ptr<block> program_block;

int main(int argc, char* argv[]) {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();

    driver drv;
    drv.parse("-");

    program_block->code_gen();

    codegen_context ctx;

    ctx.generate_code(program_block);
}
