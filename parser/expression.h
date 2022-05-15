#ifndef BABY_SUB_EXPRESSION_H
#define BABY_SUB_EXPRESSION_H

#include <memory>

#include "lex.h"

struct Expression {
protected:
    virtual int GetID() = 0;
};

struct Variable : public Expression {
    Token var;

    explicit Variable(const Token& p_token) : var(p_token) {}
    int GetID() override { return 0; }
};

struct Literal : public Expression {
    Token lit;

    explicit Literal(const Token& p_token) : lit(p_token) {}
    int GetID() override { return 1; }
};

struct Lambda : public Expression {
    std::shared_ptr<Variable> var;
    std::shared_ptr<Expression> body;

    int GetID() override { return 2; }
};

struct Application : public Expression {
    std::shared_ptr<Expression> lambda;
    std::shared_ptr<Expression> value;

    int GetID() override { return 3; }
};

struct Let : public Expression {
    std::shared_ptr<Variable> var;
    std::shared_ptr<Expression> body;
    std::shared_ptr<Expression> rhs;

    int GetID() override { return 4; }
};

#endif//BABY_SUB_EXPRESSION_H
