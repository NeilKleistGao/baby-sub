#include "lex.h"

#include <cctype>

Lex::Lex() {
    m_keywords.insert(std::make_pair("let", Token{Token::Type::LET}));
    m_keywords.insert(std::make_pair("in", Token{Token::Type::IN}));
    m_keywords.insert(std::make_pair("true", Token{Token::Type::BOOL}));
    m_keywords.insert(std::make_pair("false", Token{Token::Type::BOOL}));
}

std::vector<Token> Lex::Parse(const std::string &p_exp) {
    std::vector<Token> tokens;
    int length = p_exp.length();
    std::string exp;
    for (int i = 0, j = 0; i < length && j < length; ++j) {
        if (std::isspace(p_exp[j])) {
            GetToken(tokens, exp);
            i = j + 1; exp.clear();
        }
        else if (p_exp[j] == '(') {
            GetToken(tokens, exp);
            i = j + 1; exp.clear();
            tokens.emplace_back(Token::Type::LEFT_PARENTHESES);
        }
        else if (p_exp[j] == ')') {
            GetToken(tokens, exp);
            i = j + 1; exp.clear();
            tokens.emplace_back(Token::Type::RIGHT_PARENTHESES);
        }
        else if (p_exp[j] == '=') {
            GetToken(tokens, exp);
            i = j + 1; exp.clear();
            tokens.emplace_back(Token::Type::EQUAL);
        }
        else if (p_exp[j] == '\\') {
            GetToken(tokens, exp);
            i = j + 1; exp.clear();
            tokens.emplace_back(Token::Type::LAMBDA);
        }
        else {
            exp += p_exp[j];
        }
    }

    return tokens;
}

void Lex::GetToken(std::vector<Token>& p_tokens, const std::string& p_exp) {
    if (p_exp.empty()) {
        return;
    }

    auto it = m_keywords.find(p_exp);
    if (it != m_keywords.end()) {
        p_tokens.push_back(it->second);
        return;
    }

    bool is_num = true;
    for (const auto c : p_exp) {
        if (!std::isdigit(c)) {
            is_num = false;
            break;
        }
    }

    if (is_num) {
        p_tokens.emplace_back(Token::Type::NUM);
    }
    else {
        p_tokens.emplace_back(Token::Type::VAR, p_exp);
    }
}
