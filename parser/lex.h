#ifndef BABY_SUB_LEX_H
#define BABY_SUB_LEX_H

#include <string>
#include <vector>
#include <unordered_map>

struct Token {
    enum class Type {
        LEFT_PARENTHESES, RIGHT_PARENTHESES, LAMBDA, LET, IN, BOOL, NUM, EQUAL, VAR
    } type;

    std::string name;

    explicit Token(Type p_type, const std::string& p_name = "") : type(p_type), name(p_name) {}
    Token(const Token& p_other) = default;
    Token& operator= (const Token& p_other) = default;
    ~Token() = default;
};

class Lex {
public:
    Lex();
    ~Lex() = default;
    Lex(const Lex&) = delete;
    Lex& operator= (const Lex&) = delete;
    Lex(Lex&&) = delete;
    Lex& operator= (Lex&&) = delete;

    std::vector<Token> Parse(const std::string& p_exp);
private:
    std::unordered_map<std::string, Token> m_keywords;

    void GetToken(std::vector<Token>& p_tokens, const std::string& p_exp);
};

#endif//BABY_SUB_LEX_H
