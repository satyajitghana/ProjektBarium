#pragma once

#include "visitor.hpp"

class visitor_pprint : public visitor {
    public:
    void visit_node(node* node);
    void visit_expression(expression* expr);
    void visit_statement(statement* stmt);
    void visit_expr_statement(expr_statement* expr);
    void visit_decimal(decimal* expr);
    void visit_fraction(fraction* expr);
    void visit_stringlit(stringlit* expr);
    void visit_binary_operator(binary_operator* expr);
    void visit_unary_operator(unary_operator* expr);
    void visit_identifier(identifier* expr);
    void visit_block(block* expr);
    void visit_assignment(assignment* expr);
    void visit_function_call(function_call* expr);
    void visit_variable_declaration(variable_declaration* expr);
    void visit_comp_operator(comp_operator* expr);
    void visit_conditional(conditional* expr);
};
