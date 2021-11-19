#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

struct expression_visitor;
struct expression {
    virtual int evaluate() const = 0;
    virtual void accept(expression_visitor &) = 0;
    virtual ~expression() = default;
};

struct sum;

struct expression_visitor {
    virtual void visit(sum &) = 0;
    // TODO: add similar visit() for the other derived class
};

struct sum : expression {
    std::unique_ptr<expression> lhs, rhs;

    int evaluate() const override {
        return lhs->evaluate() + rhs->evaluate();
    }

    // TODO: implement accept()
};

auto make_sum(std::unique_ptr<expression> lhs,
              std::unique_ptr<expression> rhs) {
    auto result = std::make_unique<sum>();
    result->lhs = std::move(lhs);
    result->rhs = std::move(rhs);
    return result;
}

struct literal : expression {
    int value;

    int evaluate() const override {
        return value;
    }

    // TODO: implement accept()
};

auto make_literal(int value) {
    auto result = std::make_unique<literal>();
    result->value = value;
    return result;
}

// TODO: add structs to_string_visitor and to_string_spaced_visitor

int main() {
    std::unique_ptr<expression> expr =
        make_sum(make_literal(10), make_sum(make_literal(2), make_literal(3)));
    assert(expr->evaluate() == 10 + (2 + 3));

    {
        to_string_visitor v;
        expr->accept(v);
        assert(v.result == "(10+(2+3))");
    }
    {
        to_string_spaced_visitor v;
        expr->accept(v);
        assert(v.result == "(10 + (2 + 3))");
    }
    std::cout << "OK\n";
}
