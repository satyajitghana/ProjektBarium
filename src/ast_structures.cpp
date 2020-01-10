#include "ast_structures.hpp"
#include "code_generator.hpp"

#include <typeinfo>

llvm::Value* block::code_gen() {
    llvm::Value* last = nullptr;
    for (auto& stmt : this->statements) {
        std::cout << "[generating code for: " << typeid(*stmt).name() << " ]"
                  << "\n";
        last = stmt->code_gen();
    }

    return last;
}

llvm::Value* expr_statement::code_gen() {
    std::cout << "[generating code for: " << typeid(*expr).name() << " ]"
              << "\n";
    return this->expr->code_gen();
}

llvm::Value* decimal::code_gen() {
    std::cout << "[producing decimal for: " << value << " ]"
              << "\n";
    return llvm::ConstantInt::get(codegen_context::TheContext,
                                  llvm::APInt(64, value));
}

llvm::Value* fraction::code_gen() {
    std::cout << "[producing fraction for: " << value << " ]"
              << "\n";
    return llvm::ConstantFP::get(codegen_context::TheContext,
                                 llvm::APFloat((double)this->value));
}

llvm::Value* stringlit::code_gen() {
    std::cout << "[producing string literal for: " << value << " ]"
              << "\n";
    // return
    // codegen_context::Builder.CreateGlobalString(llvm::StringRef(this->value));

    using namespace llvm;

    // generate the type for the globale var
    ArrayType* ArrayTy_0 = ArrayType::get(
        IntegerType::get(codegen_context::TheContext, 8), value.size() + 1);
    // create global var which holds the constant string.
    GlobalVariable* gvar_array__str = new GlobalVariable(
        *codegen_context::TheModule.get(),
        /*Type=*/ArrayTy_0,
        /*isConstant=*/true, GlobalValue::PrivateLinkage,
        /*Initializer=*/0,  // has initializer, specified below
        ".str");
    gvar_array__str->setAlignment(1);
    // create the contents for the string global.
    Constant* const_array_str =
        ConstantDataArray::getString(codegen_context::TheContext, value);
    // Initialize the global with the string
    gvar_array__str->setInitializer(const_array_str);

    // generate access pointer to the string
    std::vector<Constant*> const_ptr_8_indices;
    ConstantInt* const_int = ConstantInt::get(codegen_context::TheContext,
                                              APInt(64, StringRef("0"), 10));
    const_ptr_8_indices.push_back(const_int);
    const_ptr_8_indices.push_back(const_int);
    Constant* const_ptr_8 = ConstantExpr::getGetElementPtr(
        ArrayTy_0, gvar_array__str, const_ptr_8_indices);

    return const_ptr_8;
}

llvm::Value* binary_operator::code_gen() {
    llvm::Value* L = this->lhs->code_gen();
    std::cout << "[producing binary_operator for: " << op << " ]"
              << "\n";
    llvm::Value* R = this->rhs->code_gen();

    switch (this->op) {
        case '+':
            return codegen_context::Builder.CreateAdd(L, R, "addtmp");
        case '-':
            return codegen_context::Builder.CreateFSub(L, R, "subtmp");
        case '*':
            return codegen_context::Builder.CreateFMul(L, R, "multmp");
    }

    return llvm::ConstantInt::get(codegen_context::TheContext,
                                  llvm::APInt(64, 0));
}

llvm::Value* identifier::code_gen() {
    std::cout << "[producing identifier for: " << name << " ]"
              << "\n";
    // if (codegen_context::NamedValues.find(this->name) ==
    // codegen_context::NamedValues.end()) {
    //     std::cerr << "undeclared variable: " << this->name << "\n";
    //     return nullptr;
    // }

    return llvm::ConstantInt::get(codegen_context::TheContext,
                                  llvm::APInt(64, 0));
}

llvm::Value* assignment::code_gen() {
    std::cout << "[producing assignment for: " << lhs->name << " ]"
              << "\n";
    return this->rhs->code_gen();
}

llvm::Value* function_call::code_gen() {
    std::cout << "[producing function call for: " << this->ident->name << " ]"
              << "\n";
    std::vector<llvm::Value*> args;
    for (auto & arg : *(args_list) ) {
        args.push_back(arg->code_gen());
    }

    using namespace llvm;

    if (this->ident->name == "print") {
        FunctionType* funcType = FunctionType::get(
            IntegerType::getInt32Ty(codegen_context::TheContext),
            PointerType::get(Type::getInt8Ty(codegen_context::TheContext), 0),
            true);
        FunctionCallee CalleeF =
            codegen_context::TheModule->getOrInsertFunction("printf", funcType);

        return codegen_context::Builder.CreateCall(CalleeF, args, "printfCall");
    } else {
        return nullptr;
    }
}
