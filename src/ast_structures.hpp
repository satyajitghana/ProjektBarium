#pragma once

#include <iostream>
#include <vector>
#include <llvm/IR/Value.h>

// namespace barium {
    class node {
        public:
            virtual ~node() {}
            virtual llvm::Value* code_gen() { return nullptr; }
    };

    class expression : public node {

    };

    class statement : public node {

    };

    class expr_statement : public statement {
        public:
        std::unique_ptr<expression> expr;
        expr_statement(std::unique_ptr<expression> expr) : expr(std::move(expr)) { }
        expr_statement();

        llvm::Value* code_gen();
    };

    class decimal : public expression {
        public:
        long long value;
        decimal(long long value) : value(value) { }
        decimal() {}

        llvm::Value* code_gen();
    };

    class fraction : public expression {
        public:
        long double value;
        fraction(long double value) : value(value) { }
        fraction() {}

        llvm::Value* code_gen();
    };

    class binary_operator : public expression {
        public:
        char op = 0;
        std::unique_ptr<expression> lhs = nullptr;
        std::unique_ptr<expression> rhs = nullptr;
        binary_operator(char op, std::unique_ptr<expression> lhs, std::unique_ptr<expression> rhs) : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) { }
        binary_operator() {}

        llvm::Value* code_gen();
    };

    class identifier : public expression {
        public:
        std::string name;
        identifier(const std::string& name) : name(name) { }
        identifier() {}

        llvm::Value* code_gen();
    };

    class block : public expression {
        public:
        std::vector<std::unique_ptr<statement>> statements;
        block() {}

        llvm::Value* code_gen();
    };

    class assignment : public expression {
        public:
        std::unique_ptr<identifier> lhs = nullptr;
        std::unique_ptr<expression> rhs = nullptr;
        assignment(std::unique_ptr<identifier> lhs, std::unique_ptr<expression> rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {}
        assignment() {}

        llvm::Value* code_gen();
    };
// }
