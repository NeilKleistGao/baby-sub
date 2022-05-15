#include <iostream>
#include <gtest/gtest.h>

#include "parser/lex.h"
#include "parser/parser.h"
#include "typer.h"
#include "simplifier.h"

std::string DoTest(const std::string& p_exp) {
    Lex lex{};
    auto tokens = lex.Parse(p_exp + " ");

    Parser parser{std::move(tokens)};
    auto syntax_tree = parser.Parse();
    if (syntax_tree == nullptr) {
        return "";
    }

    Typer typer{};
    auto baby_type = typer.Infer(syntax_tree);
    if (baby_type == nullptr) {
        return "";
    }
    std::cout << "Baby Type: " << baby_type->ToString() << std::endl;

    auto compacted = Simplifier::Compact(baby_type);
    if (compacted == nullptr) {
        return "";
    }
    std::cout << "Compacted Type: " << compacted->ToString() << std::endl;

    return baby_type->ToString();
}

TEST(SubAlgorithm, Basic) {
    EXPECT_EQ(DoTest("42"), "int");
    EXPECT_EQ(DoTest("\\x = 42"), "T -> int");
    EXPECT_EQ(DoTest("\\x = x"), "'a -> 'a");
    EXPECT_EQ(DoTest("\\x = (x 42)"), "(int -> 'a) -> 'a");
    EXPECT_EQ(DoTest("((\\x = x) 42)"), "int");
    EXPECT_EQ(DoTest("\\f= \\x = (f (f x))"), "('a v 'b -> 'a) -> 'b -> 'a");
    EXPECT_EQ(DoTest("let t = \\f = \\x = (f (f x)) in t"), "('a v 'b -> 'a) -> 'b -> 'a");
}
