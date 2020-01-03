#pragma once

#include "ASTExpr.hpp"
#include "ASTIdent.hpp"

#include <memory>
#include <vector>

namespace barium {
class ASTFunctionCall : public ASTExpr {
   public:
    const ASTIdent& id;
    std::vector<std::unique_ptr<ASTExpr>> args;

    /* Function Call with argument */
    ASTFunctionCall(const ASTIdent& id, std::vector<std::unique_ptr<ASTExpr>> args) : id(id), args(args) {}
    /* Function Call without any arguments */
    ASTFunctionCall(const ASTIdent& id) : id(id) {}

    virtual llvm::Value* codeGen(CodeGenContext& context) override;
};

llvm::Value* ASTFunctionCall::codeGen(CodeGenContext& context) {
    llvm::Function* function = context.module->getFunction(id.name.c_str());
}

}  // namespace barium
