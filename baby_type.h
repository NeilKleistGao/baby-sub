#ifndef BABY_SUB_BABY_TYPE_H
#define BABY_SUB_BABY_TYPE_H

#include <string>
#include <memory>

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

#endif//BABY_SUB_BABY_TYPE_H
