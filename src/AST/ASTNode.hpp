#pragma once

#include "../codegen_context.hpp"
#include "llvm/IR/BasicBlock.h"

namespace barium {

/* Basic class for all expression nodes */
class ASTNode {
   public:
    virtual ~ASTNode() {}
    virtual llvm::Value* codegen() = 0;
};

}  // namespace barium
