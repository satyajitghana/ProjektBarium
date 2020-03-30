#include "visitor_pprint.hpp"

#include "external/loguru.hpp"
#include "ast_structures.hpp"

void visitor_pprint::visit_node(node* node) {
    LOG_S(INFO) << "created node [ addr: " << node << " ]";
}

void visitor_pprint::visit_expression(expression* expr) {
    LOG_S(INFO) << "created expression [ addr: " << expr << " ]";
}

void visitor_pprint::visit_statement(statement* stmt) {
    LOG_S(INFO) << "created statement [ addr: " << stmt << " ]";
}

void visitor_pprint::visit_expr_statement(expr_statement* expr) {
    LOG_SCOPE_FUNCTION(INFO);
    LOG_S(INFO) << "created expr_statement [ addr: " << expr << " ]";
    LOG_SCOPE_F(1, "contains expression [ addr: %x ]", expr->expr.get());
}

void visitor_pprint::visit_decimal(decimal* expr) {
    LOG_S(INFO) << "created decimal [ addr: " << expr << ", value: " << expr->value << " ]";
}

void visitor_pprint::visit_fraction(fraction* expr) {
    LOG_S(INFO) << "created fraction [ addr: " << expr << ", value: " << expr->value << " ]";
}

void visitor_pprint::visit_stringlit(stringlit* expr) {
    LOG_S(INFO) << "created stringlit [ addr: " << expr << ", value: " << expr->value << " ]";
}

void visitor_pprint::visit_binary_operator(binary_operator* expr) {
    LOG_S(INFO) << "created binary operator [ addr: " << expr << ", op: " << expr->op << ", lhs addr: " << expr->lhs.get() << ", rhs addr: " << expr->rhs.get() << " ]";
}

void visitor_pprint::visit_unary_operator(unary_operator* expr) {
    LOG_S(INFO) << "created unary operator [ addr: " << expr << ", op: " << expr->op << ", operand: " << expr->expr.get() << " ]";
}

void visitor_pprint::visit_identifier(identifier* expr) {
    LOG_S(INFO) << "created identifier [ addr: " << expr << ", name: " << expr->name << " ]";
}

void visitor_pprint::visit_block(block* expr) {
    LOG_SCOPE_FUNCTION(INFO);
    LOG_S(INFO) << "created block [ addr: " << expr << " ]";

    for (auto& stmt: expr->statements) {
        LOG_SCOPE_F(1, "contains statement [ addr: %x ]", stmt.get());
    }

}

void visitor_pprint::visit_function_call(function_call* expr) {
    LOG_S(INFO) << "created function_call [ addr: " << expr << ", ident: " << expr->ident.get() << " ]";
    LOG_SCOPE_FUNCTION(INFO);

    LOG_IF_S(INFO, expr->args_list->size() == 0) << "empty args";

    for (auto& arg: *expr->args_list) {
        LOG_SCOPE_F(1, "contains arg [ addr: %x ]", arg.get());
    }
}

void visitor_pprint::visit_variable_declaration(variable_declaration* expr) {
    LOG_S(INFO) << "created variable_declaration [ addr: " << expr << ", type: " << expr->type->name << ", ident: " << expr->ident->name << ", assign_expr: " << expr->assign_expr.get() << " ]";
}

void visitor_pprint::visit_comp_operator(comp_operator* expr) {
    LOG_S(INFO) << "created comp_operator [ addr: " << expr << ", op: " << expr->op << ", lhs addr: " << expr->lhs.get() << ", rhs addr: " << expr->rhs.get() << " ]";
}

void visitor_pprint::visit_conditional(conditional* expr) {
    LOG_S(INFO) << "created conditional [ addr: " << expr << ", comp_expr: " << expr->comp_expr.get() << ", then_expr: " << expr->then_expr.get() << " ]";

    LOG_IF_S(INFO, expr->else_expr.get() != nullptr) << "contains else_expr [ addr: " << expr->else_expr.get() << " ]";
}