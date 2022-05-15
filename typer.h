#ifndef BABY_SUB_TYPER_H
#define BABY_SUB_TYPER_H

#include <unordered_map>

#include "baby_type.h"
#include "parser/expression.h"

class Typer {
public:
    Typer();
    ~Typer() = default;
    Typer(const Typer&) = delete;
    Typer& operator=(const Typer&) = delete;
    Typer(Typer&&) = delete;
    Typer& operator=(Typer&&) = delete;

    std::shared_ptr<BabyType> Infer(const std::shared_ptr<Expression>& p_exp);
private:
    using Context = std::unordered_map<std::string, std::shared_ptr<BabyType>>;
    Context m_context;

    std::shared_ptr<PrimitiveType> m_bool_type;
    std::shared_ptr<PrimitiveType> m_int_type;
};

#endif//BABY_SUB_TYPER_H
