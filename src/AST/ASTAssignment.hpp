#pragma once

#include "ASTExpr.hpp"
#include "ASTIdent.hpp"

namespace barium {

class ASTAssignment : public ASTExpr {
    public:
    ASTIdent& lhs;
    ASTExpr& rhs;

    ASTAssignment(ASTIdent& lhs, ASTExpr& rhs) : lhs(lhs), rhs(rhs) { }

    virtual llvm::Value* codegen() override;
};

llvm::Value* ASTAssignment::codegen() {
    std::cout << "producing assignment for " << lhs.name << "\n";

    return nullptr;
    
}

}