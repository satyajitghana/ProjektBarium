#pragma once

#include "ASTExpr.hpp"

#include <iostream>
#include <string>

namespace barium {
class ASTIdent : public ASTExpr {
   public:
    std::string name;
    ASTIdent(const std::string& name) : name(name) {}

    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};

llvm::Value* ASTIdent::codeGen(CodeGenContext& context) {
    std::cout << "producing a identifier reference: " << name << "\n";

    if (context.locals().find(name) == context.locals().end()) {
        std::cerr << "undeclared variable"
                  << "\n";

        return nullptr;
    }

    return new LoadInst(context.locals()[name], "", false, context.currentBlock());
}

}  // namespace barium
