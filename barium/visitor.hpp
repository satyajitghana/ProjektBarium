#pragma once

// forward declare the AST classes
// to prevent cyclic dependency

class node;
class expression;
class statement;
class expr_statement;
class decimal;
class fraction;
class stringlit;
class binary_operator;
class unary_operator;
class identifier;
class block;
class function_call;
class variable_declaration;
class comp_operator;
class conditional;

class visitor {
    public:
    virtual void visit_node(node* node) = 0;
    virtual void visit_expression(expression* expr) = 0;
    virtual void visit_statement(statement* stmt) = 0;
    virtual void visit_expr_statement(expr_statement* expr) = 0;
    virtual void visit_decimal(decimal* expr) = 0;
    virtual void visit_fraction(fraction* expr) = 0;
    virtual void visit_stringlit(stringlit* expr) = 0;
    virtual void visit_binary_operator(binary_operator* expr) = 0;
    virtual void visit_unary_operator(unary_operator* expr) = 0;
    virtual void visit_identifier(identifier* expr) = 0;
    virtual void visit_block(block* expr) = 0;
    virtual void visit_function_call(function_call* expr) = 0;
    virtual void visit_variable_declaration(variable_declaration* expr) = 0;
    virtual void visit_comp_operator(comp_operator* expr) = 0;
    virtual void visit_conditional(conditional* expr) = 0;
};

