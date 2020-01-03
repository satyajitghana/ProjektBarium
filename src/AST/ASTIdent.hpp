#pragma once

#include "ASTExpr.hpp"

#include <iostream>
#include <string>

namespace barium {
class ASTIdent : public ASTExpr {
   public:
    std::string name;
    ASTIdent(const std::string& name) : name(name) {}

    virtual llvm::Value* codegen() override;
};

llvm::Value* ASTIdent::codegen() {
    std::cout << "producing a identifier reference: " << name << "\n";

    if (codegen_ctx::Locals().find(name) == codegen_ctx::Locals().end()) {
        std::cerr << "undeclared variable"
                  << "\n";

        return nullptr;
    }

    return nullptr;

    // return new llvm::LoadInst(codegen_ctx::Locals()[name], "", false, codegen_ctx::CurrentBlock());
}

}  // namespace barium
