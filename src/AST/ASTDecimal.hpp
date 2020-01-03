#pragma once

#include <iostream>
#include "ASTExpr.hpp"

namespace barium {

class ASTDecimal : public ASTExpr {
   public:
    long long value;

    ASTDecimal(long long value) : value(value) {}

    virtual llvm::Value* codegen() override;
};

llvm::Value*
ASTDecimal::codegen() {
    std::cout << "producing decimal: " << value << "\n";

    return llvm::ConstantInt::get(llvm::Type::getInt128Ty(codegen_ctx::TheContext), value);
};

}  // namespace barium