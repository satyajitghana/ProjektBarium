#include "codegen_context.hpp"

void codegen_ctx::InitializeModule() {
    TheModule = std::make_unique<llvm::Module>("Barium-LLVM", TheContext);
}

std::map<std::string, llvm::Value*> codegen_ctx::Locals() { return blocks.top()->locals; }

std::shared_ptr<llvm::BasicBlock> codegen_ctx::CurrentBlock() { return blocks.top()->block; }

void codegen_ctx::PushBlock(std::unique_ptr<llvm::BasicBlock> block) {
    blocks.push(std::make_unique<codegen_ctx::codegen_block>());
    blocks.top()->returnValue = nullptr;
    blocks.top()->block = std::move(block);
}

void codegen_ctx::PopBlock() {
    blocks.pop();
}

void codegen_ctx::SetCurrentReturnValue(std::shared_ptr<llvm::Value> value) {
    blocks.top()->returnValue = std::move(value);
}

std::shared_ptr<llvm::Value> codegen_ctx::GetCurrentReturnValue() {
    return blocks.top()->returnValue;
}