#include "typer.h"

int TypeVariable::s_count = 0;

Typer::Typer() {
    TypeVariable::s_count = 0;
    m_bool_type = std::make_shared<PrimitiveType>();
    m_int_type = std::make_shared<PrimitiveType>();

    m_bool_type->name = "bool";
    m_int_type->name = "int";

    auto add = std::make_shared<FunctionType>();
    add->lhs = m_int_type;
    add->rhs = std::make_shared<FunctionType>();
    dynamic_cast<FunctionType*>(add->rhs.get())->lhs = m_int_type;
    dynamic_cast<FunctionType*>(add->rhs.get())->rhs = m_int_type;
    m_context["add"] = add;
}

std::shared_ptr<BabyType> Typer::Infer(const std::shared_ptr<Expression>& p_exp, int p_level) {
    std::shared_ptr<BabyType> res = nullptr;
    if (dynamic_cast<Literal*>(p_exp.get()) != nullptr) {
        auto* lit = dynamic_cast<Literal*>(p_exp.get());
        if (lit->lit.type == Token::Type::BOOL) {
            res = m_bool_type;
        }
        else {
            res = m_int_type;
        }
    }
    else if (dynamic_cast<Variable*>(p_exp.get()) != nullptr) {
        auto* var = dynamic_cast<Variable*>(p_exp.get());
        if (m_context.find(var->var.name) != m_context.end()) {
            res = m_context[var->var.name];
        }
    }
    else if (dynamic_cast<Lambda*>(p_exp.get()) != nullptr) {
        auto* lambda = dynamic_cast<Lambda*>(p_exp.get());
        auto param = std::make_shared<TypeVariable>();

        m_context[lambda->var->var.name] = param;
        auto body_type = Infer(lambda->body, p_level);
        m_context.erase(lambda->var->var.name);

        auto func = std::make_shared<FunctionType>();
        func->lhs = param;
        func->rhs = body_type;
        res = func;
    }
    else if (dynamic_cast<Application*>(p_exp.get()) != nullptr) {
        auto* app = dynamic_cast<Application*>(p_exp.get());
        auto ret = std::make_shared<TypeVariable>();

        auto func = Infer(app->lambda, p_level);
        auto arg = Infer(app->value, p_level);
        auto func_mirror = std::make_shared<FunctionType>();
        func_mirror->lhs = arg; func_mirror->rhs = ret;
        Constrain(func, func_mirror);

        res = ret;
    }
    else if (dynamic_cast<Let*>(p_exp.get()) != nullptr) {
        auto* let = dynamic_cast<Let*>(p_exp.get());
        auto rhs_type = std::make_shared<PolymorphicType>();
        rhs_type->level = p_level + 1;
        rhs_type->body = Infer(let->rhs, p_level + 1);

        m_context[let->var->var.name] = rhs_type;
        res = Infer(let->body, p_level);
        m_context.erase(let->var->var.name);
    }

    res->level = p_level;
    return res;
}

void Typer::Constrain(const std::shared_ptr<BabyType>& p_lhs, const std::shared_ptr<BabyType>& p_rhs) {
    if (dynamic_cast<FunctionType*>(p_lhs.get()) && dynamic_cast<FunctionType*>(p_rhs.get())) {
        auto* func1 = dynamic_cast<FunctionType*>(p_lhs.get());
        auto* func2 = dynamic_cast<FunctionType*>(p_rhs.get());

        Constrain(func2->lhs, func1->lhs);
        Constrain(func1->rhs, func2->rhs);
    }
    else if (dynamic_cast<TypeVariable*>(p_lhs.get())) {
        auto* lhs = dynamic_cast<TypeVariable*>(p_lhs.get());
        lhs->upper_bounds.push_back(p_rhs);
        for (auto& lb : lhs->lower_bounds) {
            Constrain(lb, p_rhs);
        }
    }
    else if (dynamic_cast<TypeVariable*>(p_rhs.get())) {
        auto* rhs = dynamic_cast<TypeVariable*>(p_rhs.get());
        rhs->lower_bounds.push_back(p_lhs);
        for (auto& ub : rhs->upper_bounds) {
            Constrain(p_lhs, ub);
        }
    }
}