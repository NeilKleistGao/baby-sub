#include "parser.h"

std::shared_ptr<Expression> Parser::Parse() {
    std::shared_ptr<Expression> res = nullptr;
    switch (m_tokens[m_pointer].type) {
        case Token::Type::LEFT_PARENTHESES:
            res = ParseApplicationOrGroup();
            break;
        case Token::Type::LAMBDA:
            res = ParseLambda();
            break;
        case Token::Type::LET:
            res = ParseLet();
            break;
        case Token::Type::BOOL:
        case Token::Type::NUM:
            res = ParseLiteral();
            break;
        case Token::Type::VAR:
            res = ParseVariable();
            break;
        default:
            break;
    }

    return res;
}

std::shared_ptr<Expression> Parser::ParseApplicationOrGroup() {
    ++m_pointer;
    auto exp = Parse();

    if (m_tokens[m_pointer].type != Token::Type::RIGHT_PARENTHESES) {
        return ParseApplication(exp);
    }

    if (m_tokens[m_pointer++].type != Token::Type::RIGHT_PARENTHESES) {
        return nullptr;
    }
    return exp;
}

std::shared_ptr<Lambda> Parser::ParseLambda() {
    if (m_tokens[++m_pointer].type != Token::Type::VAR) {
        return nullptr;
    }

    auto lamb = std::make_shared<Lambda>();
    lamb->var = ParseVariable();

    if (m_tokens[m_pointer++].type != Token::Type::EQUAL) {
        return nullptr;
    }

    lamb->body = Parse();
    return lamb;
}

std::shared_ptr<Let> Parser::ParseLet() {
    if (m_tokens[++m_pointer].type != Token::Type::VAR) {
        return nullptr;
    }

    auto let_exp = std::make_shared<Let>();
    let_exp->var = ParseVariable();

    if (m_tokens[m_pointer++].type != Token::Type::EQUAL) {
        return nullptr;
    }

    let_exp->body = Parse();
    if (m_tokens[m_pointer++].type != Token::Type::IN) {
        return nullptr;
    }

    let_exp->rhs = Parse();

    return let_exp;
}

std::shared_ptr<Literal> Parser::ParseLiteral() {
    return std::make_shared<Literal>(m_tokens[m_pointer++]);
}

std::shared_ptr<Variable> Parser::ParseVariable() {
    return std::make_shared<Variable>(m_tokens[m_pointer++]);
}

std::shared_ptr<Application> Parser::ParseApplication(const std::shared_ptr<Expression>& p_func) {
    auto app = std::make_shared<Application>();
    app->lambda = p_func;
    app->value = Parse();

    if (m_tokens[m_pointer++].type != Token::Type::RIGHT_PARENTHESES) {
        return nullptr;
    }
    return app;
}