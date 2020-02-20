#include <cstdlib>
#include <iostream>
#include <memory>

#include "ast_structures.hpp"
#include "code_generator.hpp"
#include "driver.hpp"

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

// #include "lld/Common/LLVM.h"
// #include "lld/Common/Driver.h"

extern std::shared_ptr<block> program_block;

int main(int argc, char* argv[]) {
    using namespace llvm;

    // hide all the preset command line options that llvm takes
    llvm::cl::OptionCategory CompilerCategory(
        "Compiler Options", "Options for controlling the compilation process.");
    llvm::cl::HideUnrelatedOptions(CompilerCategory);

    cl::opt<std::string> InputFilename(cl::Positional, cl::desc("<input file>"),
                                       cl::value_desc("filename"),
                                       cl::init("-"));

    // output file name of the executable and the object file
    cl::opt<std::string> OutputFilename(
        "o", cl::desc("Specify output filename"), cl::value_desc("filename"));

    // parse the command line options
    llvm::cl::ParseCommandLineOptions(
        argc, argv,
        "Barium Compiler\nUses STDIN if <input file> is not specified\n");

    // initiate the driver
    driver drv;
    if (InputFilename.empty()) {
        // parse stdin
        drv.parse("-");
    } else {
        drv.parse(InputFilename);
    }

    // return 0;

    std::string output_file =
        OutputFilename.empty() ? "output" : OutputFilename.getValue();

    codegen_context ctx;

    ctx.generate_code(program_block);

    return 0;

    /*

    // Initialize the Native Target Machine
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmParser();
    llvm::InitializeNativeTargetAsmPrinter();

    auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    codegen_context::TheModule->setTargetTriple(TargetTriple);

    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!Target) {
        std::cerr << Error;
        return 1;
    }

    // we'll be building for generic machine
    auto CPU = "generic";
    auto Features = "";

    llvm::TargetOptions opt;
    auto RM = llvm::Optional<llvm::Reloc::Model>();
    auto TheTargetMachine =
        Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    codegen_context::TheModule->setDataLayout(
        TheTargetMachine->createDataLayout());

    std::error_code EC;
    llvm::raw_fd_ostream dest(output_file + ".o", EC, llvm::sys::fs::OF_None);

    if (EC) {
        std::cerr << "Could not open file: " << EC.message();
        return 1;
    }
    llvm::legacy::PassManager pass;
    auto FileType = llvm::TargetMachine::CodeGenFileType::CGFT_ObjectFile;

    if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        std::cerr << "TheTargetMachine can't emit a file of this type";
        return 1;
    }

    pass.run(*codegen_context::TheModule.get());
    dest.flush();

    std::cerr << "Wrote: " << output_file << "\n";

    std::system(("gcc -no-pie " + output_file + ".o -o " + output_file).c_str());

    std::cerr << "Generated Executable "
              << "output"
              << "\n";
              */

    /* creates executable, but linking doesn't work properly for now
    std::vector<const char*> args;
    args.push_back("barium");
    args.push_back("output.o");

    llvm::ArrayRef<const char*> Args(args);
    lld::elf::link(Args, false);*/
    
}
