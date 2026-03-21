#include <catch2/catch_test_macros.hpp>

#include "../../../src/lib/errors/errors.h"
#include "../../../src/lib/regex/visitors/formatter.h"
#include "utils.h"

TEST_CASE("lang::regex::visitors::Formatter") {
    lang::regex::Parser parser;
    lang::regex::visitors::Formatter formatter;
    auto make_ast = [&parser, &formatter](const std::string& code) {
        auto ptr = parser.Parse(code);
        return formatter.ToString(ptr.get());
    };

    SECTION("Empty") {
        REQUIRE(make_ast("").empty());
    }
    SECTION("Just char") {
        REQUIRE(make_ast("a") == "a");
    }
    SECTION("Russian char") {
        REQUIRE(make_ast("я") == "я");
        REQUIRE(make_ast("Привет мир!") == "Привет мир!");
    }
    SECTION("Simple sequence") {
        REQUIRE(make_ast("abc") == "abc");
    }
    SECTION("Escape sequences") {
        REQUIRE(make_ast("\\(") == "\\(");
        REQUIRE(make_ast("\\|") == "\\|");
        REQUIRE(make_ast("\\)") == "\\)");
        REQUIRE(make_ast("\\*") == "\\*");
        REQUIRE(make_ast("\\+") == "\\+");
        REQUIRE(make_ast("\\?") == "\\?");
    }
    SECTION("Bracket symbols") {
        REQUIRE(make_ast("\\(\\)") == "\\(\\)");
    }
    SECTION("Special escape sequences") {
        REQUIRE(make_ast("\\\\") == "\\\\");
        REQUIRE(make_ast("\\'") == "'");
        REQUIRE(make_ast("\\n") == "\\n");
        REQUIRE(make_ast("\\t") == "\\t");
        REQUIRE(make_ast("\\\\\\\\") == "\\\\\\\\");
    }
    SECTION("Simple alternative") {
        REQUIRE(make_ast("(a|b)") == "(a|b)");
    }
    SECTION("Only one alternative") {
        REQUIRE(make_ast("(a)") == "a");
    }
    SECTION("Many brackets") {
        REQUIRE(make_ast("((((a|b))))") == "(a|b)");
    }
    SECTION("Recursive") {
        REQUIRE(make_ast("((((a|b))|((c))))") == "((a|b)|c)");
        REQUIRE(make_ast("(abc|def)") == "(abc|def)");
    }
    SECTION("Different repeats") {
        REQUIRE(make_ast("a*") == "a*");
        REQUIRE(make_ast("a+") == "a+");
        REQUIRE(make_ast("a?") == "a?");
    }
    SECTION("Sequence of repeats") {
        REQUIRE(make_ast("a*b+c?") == "a*b+c?");
    }
    SECTION("Repeat of choice") {
        REQUIRE(make_ast("(a|b)*c") == "(a|b)*c");
    }
    SECTION("Repeat of sequence") {
        REQUIRE(make_ast("c(ab)*") == "c(ab)*");
    }
    SECTION("Repeat of a Russian char") {
        REQUIRE(make_ast("ая+") == "ая+");
        REQUIRE(make_ast("а(я)+") == "ая+");
    }
}
