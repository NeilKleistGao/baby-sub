#include "typer.h"

Typer::Typer() {
    m_bool_type = std::make_shared<PrimitiveType>();
    m_int_type = std::make_shared<PrimitiveType>();

    m_bool_type->name = "bool";
    m_int_type->name = "int";

    m_context["true"] = m_bool_type;
    m_context["false"] = m_bool_type;

    auto add = std::make_shared<FunctionType>();
    add->lhs = m_int_type;
    add->rhs = std::make_shared<FunctionType>();
    dynamic_cast<FunctionType*>(add->rhs.get())->lhs = m_int_type;
    dynamic_cast<FunctionType*>(add->rhs.get())->rhs = m_int_type;
    m_context["add"] = add;
}

std::shared_ptr<BabyType> Typer::Infer(const std::shared_ptr<Expression>& p_exp) {
    return nullptr;
}
