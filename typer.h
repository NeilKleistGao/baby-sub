#ifndef BABY_SUB_TYPER_H
#define BABY_SUB_TYPER_H

#include <unordered_map>
#include <set>

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

    std::shared_ptr<BabyType> Infer(const std::shared_ptr<Expression>& p_exp, int p_level = 0);
private:
    using Context = std::unordered_map<std::string, std::shared_ptr<BabyType>>;
    Context m_context;

    std::shared_ptr<PrimitiveType> m_bool_type;
    std::shared_ptr<PrimitiveType> m_int_type;
    std::unordered_map<std::shared_ptr<BabyType>, std::shared_ptr<BabyType>> m_visit;

    static void Constrain(const std::shared_ptr<BabyType>& p_lhs, const std::shared_ptr<BabyType>& p_rhs);
    static std::shared_ptr<BabyType> Extrude(const std::shared_ptr<BabyType>& p_type, int p_level, bool p_polarity);

    std::shared_ptr<BabyType> Instantiate(const std::shared_ptr<BabyType>& p_poly, int p_level);
};

#endif//BABY_SUB_TYPER_H
