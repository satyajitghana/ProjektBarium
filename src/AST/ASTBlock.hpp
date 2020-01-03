#pragma once

#include "ASTExpr.hpp"
#include "ASTStmt.hpp"

#include <vector>

namespace barium {

class ASTBlock : public ASTExpr {
    public:
    std::vector<ASTStmt> statements;
    virtual llvm::Value* codegen() override;
};

llvm::Value* ASTBlock::codegen() {
    return nullptr;
}

}