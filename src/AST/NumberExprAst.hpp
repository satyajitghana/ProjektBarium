#pragma once

#include "ExprAst.hpp"

class NumberExprAst : public ExprAst {
    double val;

   public:
    NumberExprAst(double val) : val(val) {}
    llvm::Value* codeGen() override;
};