#pragma once

#include "../CodeGenContext.hpp"
#include "llvm/IR/BasicBlock.h"

namespace barium {

/* Basic class for all expression nodes */
class ASTNode {
   public:
    virtual ~ASTNode() {}
    virtual llvm::Value* codeGen(CodeGenContext& context) = 0;
};

}  // namespace barium
