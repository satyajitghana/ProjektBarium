#pragma once

#include "ASTNode.hpp"

namespace barium {
class ASTExpr : public ASTNode {
    public:
    virtual llvm::Value* codegen() = 0;;
};

}  // namespace barium
