#include "simplifier.h"

std::shared_ptr<CompactType> Simplifier::Compact(const std::shared_ptr<BabyType> &p_term, bool p_polarity) {
    auto res = std::make_shared<CompactType>();
    if (dynamic_cast<FunctionType*>(p_term.get()) != nullptr) {
        auto func = std::dynamic_pointer_cast<FunctionType>(p_term);
        res->function = std::make_pair<std::shared_ptr<CompactType>, std::shared_ptr<CompactType>>(Compact(func->lhs, !p_polarity),
                                                                                                   Compact(func->rhs, p_polarity));
    }
    else if (dynamic_cast<PrimitiveType*>(p_term.get()) != nullptr) {
        auto prim = std::dynamic_pointer_cast<PrimitiveType>(p_term);
        res->primitive.insert(prim);
    }
    else if (dynamic_cast<TypeVariable*>(p_term.get()) != nullptr) {
        auto type = std::dynamic_pointer_cast<TypeVariable>(p_term);
        auto bounds = (p_polarity) ? type->lower_bounds : type->upper_bounds;
        res->variables.insert(type);

        for (const auto& bd : bounds) {
            auto com_bd = Compact(bd, p_polarity);
            res = Merge(res, com_bd, p_polarity);
        }
    }

    return res;
}

std::shared_ptr<CompactType> Simplifier::Merge(const std::shared_ptr<CompactType>& p_lhs, const std::shared_ptr<CompactType>& p_rhs, bool p_polarity) {
    auto res = p_lhs;
    for (const auto& v : p_rhs->variables) {
        res->variables.insert(v);
    }
    for (const auto& p : p_rhs->primitive) {
        res->primitive.insert(p);
    }

    if (res->function.has_value() && p_rhs->function.has_value()) {
        res->function = std::make_pair(Merge(res->function->first, p_rhs->function->first, !p_polarity),
                                       Merge(res->function->second, p_rhs->function->second, p_polarity));
    }
    else if (p_rhs->function.has_value()) {
        res->function = p_rhs->function;
    }

    return res;
}

std::string CompactType::ToString() const {
    std::string str = "";

    for (const auto& v : variables) {
        str += v->ToString() + ", ";
    }
    for (const auto& p : primitive) {
        str += p->ToString() + ", ";
    }

    if (function.has_value()) {
        str += function->first->ToString() + " -> " + function->second->ToString() + ", ";
    }

    return (str.empty()) ? "<>" : "<" + str.substr(0, str.length() - 2) + ">";
}
