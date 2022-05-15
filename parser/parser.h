#ifndef BABY_SUB_PARSER_H
#define BABY_SUB_PARSER_H

#include <vector>
#include "expression.h"

class Parser {
public:
    explicit Parser(std::vector<Token>&& p_tokens) : m_tokens(p_tokens), m_pointer(0) {}
    std::shared_ptr<Expression> Parse();
private:
    const std::vector<Token>& m_tokens;
    int m_pointer;

    std::shared_ptr<Expression> ParseApplicationOrGroup();
    std::shared_ptr<Lambda> ParseLambda();
    std::shared_ptr<Let> ParseLet();
    std::shared_ptr<Literal> ParseLiteral();
    std::shared_ptr<Variable> ParseVariable();
    std::shared_ptr<Application> ParseApplication(const std::shared_ptr<Expression>& p_func);
};

#endif//BABY_SUB_PARSER_H
