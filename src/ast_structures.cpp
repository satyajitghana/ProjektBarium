#include "ast_structures.hpp"
#include "code_generator.hpp"

#include <typeinfo>

llvm::Value* block::code_gen() {

    llvm::Value* last = nullptr;
    for (auto& stmt: this->statements) {
        std::cout << "[generating code for: " << typeid(*stmt).name() << " ]" << "\n";
        last = stmt->code_gen();
    }

    return last;
}

llvm::Value* expr_statement::code_gen() {
    std::cout << "[generating code for: " << typeid(*expr).name() << " ]" << "\n";
    return this->expr->code_gen();
}

llvm::Value* decimal::code_gen() {
    std::cout << "[producing decimal for: " << value << " ]" << "\n";
    return llvm::ConstantInt::get(codegen_context::TheContext, llvm::APInt(64, value));
}

llvm::Value* fraction::code_gen() {
    std::cout << "[producing fraction for: " << value << " ]" << "\n";
    return llvm::ConstantFP::get(codegen_context::TheContext, llvm::APFloat((double)this->value));
}

llvm::Value* binary_operator::code_gen() {
    llvm::Value* L = this->lhs->code_gen();
    std::cout << "[producing binary_operator for: " << op << " ]" << "\n";
    llvm::Value* R = this->rhs->code_gen();

    switch (this->op) {
        case '+': return codegen_context::Builder.CreateAdd(L, R, "addtmp");
        case '-': return codegen_context::Builder.CreateFSub(L, R, "subtmp");
        case '*': return codegen_context::Builder.CreateFMul(L, R, "multmp");
    }

    return nullptr;
}

llvm::Value* identifier::code_gen() {
    std::cout << "[producing identifier for: " << name << " ]" << "\n";
    if (codegen_context::NamedValues.find(this->name) == codegen_context::NamedValues.end()) {
        std::cerr << "undeclared variable: " << this->name << "\n";
        return nullptr;
    }

    return nullptr;
}

llvm::Value* assignment::code_gen() {
    std::cout << "[producing assignment for: " << lhs->name << " ]" << "\n";
    return this->rhs->code_gen();
}
