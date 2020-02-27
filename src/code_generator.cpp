#include "code_generator.hpp"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
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
std::map<std::string, llvm::Value*> codegen_context::NamedValues;

std::unique_ptr<llvm::legacy::FunctionPassManager> codegen_context::TheFPM;

codegen_context::codegen_context() {
    // Initialize Native Target
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmParser();
    llvm::InitializeNativeTargetAsmPrinter();
}

void codegen_context::generate_code(std::shared_ptr<block> root) {
    std::cout << "Generating LLVM IR: "
              << "\n";

    std::cout << "setting up in-builts\n";

    // add the inbuilt functions to the module
    setup_inbuilts();

    // create the argument list
    std::vector<llvm::Type*> argTypes;
    // create the function prototype/signature
    llvm::FunctionType* funcType = llvm::FunctionType::get(codegen_context::Builder.getInt64Ty(), argTypes, false);

    // create the main_function
    this->main_function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", codegen_context::TheModule.get());

    // create the entry block and fill it with appropriate code
    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(codegen_context::TheContext, "entry", this->main_function, 0);

    this->blocks.emplace(std::make_unique<basic_block>(entryBlock));
    // the code will be inserted into entry block now
    codegen_context::Builder.SetInsertPoint(entryBlock);
    root->code_gen(this);  // generate code for the entire tree
    // codegen_context::Builder.CreateRet(blocks.top()->block);

    // set the return of main function to decimal 1
    codegen_context::Builder.CreateRet(llvm::ConstantInt::get(codegen_context::TheContext,
                                                              llvm::APInt(64, 1)));
    this->blocks.pop();

    // print the IR
    codegen_context::TheModule->print(llvm::errs(), nullptr);
}

llvm::GenericValue codegen_context::run_code() {
    using namespace llvm;
    std::cout << "Running Code!" << '\n';

    TargetOptions Opts;

    auto* module = this->TheModule.get();
    std::unique_ptr<RTDyldMemoryManager> MemMgr(new llvm::SectionMemoryManager());

    // Create the JIT Engine
    EngineBuilder factory(std::move(this->TheModule));
    factory.setEngineKind(EngineKind::JIT);
    factory.setTargetOptions(Opts);
    factory.setMCJITMemoryManager(std::move(MemMgr));

    // setup the execution engine
    auto execution_engine = std::unique_ptr<ExecutionEngine>(factory.create());

    // set the memory layout of the module to same as of the engine
    module->setDataLayout(execution_engine->getDataLayout());

    // add the inbuilt functions to the execution engine
    for (auto [fun, fun_addr] : this->inbuilts_info) {
        execution_engine->addGlobalMapping(fun, fun_addr);
    }

    execution_engine->finalizeObject();

    std::vector<GenericValue> noargs;

    std::cout << "hi" << '\n';

    // fetch the returned value of the main funciton
    GenericValue val_ret = execution_engine->runFunction(this->main_function, noargs);

    std::cout << "Code was run!" << '\n';

    return val_ret;
}

void codegen_context::setup_inbuilts() {
    using namespace llvm;

    // setup "display" function

    // arg: int8 pointer
    std::vector<llvm::Type*> display_arg_types(1, codegen_context::Builder.getInt8PtrTy());
    // return: Void, Params: int8 pointer, isVarArg: true
    FunctionType* display_ft = FunctionType::get(codegen_context::Builder.getVoidTy(), display_arg_types, true);

    Function* display_func = Function::Create(display_ft, Function::ExternalLinkage, "display", codegen_context::TheModule.get());

    auto i = display_func->arg_begin();
    if (i != display_func->arg_end()) {
        i->setName("format_str");
    }

    this->inbuilts_info.push_back({display_func, (void*)display});

    // setup "displayln" function
    Function* displayln_func = Function::Create(display_ft, Function::ExternalLinkage, "displayln", codegen_context::TheModule.get());

    i = displayln_func->arg_begin();
    if (i != displayln_func->arg_end()) {
        i->setName("format_str");
    }

    this->inbuilts_info.push_back({displayln_func, (void*)displayln});
}

llvm::Type* codegen_context::type_of(const identifier* type) {
    if (type->name.compare("decimal") == 0) {
        return this->Builder.getInt64Ty();
    } else if (type->name.compare("fraction") == 0) {
        return this->Builder.getDoubleTy();
    }

    return this->Builder.getVoidTy();
}
