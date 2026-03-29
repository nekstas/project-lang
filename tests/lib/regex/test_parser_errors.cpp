#include <catch2/catch_test_macros.hpp>

#include "../../../src/lib/errors/errors.h"
#include "../../../src/lib/regex/parser/parser.h"
#include "../../../src/lib/regex/visitors/ast_printer.h"

TEST_CASE("lib::regex::Parser errors") {
    lib::regex::Parser parser;
    lib::regex::visitors::AstPrinter ast_printer(0, false);
    auto make_ast = [&parser, &ast_printer](const std::string& code) {
        auto ptr = parser.Parse(code);
        return ast_printer.ToString(ptr.get());
    };

    SECTION("Parses the full string") {
        REQUIRE_THROWS_AS(make_ast("a)"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a|"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast(")"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("|"), lib::regex::errors::ParserError);
    }
    SECTION("Without close bracket") {
        REQUIRE_THROWS_AS(make_ast("(a"), lib::regex::errors::ParserError);
    }
    SECTION("Empty brackets") {
        REQUIRE_THROWS_AS(make_ast("()"), lib::regex::errors::ParserError);
    }
    SECTION("Alternative without brackets") {
        REQUIRE_THROWS_AS(make_ast("a|b"), lib::regex::errors::ParserError);
    }
    SECTION("Multiple repeat modifiers are unsupported") {
        REQUIRE_THROWS_AS(make_ast("a**"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a*+"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a*?"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a+*"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a++"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a+?"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a?*"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a?+"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("a??"), lib::regex::errors::ParserError);
    }
    SECTION("Repeat empty sequence") {
        REQUIRE_THROWS_AS(make_ast("()*"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("()+"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("()?"), lib::regex::errors::ParserError);
    }
    SECTION("Multiple repeat modifiers with brackets") {
        REQUIRE_THROWS_AS(make_ast("(a*)*"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(a*)+"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(a*)?"), lib::regex::errors::ParserError);
    }
    SECTION("Corner cases with brackets") {
        REQUIRE_THROWS_AS(make_ast("()()"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(()|())"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(|a)"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(b|)"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(|)"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("(()|(()))()(())"), lib::regex::errors::ParserError);
    }
    SECTION("Repeat modifier without repeat body") {
        REQUIRE_THROWS_AS(make_ast("*"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("+"), lib::regex::errors::ParserError);
        REQUIRE_THROWS_AS(make_ast("?"), lib::regex::errors::ParserError);
    }
    SECTION("Backslash in the end of the string") {
        REQUIRE_THROWS_AS(make_ast("\\"), lib::regex::errors::ParserError);
    }
    SECTION("Char set") {
        SECTION("Empty") {
            REQUIRE_THROWS_AS(make_ast("[]"), lib::regex::errors::ParserError);
        }
        SECTION("Triple dash") {
            REQUIRE_THROWS_AS(make_ast("[---]"), lib::regex::errors::ParserError);
        }
        SECTION("Double dash with something else") {
            REQUIRE_THROWS_AS(make_ast("[--a]"), lib::regex::errors::ParserError);
            REQUIRE_THROWS_AS(make_ast("[a--]"), lib::regex::errors::ParserError);
            REQUIRE_THROWS_AS(make_ast("[--\\w]"), lib::regex::errors::ParserError);
            REQUIRE_THROWS_AS(make_ast("[\\w--]"), lib::regex::errors::ParserError);
        }
        SECTION("Range with char class") {
            REQUIRE_THROWS_AS(make_ast("[a-\\w]"), lib::regex::errors::ParserError);
            REQUIRE_THROWS_AS(make_ast("[\\d-b]"), lib::regex::errors::ParserError);
            REQUIRE_THROWS_AS(make_ast("[\\S-\\s]"), lib::regex::errors::ParserError);
        }
        SECTION("Decreasing order") {
            REQUIRE_THROWS_AS(make_ast("[z-a]"), lib::regex::errors::ParserError);
        }
        SECTION("Without close bracket") {
            REQUIRE_THROWS_AS(make_ast("["), lib::regex::errors::ParserError);
            REQUIRE_THROWS_AS(make_ast("[\\]"), lib::regex::errors::ParserError);
        }
        SECTION("Closed bracket as a char") {
            REQUIRE_THROWS_AS(make_ast("[]]"), lib::regex::errors::ParserError);
        }
    }
}
