#pragma once

#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>

#include <memory>
#include <string>
#include <map>
#include <stack>

#include "AST/ASTBlock.hpp"

namespace codegen_ctx {

namespace {
// This is an object that owns LLVM core data structures
llvm::LLVMContext TheContext;
// This is a helper object that makes easy to generate LLVM instructions
llvm::IRBuilder<> Builder(TheContext);

// This is an LLVM construct that contains functions and global variables
std::unique_ptr<llvm::Module> TheModule;

// This map keeps track of which values are defined in the current scope
std::map<std::string, llvm::Value *> NamedValues;
}

// initializes the above variables
void InitializeModule();

struct codegen_block {
    std::shared_ptr<llvm::BasicBlock> block;
    std::shared_ptr<llvm::Value> returnValue;
    std::map<std::string, llvm::Value*> locals;
};

namespace {
std::stack<std::unique_ptr<codegen_block>> blocks;
std::unique_ptr<llvm::Function> mainFunction;
}

void GenerateCode(barium::ASTBlock& root);
llvm::GenericValue runCode();
std::map<std::string, llvm::Value*> Locals();
std::shared_ptr<llvm::BasicBlock> CurrentBlock();
void PushBlock(std::unique_ptr<llvm::BasicBlock> block);
void PopBlock();
void SetCurrentReturnValue(std::shared_ptr<llvm::Value> value);
std::shared_ptr<llvm::Value> GetCurrentReturnValue();

}