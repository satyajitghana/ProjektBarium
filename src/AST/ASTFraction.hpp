#pragma once

#include "ASTExpr.hpp"

namespace barium {
class ASTFraction : public ASTExpr {
   public:
    long double value;

    ASTFraction(long double value) : value(value) {}

    virtual llvm::Value* codegen() override;
};

llvm::Value*
ASTFraction::codegen() {
    std::cout << "producing fraction: " << value << "\n";

    return llvm::ConstantFP::get(llvm::Type::getFP128Ty(codegen_ctx::TheContext), value);
}

}  // namespace barium
