#pragma once

#include <iostream>
#include "ASTExpr.hpp"

#include "parser.hpp"

namespace barium {
class ASTBinaryOp : public ASTExpr {
    public:
    int op;
    ASTExpr& LHS;
    ASTExpr& RHS;

    ASTBinaryOp(ASTExpr& lhs, int op, ASTExpr& rhs) : LHS(lhs), RHS(rhs), op(op) {}

    virtual llvm::Value* codegen() override;
};

llvm::Value* ASTBinaryOp::codegen() {
    std::cout << "producing binary operation " << op << "\n";

    llvm::Instruction::BinaryOps instr;

    switch(op) {
        case TPLUS:     instr = llvm::Instruction::Add; break;
        case TMINUS:    instr = llvm::Instruction::Sub; break;
        case TMUL:      instr = llvm::Instruction::Mul; break;
        case TDIV:      instr = llvm::Instruction::SDiv; break;

        default:
            return nullptr;
    }

    return llvm::BinaryOperator::Create(instr, LHS.codegen(), RHS.codegen(), "", codegen_ctx::CurrentBlock().get());

}

}