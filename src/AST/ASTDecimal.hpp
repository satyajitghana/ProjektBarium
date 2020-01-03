#pragma once

#include <iostream>
#include "ASTExpr.hpp"

namespace barium {

class ASTDecimal : public ASTExpr {
   public:
    long long value;

    ASTDecimal(long long value) : value(value) {}

    virtual llvm::Value* codeGen(CodeGenContext& context) override;
}

llvm::Value*
ASTDecimal::codeGen(CodeGenContext& context) {
    std::cout << "producing decimal: " << value << "\n";

    return llvm::ConstantInt::get(Type::getInt128Ty(TheContext), value);
};

}  // namespace barium