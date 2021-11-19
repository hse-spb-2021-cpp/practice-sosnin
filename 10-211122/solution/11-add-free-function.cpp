#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

struct expression {
    virtual int evaluate() const = 0;
    virtual ~expression() = default;
};

struct sum : expression {
    std::unique_ptr<expression> lhs, rhs;

    int evaluate() const override {
        return lhs->evaluate() + rhs->evaluate();
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
};

auto make_literal(int value) {
    auto result = std::make_unique<literal>();
    result->value = value;
    return result;
}

std::string to_string(expression &e) {
    if (auto *s = dynamic_cast<sum *>(&e)) {
        return "(" + to_string(*s->lhs) + "+" + to_string(*s->rhs) + ")";
    } else if (auto *l = dynamic_cast<literal *>(&e)) {
        return std::to_string(l->value);
    } else {
        std::terminate();
    }
}

std::string to_string_spaced(expression &e) {
    if (auto *s = dynamic_cast<sum *>(&e)) {
        return "(" + to_string_spaced(*s->lhs) + " + " +
               to_string_spaced(*s->rhs) + ")";
    } else if (auto *l = dynamic_cast<literal *>(&e)) {
        return std::to_string(l->value);
    } else {
        std::terminate();
    }
}

int main() {
    std::unique_ptr<expression> expr =
        make_sum(make_literal(10), make_sum(make_literal(2), make_literal(3)));
    assert(expr->evaluate() == 10 + (2 + 3));
    assert(to_string(*expr) == "(10+(2+3))");
    assert(to_string_spaced(*expr) == "(10 + (2 + 3))");
    std::cout << "OK\n";
}
