#ifndef BABY_SUB_SIMPLIFIER_H
#define BABY_SUB_SIMPLIFIER_H

#include <unordered_set>
#include <optional>
#include "baby_type.h"

struct CompactType {
    std::unordered_set<std::shared_ptr<TypeVariable>> variables;
    std::unordered_set<std::shared_ptr<PrimitiveType>> primitive;
    std::optional<std::pair<std::shared_ptr<CompactType>, std::shared_ptr<CompactType>>> function;

    std::string ToString() const;
};

class Simplifier {
public:
    static std::shared_ptr<CompactType> Compact(const std::shared_ptr<BabyType>& p_term, bool p_polarity = true);
private:
    static std::shared_ptr<CompactType> Merge(const std::shared_ptr<CompactType>& p_lhs, const std::shared_ptr<CompactType>& p_rhs, bool p_polarity);
};

#endif//BABY_SUB_SIMPLIFIER_H
