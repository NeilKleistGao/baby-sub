#ifndef BABY_SUB_BABY_TYPE_H
#define BABY_SUB_BABY_TYPE_H

#include <string>
#include <memory>
#include <vector>

struct BabyType {
    int level = 0;

    virtual std::string ToString() = 0;
};

struct PrimitiveType : public BabyType {
    std::string name;

    std::string ToString() override { return name; }
};

struct FunctionType : public BabyType {
    std::shared_ptr<BabyType> lhs;
    std::shared_ptr<BabyType> rhs;

    std::string ToString() override { return lhs->ToString() + " -> " + rhs->ToString(); }
};

struct TypeVariable : public BabyType {
    static int s_count;
    int id;
    std::vector<std::shared_ptr<TypeVariable>> lower_bounds;
    std::vector<std::shared_ptr<TypeVariable>> upper_bounds;

    TypeVariable() : id(s_count++) {}
    std::string ToString() override { return "a" + std::to_string(id); }
};

#endif//BABY_SUB_BABY_TYPE_H
