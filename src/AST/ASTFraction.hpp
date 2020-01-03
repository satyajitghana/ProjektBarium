#include "ASTExpr.hpp"

namespace barium {
class ASTFraction : public ASTExpr {
   public:
    long double value;

    ASTFraction(long double value) : value(value) {}

    virtual llvm::Value* codeGen(CodeGenContext& context) override;
}

llvm::Value*
ASTFraction::codeGen(CodeGenContext& context) {
    std::cout << "producing fraction: " << value << "\n";

    return llvm::ConstantFP::get(Type::getFP128Ty(TheContext), value);
}

}  // namespace barium
