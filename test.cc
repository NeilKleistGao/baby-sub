#include <gtest/gtest.h>

#include "parser/lex.h"

std::string DoTest(const std::string& p_exp) {
    Lex lex{};
    auto tokens = lex.Parse(p_exp + " ");
    return "";
}

TEST(SubAlgorithm, Basic) {
    EXPECT_EQ(DoTest("42"), "int");
    EXPECT_EQ(DoTest("\\x = 42"), "T -> int");
    EXPECT_EQ(DoTest("\\x = x"), "'a -> 'a");
    EXPECT_EQ(DoTest("\\x = (x 42)"), "(int -> 'a) -> 'a");
    EXPECT_EQ(DoTest("((\\x = x) 42)"), "int");
    EXPECT_EQ(DoTest("\\f= \\x = f (f x)"), "('a ∨ 'b -> 'a) -> 'b -> 'a");
    EXPECT_EQ(DoTest("let t = \\f = \\x = f (f x) in t"), "('a ∨ 'b -> 'a) -> 'b -> 'a");
}
