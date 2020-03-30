#pragma once

#include <llvm/IR/Value.h>
#include <iostream>
#include <vector>

#include "visitor.hpp"

// this produces cyclic import problem
// #include "code_generator.hpp"
// so forward declare codegen_context
class codegen_context;

// enum to keep track of which node is which
enum class node_type {
    decimal,
    fraction
};

/// every class has to have a default constructor, since parser.y
/// needs to create these objects without arguments first

// namespace barium {

class node {
   public:
    virtual ~node() {}
    virtual llvm::Value* code_gen(codegen_context* ctx) {
        std::cerr << "ERROR code_gen not implemented" << '\n';
        return nullptr;
    }

    virtual std::string to_str() {
        std::cerr << "ERROR to_str not implemented" << '\n';
        return "";
    }

    virtual void accept(visitor& v) {
        v.visit_node(this);
    }
};

class expression : public node {
    public:
    void accept(visitor& v) override { v.visit_expression(this); }
};

class statement : public node {
    public:
    void accept(visitor& v) override { v.visit_statement(this); }
};

class expr_statement : public statement {
   public:
    std::unique_ptr<expression> expr;
    expr_statement(std::unique_ptr<expression> expr) : expr(std::move(expr)) {}
    expr_statement();

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_expr_statement(this); }
};

class decimal : public expression {
   public:
    long long value;
    decimal(long long value) : value(value) {}
    decimal() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_decimal(this); }
};

class fraction : public expression {
   public:
    long double value;
    fraction(long double value) : value(value) {}
    fraction() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_fraction(this); }
};

class stringlit : public expression {
   public:
    std::string value;
    stringlit(std::string value) : value(value) {}
    stringlit();

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_stringlit(this); }
};

class binary_operator : public expression {
   public:
    char op = 0;
    std::unique_ptr<expression> lhs = nullptr;
    std::unique_ptr<expression> rhs = nullptr;
    binary_operator(char op, std::unique_ptr<expression> lhs, std::unique_ptr<expression> rhs) : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
    binary_operator() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_binary_operator(this); }    
};

class unary_operator : public expression {
   public:
    char op = 0;
    std::unique_ptr<expression> expr = nullptr;
    unary_operator(char op, std::unique_ptr<expression> expr) : op(op), expr(std::move(expr)) {}
    unary_operator() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_unary_operator(this); }
};

class identifier : public expression {
   public:
    std::string name;
    identifier(const std::string& name) : name(name) {}
    identifier() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_identifier(this); }
    
};

class block : public expression {
   public:
    std::vector<std::unique_ptr<statement>> statements;
    block() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_block(this); }    
};

class assignment : public expression {
   public:
    std::unique_ptr<identifier> lhs = nullptr;
    std::unique_ptr<expression> rhs = nullptr;
    assignment(std::unique_ptr<identifier> lhs, std::unique_ptr<expression> rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {}
    assignment() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_assignment(this); }
};

class function_call : public expression {
   public:
    std::unique_ptr<identifier> ident;
    std::unique_ptr<std::vector<std::unique_ptr<expression>>> args_list;

    function_call(std::unique_ptr<identifier> ident, std::unique_ptr<std::vector<std::unique_ptr<expression>>> args_list) : ident(std::move(ident)), args_list(std::move(args_list)) {}
    function_call() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_function_call(this); }
};

class variable_declaration : public statement {
   public:
    std::unique_ptr<identifier> type;
    std::unique_ptr<identifier> ident;
    std::unique_ptr<expression> assign_expr;

    variable_declaration(
        std::unique_ptr<identifier> type,
        std::unique_ptr<identifier> ident,
        std::unique_ptr<expression> assign_expr) : type(std::move(type)),
                                                   ident(std::move(ident)),
                                                   assign_expr(std::move(assign_expr)) {}

    variable_declaration(
        std::unique_ptr<identifier> type,
        std::unique_ptr<identifier> ident) : type(std::move(type)),
                                             ident(std::move(ident)) {}

    variable_declaration() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_variable_declaration(this); }
};

class comp_operator : public expression {
    public:
    std::string op;
    std::unique_ptr<expression> lhs;
    std::unique_ptr<expression> rhs;

    comp_operator(std::string op, std::unique_ptr<expression> lhs, std::unique_ptr<expression> rhs) : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_comp_operator(this); }
};

class conditional : public statement {
    public:
    std::unique_ptr<expression> comp_expr;
    std::unique_ptr<expression> then_expr;
    std::unique_ptr<expression> else_expr;

    conditional(std::unique_ptr<expression> comp_expr, 
    std::unique_ptr<expression> then_expr, 
    std::unique_ptr<expression> else_expr = nullptr) : comp_expr(std::move(comp_expr)), 
                                                       then_expr(std::move(then_expr)), 
                                                       else_expr(std::move(else_expr)) {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_conditional(this); }

};

// }
