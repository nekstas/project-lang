#include <catch2/catch_test_macros.hpp>

#include "../../../src/lib/errors/errors.h"
#include "utils.h"

TEST_CASE("lang::regex::Parser errors") {
    lang::regex::Parser parser;
    lang::regex::visitors::AstPrinter ast_printer(0, false);
    auto make_ast = [&parser, &ast_printer](const std::string& code) {
        auto ptr = parser.Parse(code);
        return ast_printer.ToString(ptr.get());
    };

    SECTION("Parses the full string") {
        REQUIRE_THROWS_AS(make_ast("a)"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a|"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast(")"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("|"), lang::regex::errors::ParserError);
    }
    SECTION("Without close bracket") {
        REQUIRE_THROWS_AS(make_ast("(a"), lang::regex::errors::ParserError);
    }
    SECTION("Empty brackets") {
        REQUIRE_THROWS_AS(make_ast("()"), lang::regex::errors::ParserError);
    }
    SECTION("Alternative without brackets") {
        REQUIRE_THROWS_AS(make_ast("a|b"), lang::regex::errors::ParserError);
    }
    SECTION("Multiple repeat modifiers are unsupported") {
        REQUIRE_THROWS_AS(make_ast("a**"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a*+"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a*?"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a+*"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a++"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a+?"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a?*"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a?+"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a??"), lang::regex::errors::ParserError);
    }
    SECTION("Repeat empty sequence") {
        REQUIRE_THROWS_AS(make_ast("()*"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("()+"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("()?"), lang::regex::errors::ParserError);
    }
    SECTION("Multiple repeat modifiers with brackets") {
        REQUIRE_THROWS_AS(make_ast("(a*)*"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(a*)+"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(a*)?"), lang::regex::errors::ParserError);
    }
    SECTION("Corner cases with brackets") {
        REQUIRE_THROWS_AS(make_ast("()()"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(()|())"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(|a)"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(b|)"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(|)"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(()|(()))()(())"), lang::regex::errors::ParserError);
    }
    SECTION("Repeat modifier without repeat body") {
        REQUIRE_THROWS_AS(make_ast("*"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("+"), lang::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("?"), lang::regex::errors::ParserError);
    }
    SECTION("Backslash in the end of the string") {
        REQUIRE_THROWS_AS(make_ast("\\"), lang::regex::errors::ParserError);
    }
}
