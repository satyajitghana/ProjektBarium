#include "code_generator.hpp"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/Support/TargetSelect.h"

// declare all the static variables
// this will also define their storage size
// and that's how static variables are instantiated

// LLVMContext holds a lot of LLVM Data Structures like type and constant value tables
llvm::LLVMContext codegen_context::TheContext;

// Builder makes it easy to generate LLVM IR, IR Builder class keeps track of wehere to insert instrs. to 
llvm::IRBuilder<> codegen_context::Builder(codegen_context::TheContext);

// Module contains functions and global variables
std::unique_ptr<llvm::Module> codegen_context::TheModule = std::make_unique<llvm::Module>("barium-jit", codegen_context::TheContext);
// llvm::Module* codegen_context::TheModule = nullptr;

// NamedValues keeps track of which values are defined in the current scope. It's a symbol table for the code
std::map<std::string, llvm::Value *> codegen_context::NamedValues;

std::unique_ptr<llvm::legacy::FunctionPassManager> codegen_context::TheFPM;

void codegen_context::generate_code(std::shared_ptr<block> root) {

    /*
    // Create the JIT Engine
    auto myModule = std::make_unique<llvm::Module>("Bairum-JIT", codegen_context::TheContext);
    // auto* module = myModule.get();
    codegen_context::TheModule = myModule.get();

    llvm::TargetOptions Opts;
    std::unique_ptr<llvm::RTDyldMemoryManager> MemMgr(new llvm::SectionMemoryManager());

    // Create JIT engine
    llvm::EngineBuilder factory(std::move(myModule));
    factory.setEngineKind(llvm::EngineKind::JIT);
    factory.setTargetOptions(Opts);
    factory.setMCJITMemoryManager(std::move(MemMgr));
    auto executionEngine = std::unique_ptr<llvm::ExecutionEngine>(factory.create());
    // seg fault
    codegen_context::TheModule->setDataLayout(executionEngine->getDataLayout());
    */

    // create the entry function aka the main function

    // create the argument list
    std::vector<llvm::Type*> argTypes;
    // create the function prototype/signature
    llvm::FunctionType* funcType = llvm::FunctionType::get(codegen_context::Builder.getVoidTy(), argTypes, false);
    
    // create the main_function
    this->main_function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", codegen_context::TheModule.get());

    // create the entry block and fill it with appropriate code
    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(codegen_context::TheContext, "entry", this->main_function, 0);

    this->blocks.emplace(std::make_unique<basic_block>(entryBlock));
    // the code will be inserted into entry block now
    codegen_context::Builder.SetInsertPoint(entryBlock);
    // root->code_gen(); // generate code for the entire tree
    codegen_context::Builder.CreateRet(root->code_gen());
    this->blocks.pop();

    // print the IR
    codegen_context::TheModule->print(llvm::errs(), nullptr);

}
