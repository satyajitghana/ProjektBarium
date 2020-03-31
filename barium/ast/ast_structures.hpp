#pragma once

#include <llvm/IR/Value.h>
#include <iostream>
#include <vector>

#include "../visitor/visitor.hpp"
#include "location.hh"

// this produces cyclic import problem
// #include "codegen/code_generator.hpp"
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
   yy::location loc;
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
    yy::location loc;

    decimal(long long value, yy::location loc) : value(value), loc(loc) {}
    decimal() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_decimal(this); }
};

class fraction : public expression {
   public:
    long double value;
    yy::location loc;

    fraction(long double value, yy::location loc) : value(value), loc(loc) {}
    fraction() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_fraction(this); }
};

class stringlit : public expression {
   public:
    std::string value;
    yy::location loc;

    stringlit(std::string value, yy::location loc) : value(value), loc(loc) {}
    stringlit();

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_stringlit(this); }
};

class binary_operator : public expression {
   public:
    char op = 0;
    std::unique_ptr<expression> lhs = nullptr;
    std::unique_ptr<expression> rhs = nullptr;
    yy::location loc;

    binary_operator(char op, std::unique_ptr<expression> lhs, std::unique_ptr<expression> rhs, yy::location loc) : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)), loc(loc) {}
    binary_operator() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_binary_operator(this); }    
};

class unary_operator : public expression {
   public:
    char op = 0;
    std::unique_ptr<expression> expr = nullptr;
    yy::location loc;
    
    unary_operator(char op, std::unique_ptr<expression> expr, yy::location loc) : op(op), expr(std::move(expr)), loc(loc) {}
    unary_operator() {}

    llvm::Value* code_gen(codegen_context* ctx);

    void accept(visitor& v) override { v.visit_unary_operator(this); }
};

class identifier : public expression {
   public:
    std::string name;
    yy::location loc;

    identifier(const std::string& name, yy::location loc) : name(name), loc(loc) {}
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

class for_loop : public statement {
    public:
    std::unique_ptr<expression> init_expr;
    std::unique_ptr<expression> cond_expr;
    std::unique_ptr<expression> update_expr;
    std::unique_ptr<expression> then_expr;

    for_loop(std::unique_ptr<expression> init_expr,
    std::unique_ptr<expression> cond_expr,
    std::unique_ptr<expression> update_expr,
    std::unique_ptr<expression> then_expr) : init_expr(std::move(init_expr)),
                                             cond_expr(std::move(cond_expr)),
                                             update_expr(std::move(update_expr)),
                                             then_expr(std::move(then_expr)) {}
    
    void accept(visitor& v) override { v.visit_for_loop(this); }
};

class for_range : public statement {
    public:
    std::unique_ptr<identifier> ident;
    std::unique_ptr<decimal> range_lim;
    std::unique_ptr<expression> then_expr;

    for_range(std::unique_ptr<identifier> ident, std::unique_ptr<decimal> range_lim, std::unique_ptr<expression> then_expr) : ident(std::move(ident)), range_lim(std::move(range_lim)), then_expr(std::move(then_expr)) {}

    void accept(visitor& v) override { v.visit_for_range(this); }
};

class array_access : public expression {
    public:
    std::unique_ptr<identifier> var_name;
    std::unique_ptr<expression> index;
    // arr[0][1] -> here arr[0] is the next_dimension
    std::unique_ptr<expression> next_dimension;

    // single index access
    array_access(std::unique_ptr<identifier> var_name, std::unique_ptr<expression> index) : var_name(std::move(var_name)), index(std::move(index)) {}
    
    // multi dimension access
    array_access(std::unique_ptr<expression> next_dimension, std::unique_ptr<expression> index) : next_dimension(std::move(next_dimension)), index(std::move(index)) {}

    void accept(visitor& v) override { v.visit_array_access(this); }
};

// }
