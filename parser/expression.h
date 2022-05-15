#ifndef BABY_SUB_EXPRESSION_H
#define BABY_SUB_EXPRESSION_H

#include <memory>

#include "lex.h"

struct Expression {
};

struct Variable : public Expression {
    Token var;

    explicit Variable(const Token& p_token) : var(p_token) {}
};

struct Literal : public Expression {
    Token lit;

    explicit Literal(const Token& p_token) : lit(p_token) {}
};

struct Lambda : public Expression {
    std::shared_ptr<Variable> var;
    std::shared_ptr<Expression> body;
};

struct Application : public Expression {
    std::shared_ptr<Expression> lambda;
    std::shared_ptr<Expression> value;
};

struct Let : public Expression {
    std::shared_ptr<Variable> var;
    std::shared_ptr<Expression> body;
    std::shared_ptr<Expression> rhs;
};

#endif//BABY_SUB_EXPRESSION_H
