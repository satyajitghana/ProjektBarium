#include "visitor_pprint.hpp"

#include "../external/loguru.hpp"
#include "../ast/ast_structures.hpp"

std::string visitor_pprint::get_loc(node* node) {
    std::stringstream ss;

    ss << "loc: " << node->loc.begin.line << "." << node->loc.begin.column;

    return ss.str();
}

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
    LOG_S(INFO) << "created expr_statement [ addr: " << expr << " ]";
    LOG_SCOPE_FUNCTION(INFO);
    LOG_S(INFO) << "contains expression [ addr: " << expr->expr.get() << " ]";
}

void visitor_pprint::visit_decimal(decimal* expr) {
    // LOG_S(INFO) << "created decimal [ " << get_loc(expr) << ", addr: " << expr << ", value: " << expr->value << " ]";
    LOG_S(INFO) << "created decimal [ addr: " << expr << ", value: " << expr->value << " ]";
}

void visitor_pprint::visit_fraction(fraction* expr) {
    LOG_S(INFO) << "created fraction [ addr: " << expr << ", value: " << expr->value << " ]";
}

void visitor_pprint::visit_stringlit(stringlit* expr) {
    LOG_S(INFO) << "created stringlit [ addr: " << expr << ", value: \"" << expr->value << "\" ]";
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
    LOG_S(INFO) << "created block [ addr: " << expr << " ]";

    LOG_SCOPE_FUNCTION(INFO);
    for (auto& stmt: expr->statements) {
        LOG_S(INFO) << "contains statement [ addr: " << stmt.get() << " ]";
    }

}

void visitor_pprint::visit_assignment(assignment* expr) {
    LOG_S(INFO) << "created assignment [ addr: " << expr << ", lhs addr: " << expr->lhs.get() << ", rhs addr: " << expr->rhs.get() << " ]";
}

void visitor_pprint::visit_function_call(function_call* expr) {
    LOG_S(INFO) << "created function_call [ addr: " << expr << ", ident: " << expr->ident->name << " ]";
    LOG_SCOPE_FUNCTION(INFO);

    LOG_IF_S(INFO, expr->args_list->size() == 0) << "empty args";

    for (auto& arg: *(expr->args_list)) {
        LOG_S(INFO) << "contains arg [ addr: " << arg.get() << " ]";
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

    LOG_SCOPE_FUNCTION(INFO);
    LOG_IF_S(INFO, expr->else_expr.get() != nullptr) << "contains else_expr [ addr: " << expr->else_expr.get() << " ]";
}

void visitor_pprint::visit_for_loop(for_loop* stmt) {
    LOG_S(INFO) << "created for_loop [ addr: " << stmt << ", init_expr addr: " << stmt->init_expr.get() << ", cond_expr addr: " << stmt->cond_expr.get() << ", update_expr addr: " << stmt->update_expr.get() << ", then_expr addr: " << stmt->then_expr.get() << " ]";
}

void visitor_pprint::visit_for_range(for_range* stmt) {
    LOG_S(INFO) << "created for_range [ addr: " << stmt << ", ident: " << stmt->ident->name << ", range_lim: " << stmt->range_lim->value << ", then_expr addr: " << stmt->then_expr.get() << " ]";
}

void visitor_pprint:: visit_array_access(array_access* expr) {
    LOG_IF_S(INFO, expr->var_name != nullptr) << "created array_access [ addr: " << expr << ", var_name: " << expr->var_name->name << ", index expr addr: " << expr->index.get() << " ]";
    LOG_IF_S(INFO, expr->next_dimension != nullptr) << "created multidim array_access [ addr: " << expr << ", next_dim addr: " << expr->next_dimension.get() << ", index: " << expr->index.get() << " ]";
}
