#pragma once

#include "ast_structures.hpp"

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <stack>

#include "extern_func.hpp"

class basic_block {
    public:
    llvm::BasicBlock* block;
    std::map<std::string, llvm::Value*> locals;

    basic_block(llvm::BasicBlock* block) : block(block) {}
};

class codegen_context {
    public:
    std::stack<std::unique_ptr<basic_block>> blocks;
    llvm::Function* main_function;
    // store the llvm::Function*, pointer to the extern function
    std::vector<std::pair<llvm::Function*, void*>> inbuilts_info;

    // as explained in llvm tutorial
    static llvm::LLVMContext TheContext;
    static llvm::IRBuilder<> Builder;
    static std::unique_ptr<llvm::Module> TheModule;
    // static llvm::Module* TheModule;
    static std::map<std::string, llvm::Value *> NamedValues;
    static std::unique_ptr<llvm::legacy::FunctionPassManager> TheFPM;

    void generate_code(std::shared_ptr<block> root);

    llvm::GenericValue run_code();

    void setup_inbuilts();

    codegen_context();

};