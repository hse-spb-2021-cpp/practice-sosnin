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
struct literal;

struct expression_visitor {
    virtual void visit(sum &) = 0;
    virtual void visit(literal &) = 0;
};

struct sum : expression {
    std::unique_ptr<expression> lhs, rhs;

    int evaluate() const override {
        return lhs->evaluate() + rhs->evaluate();
    }

    void accept(expression_visitor &v) {
        v.visit(*this);
    }
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

    void accept(expression_visitor &v) {
        v.visit(*this);
    }
};

auto make_literal(int value) {
    auto result = std::make_unique<literal>();
    result->value = value;
    return result;
}

struct to_string_visitor : expression_visitor {
    std::string result;

    void visit(sum &s) {
        result += "(";
        s.lhs->accept(*this);
        result += "+";
        s.rhs->accept(*this);
        result += ")";
    }

    void visit(literal &l) {
        result += std::to_string(l.value);
    }
};

struct to_string_spaced_visitor : expression_visitor {
    std::string result;

    void visit(sum &s) {
        result += "(";
        s.lhs->accept(*this);
        result += " + ";
        s.rhs->accept(*this);
        result += ")";
    }

    void visit(literal &l) {
        result += std::to_string(l.value);
    }
};

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
