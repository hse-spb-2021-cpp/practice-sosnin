#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

const std::string kLHB{"("};
const std::string kRHB{")"};
const std::string kPlus{"+"};
const std::string kPlusSpaced{" + "};

struct expression
{
    virtual int evaluate() const = 0;
    virtual std::string to_string() const = 0;
    virtual std::string to_string_spaced() const = 0;
    virtual ~expression() = default;
};

struct sum : expression
{
    std::unique_ptr<expression> lhs, rhs;

    int evaluate() const override
    {
        return lhs->evaluate() + rhs->evaluate();
    }

    std::string to_string() const override
    {
        return kLHB + lhs->to_string() + kPlus + rhs->to_string() + kRHB;
    };

    std::string to_string_spaced() const override
    {
        return kLHB + lhs->to_string_spaced() + kPlusSpaced + rhs->to_string_spaced() + kRHB;
    };
};

auto make_sum(std::unique_ptr<expression> lhs,
              std::unique_ptr<expression> rhs)
{
    auto result = std::make_unique<sum>();
    result->lhs = std::move(lhs);
    result->rhs = std::move(rhs);
    return result;
}

struct literal : expression
{
    int value;

    int evaluate() const override
    {
        return value;
    }

    
    std::string to_string() const override
    {
        return std::to_string(value);
    };

    std::string to_string_spaced() const override
    {
        return to_string();
    };
};

auto make_literal(int value)
{
    auto result = std::make_unique<literal>();
    result->value = value;
    return result;
}

int main()
{
    std::unique_ptr<expression> expr =
        make_sum(make_literal(10), make_sum(make_literal(2), make_literal(3)));
    assert(expr->evaluate() == 10 + (2 + 3));
    assert(expr->to_string() == "(10+(2+3))");
    assert(expr->to_string_spaced() == "(10 + (2 + 3))");
    std::cout << "OK\n";
}
