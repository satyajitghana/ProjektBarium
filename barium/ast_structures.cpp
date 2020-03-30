#include "ast_structures.hpp"
#include "code_generator.hpp"

#include "parser.hpp"

#include <typeinfo>

llvm::Value* block::code_gen(codegen_context* ctx) {
    llvm::Value* last = nullptr;
    std::cout << "[ found " << this->statements.size() << " statements ]"
              << "\n";
    for (auto& stmt : this->statements) {
        std::cout << "[generating code for: " << typeid(*stmt).name() << " ]"
                  << "\n";
        last = stmt->code_gen(ctx);
    }

    return last;
}

llvm::Value* expr_statement::code_gen(codegen_context* ctx) {
    std::cout << "[ generating code for: " << typeid(*expr).name() << " ]"
              << "\n";
    return this->expr->code_gen(ctx);
}

llvm::Value* decimal::code_gen(codegen_context* ctx) {
    std::cout << "[producing decimal for: " << value << " ]"
              << "\n";
    return llvm::ConstantInt::get(codegen_context::TheContext,
                                  llvm::APInt(64, value));
}

llvm::Value* fraction::code_gen(codegen_context* ctx) {
    std::cout << "[producing fraction for: " << value << " ]"
              << "\n";
    return llvm::ConstantFP::get(codegen_context::TheContext,
                                 llvm::APFloat((double)this->value));
}

llvm::Value* stringlit::code_gen(codegen_context* ctx) {
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

llvm::Value* binary_operator::code_gen(codegen_context* ctx) {
    using namespace llvm;

    llvm::Value* L = this->lhs->code_gen(ctx);
    std::cout << "[producing binary_operator for: " << op << " ]"
              << "\n";
    llvm::Value* R = this->rhs->code_gen(ctx);

    // check if the value TypeIDs are same for left and right
    // if they are different cast them to doubles, since we only have
    // 2 data types, this works
    if (L->getType()->getTypeID() != R->getType()->getTypeID()) {
        auto doubleTy = ctx->Builder.getDoubleTy();

        // cast RHS
        auto cast_instr = CastInst::getCastOpcode(R, true, doubleTy, true);
        // CastOp, Value*, Type*, Twine
        R = ctx->Builder.CreateCast(cast_instr, R, doubleTy, "cast_double");

        // cast LHS
        cast_instr = CastInst::getCastOpcode(L, true, doubleTy, true);
        L = ctx->Builder.CreateCast(cast_instr, L, doubleTy, "cast_double");
    }

    bool is_double = R->getType()->isFloatingPointTy();

    Instruction::BinaryOps op_instr;
    switch (this->op) {
        case '+':
            op_instr = is_double ? Instruction::FAdd : Instruction::Add;
            break;
        case '-':
            op_instr = is_double ? Instruction::FSub : Instruction::Sub;
            break;
        case '*':
            op_instr = is_double ? Instruction::FMul : Instruction::Mul;
            break;
        case '/':
            op_instr = is_double ? Instruction::FDiv : Instruction::SDiv;
            break;
        // these are short circuited logical operators
        case '&':
            op_instr = Instruction::And;
            break;
        case '|':
            op_instr = Instruction::Or;
            break;
        default: {
            std::cerr << "unknown operator !" << '\n';
            return nullptr;
        }
    }

    Value* bin_op = ctx->Builder.CreateBinOp(op_instr, L, R, "math_tmp");

    return bin_op;
}

llvm::Value* unary_operator::code_gen(codegen_context* ctx) {
    using namespace llvm;

    std::cout << "[producing unary operator for: " << this->op << " ]"
              << "\n";

    Value* expr = this->expr->code_gen(ctx);

    // Instruction::UnaryOps op_instr;
    Value* un_op = nullptr;

    switch (this->op) {
        // does bitwise not
        case '!': {
            Value* neg_one = llvm::ConstantInt::get(ctx->TheContext,
                                                    llvm::APInt(64, -1));

            auto instr = Instruction::Xor;
            un_op = ctx->Builder.CreateBinOp(instr, neg_one, expr, "not_temp");
        } break;
        default: {
            std::cerr << "unknown operator !" << '\n';
            return nullptr;
        }
    }

    // Value* un_op = ctx->Builder.CreateUnOp(op_instr, expr, "unary_tmp");

    return un_op;
}

llvm::Value* identifier::code_gen(codegen_context* ctx) {
    using namespace llvm;

    std::cout << "[producing identifier for: " << this->name << " ]"
              << "\n";

    // check if the variable does not exist in the current locals
    if (ctx->current_block()->locals.find(this->name) == ctx->current_block()->locals.end()) {
        std::cerr << "undeclared variable " << this->name << " !" << '\n';

        return nullptr;
    }

    // load the variable
    Value* loaded_var = ctx->Builder.CreateLoad(ctx->current_block()->locals[this->name], this->name.c_str());

    return loaded_var;
}

llvm::Value* assignment::code_gen(codegen_context* ctx) {
    using namespace llvm;

    std::cout << "[producing assignment for: " << lhs->name << " ]"
              << "\n";
    // check if the variable does not exist in the current locals
    if (ctx->current_block()->locals.find(lhs->name) == ctx->current_block()->locals.end()) {
        std::cerr << "undeclared variable " << lhs->name << " !" << '\n';

        return nullptr;
    }

    StoreInst* si = ctx->Builder.CreateStore(this->rhs->code_gen(ctx), ctx->current_block()->locals[this->lhs->name]);

    return si;
}

llvm::Value* function_call::code_gen(codegen_context* ctx) {
    using namespace llvm;

    std::cout << "[producing function call for: " << this->ident->name << " ]"
              << "\n";

    // fetch the function from the module
    Function* function = codegen_context::TheModule->getFunction(this->ident->name.c_str());

    std::vector<Value*> args;

    // put all the parameters into the vector
    for (auto& arg : *(args_list)) {
        args.push_back(arg->code_gen(ctx));
    }

    // create the instruction call
    CallInst* call = CallInst::Create(function, args, "", ctx->blocks.top()->block);

    return call;

    // experiment on printf function call directly from code
    // i then realised about external function, so rather use that
    // its more generic
    // but i'm keeping this here as a reference, might use later ?
    // - shadowleaf
    //
    // if (this->ident->name == "print") {
    //     FunctionType* funcType = FunctionType::get(
    //         IntegerType::getInt32Ty(codegen_context::TheContext),
    //         PointerType::get(Type::getInt8Ty(codegen_context::TheContext), 0),
    //         true);
    //     FunctionCallee CalleeF =
    //         codegen_context::TheModule->getOrInsertFunction("printf", funcType);

    //     return codegen_context::Builder.CreateCall(CalleeF, args, "printfCall");
    // } else {
    //     return nullptr;
    // }
}

llvm::Value* variable_declaration::code_gen(codegen_context* ctx) {
    using namespace llvm;

    std::cout << "[producing variable declaration for: " << this->ident->name << " ]"
              << "\n";
    if (ctx->current_block()->locals[this->ident->name] != nullptr) {
        std::cout << "error ! " << this->ident->name << " already declared" << '\n';

        return nullptr;
    }

    IRBuilder<> TmpB(ctx->current_block()->block, ctx->current_block()->block->begin());

    AllocaInst* alloc = TmpB.CreateAlloca(ctx->type_of(this->type.get()), nullptr, this->ident->name);

    ctx->current_block()->locals[this->ident->name] = alloc;

    // now create an assignment operation for the above allocation
    if (this->assign_expr != nullptr) {
        assignment assign(std::make_unique<identifier>(this->ident->name), std::move(this->assign_expr));
        assign.code_gen(ctx);
    }

    return alloc;
}


llvm::Value* comp_operator::code_gen(codegen_context* ctx) {
    using namespace llvm;

    Value* lhs_val = this->lhs->code_gen(ctx);
    Value* rhs_val = this->rhs->code_gen(ctx);

    if (lhs_val == nullptr or rhs_val == nullptr) {
        std::cerr << "error ! lhs or rhs of comp operator null !";

        return nullptr;
    }

    // TODO: write code to check if the lhs and rhs are types that can be compared
    // also check if they are of differnt types, for now assume they are going to be same
    bool is_double = lhs_val->getType()->isFloatingPointTy();

    Instruction::OtherOps oinstr = is_double ? Instruction::FCmp : Instruction::ICmp;

    CmpInst::Predicate predicate;

    if (this->op == ">=") {
        predicate = is_double ? CmpInst::FCMP_OGE : CmpInst::ICMP_SGE;
    } else if (this->op == ">") {
        predicate = is_double ? CmpInst::FCMP_OGT : CmpInst::ICMP_SGT;
    } else {
        std::cerr << "operator: " << this->op << " not supported!" << '\n';
        return nullptr;
    } 

    return CmpInst::Create(oinstr, predicate, lhs_val, rhs_val, "cmp_tmp", ctx->current_block()->block);
}

llvm::Value* conditional::code_gen(codegen_context* ctx) {
    using namespace llvm;

    Value* comp_val = this->comp_expr->code_gen(ctx);

    return nullptr;
}

