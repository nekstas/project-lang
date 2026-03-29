#include <catch2/catch_test_macros.hpp>

#include "../../../src/lib/errors/errors.h"
#include "../../../src/lib/regex/parser/parser.h"
#include "../../../src/lib/regex/visitors/formatter.h"

TEST_CASE("lib::regex::visitors::Formatter") {
    lib::regex::Parser parser;
    lib::regex::visitors::Formatter formatter;
    auto make_ast = [&parser, &formatter](const std::string& code) {
        auto ptr = parser.Parse(code);
        auto repr = formatter.ToString(ptr.get());
        auto ptr2 = parser.Parse(repr);
        auto repr2 = formatter.ToString(ptr2.get());
        REQUIRE(repr == repr2);
        return repr;
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
        REQUIRE(make_ast("\\[") == "\\[");
        REQUIRE(make_ast("\\]") == "]");
        REQUIRE(make_ast("]") == "]");
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
    SECTION("Special whitespace symbols") {
        REQUIRE(make_ast("\\r") == "\\r");
        REQUIRE(make_ast("\\f") == "\\f");
        REQUIRE(make_ast("\\v") == "\\v");
    }
    SECTION("Special char classes") {
        REQUIRE(make_ast("\\w") == "\\w");
        REQUIRE(make_ast("\\W") == "\\W");
        REQUIRE(make_ast("\\d") == "\\d");
        REQUIRE(make_ast("\\D") == "\\D");
        REQUIRE(make_ast("\\s") == "\\s");
        REQUIRE(make_ast("\\S") == "\\S");
        REQUIRE(make_ast(".") == ".");
    }
    SECTION("Char sets") {
        SECTION("Dashes") {
            REQUIRE(make_ast("[-]") == "[-]");
            REQUIRE(make_ast("[--]") == "[-]");
            REQUIRE(make_ast("[-a]") == "[a-]");
            REQUIRE(make_ast("[a-]") == "[a-]");
            REQUIRE(make_ast("[-a-]") == "[a-]");
            REQUIRE(make_ast("[-a-z-]") == "[a-z-]");
        }
        SECTION("All") {
            REQUIRE(make_ast("[^]") == "[^]");
        }
        SECTION("Simple") {
            REQUIRE(make_ast("[a]") == "[a]");
            REQUIRE(make_ast("[a-z]") == "[a-z]");
            REQUIRE(make_ast("[A-Z]") == "[A-Z]");
            REQUIRE(make_ast("[a-zA-Z0-9_]") == "[0-9A-Z_a-z]");
        }
        SECTION("Ranges with two chars") {
            REQUIRE(make_ast("[a-bdeg]") == "[abdeg]");
            REQUIRE(make_ast("[gdea-b]") == "[abdeg]");
        }
        SECTION("Special symbols") {
            REQUIRE(make_ast("[*+?().]") == "[(-+.?]");
            REQUIRE(make_ast("[[]") == "[[]");
            REQUIRE(make_ast("[\\]]") == "[\\]]");
        }
        SECTION("Char classes") {
            REQUIRE(make_ast("[\\w]") == "[0-9A-Z_a-z]");
            REQUIRE(make_ast("[\\d]") == "[0-9]");
            REQUIRE(make_ast("[\\s]") == "[\\t-\\r ]");
            REQUIRE(make_ast("[\\W]") == "[\\x00-,./:-@[-^`{-\\xFF-]");
            REQUIRE(make_ast("[\\D]") == "[\\x00-,./:-\\xFF-]");
            REQUIRE(make_ast("[\\S]") == "[\\x00-\\x08\\x0E-\\x1F!-,.-\\xFF-]");
            REQUIRE(make_ast("[^\\w]") == "[^0-9A-Z_a-z]");
            REQUIRE(make_ast("[^\\d]") == "[^0-9]");
            REQUIRE(make_ast("[^\\s]") == "[^\\t-\\r ]");
            REQUIRE(make_ast("[^\\W]") == "[^\\x00-,./:-@[-^`{-\\xFF-]");
            REQUIRE(make_ast("[^\\D]") == "[^\\x00-,./:-\\xFF-]");
            REQUIRE(make_ast("[^\\S]") == "[^\\x00-\\x08\\x0E-\\x1F!-,.-\\xFF-]");
        }
        SECTION("Mixed") {
            REQUIRE(make_ast("[\\d?]") == "[0-9?]");
            REQUIRE(make_ast("[?\\d]") == "[0-9?]");
        }
        SECTION("Duplicated chars") {
            REQUIRE(make_ast("[?????]") == "[?]");
            REQUIRE(make_ast("[?a?b?c?d?]") == "[?a-d]");
        }
        SECTION("Escape sequences") {
            REQUIRE(make_ast("[\\n\\t]") == "[\\t\\n]");
        }
        SECTION("Regex priorities") {
            REQUIRE(make_ast("[a-z0]+") == "[0a-z]+");
        }
        SECTION("Negative modifier escape sequence") {
            REQUIRE(make_ast("[^^]") == "[^^]");
            REQUIRE(make_ast("[\\^]") == "[\\^]");
        }
    }
}
