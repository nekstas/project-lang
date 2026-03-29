#include <catch2/catch_test_macros.hpp>

#include "../../../src/lib/errors/errors.h"
#include "../../../src/lib/regex/parser/parser.h"
#include "../../../src/lib/regex/visitors/ast_printer.h"

TEST_CASE("lib::regex::visitors::AstPrinter") {
    lib::regex::Parser parser;
    lib::regex::visitors::AstPrinter ast_printer(0, false);
    auto make_ast = [&parser, &ast_printer](const std::string& code) {
        auto ptr = parser.Parse(code);
        return ast_printer.ToString(ptr.get());
    };

    SECTION("Empty") {
        REQUIRE(make_ast("") == "[null]");
    }
    SECTION("Just char") {
        REQUIRE(make_ast("a") == "['a']");
    }
    SECTION("Russian char") {
        REQUIRE(make_ast("я") == "[\"я\"]");
        REQUIRE(
            make_ast("Привет мир!") ==
            "[seq][\"П\"][\"р\"][\"и\"][\"в\"][\"е\"][\"т\"][' '][\"м\"][\"и\"][\"р\"]['!'][/seq]");
    }
    SECTION("Simple sequence") {
        REQUIRE(make_ast("abc") == "[seq]['a']['b']['c'][/seq]");
    }
    SECTION("Escape sequences") {
        REQUIRE(make_ast("\\(") == "['(']");
        REQUIRE(make_ast("\\|") == "['|']");
        REQUIRE(make_ast("\\)") == "[')']");
        REQUIRE(make_ast("\\*") == "['*']");
        REQUIRE(make_ast("\\+") == "['+']");
        REQUIRE(make_ast("\\?") == "['?']");
        REQUIRE(make_ast("\\[") == "['[']");
        REQUIRE(make_ast("]") == "[']']");
    }
    SECTION("Bracket symbols") {
        REQUIRE(make_ast("\\(\\)") == "[seq]['('][')'][/seq]");
    }
    SECTION("Special escape sequences") {
        REQUIRE(make_ast("\\\\") == "['\\\\']");
        REQUIRE(make_ast("\\'") == "['\\'']");
        REQUIRE(make_ast("\\n") == "['\\n']");
        REQUIRE(make_ast("\\t") == "['\\t']");
        REQUIRE(make_ast("\\\\\\\\") == "[seq]['\\\\']['\\\\'][/seq]");
    }
    SECTION("Simple alternative") {
        REQUIRE(make_ast("(a|b)") == "[choice]['a']['b'][/choice]");
    }
    SECTION("Only one alternative") {
        REQUIRE(make_ast("(a)") == "['a']");
    }
    SECTION("Many brackets") {
        REQUIRE(make_ast("((((a|b))))") == "[choice]['a']['b'][/choice]");
    }
    SECTION("Recursive") {
        REQUIRE(
            make_ast("((((a|b))|((c))))") == "[choice][choice]['a']['b'][/choice]['c'][/choice]");
        REQUIRE(make_ast("(abc|def)") ==
                "[choice][seq]['a']['b']['c'][/seq][seq]['d']['e']['f'][/seq][/choice]");
    }
    SECTION("Different repeats") {
        REQUIRE(make_ast("a*") == "[repeat *]['a'][/repeat]");
        REQUIRE(make_ast("a+") == "[repeat +]['a'][/repeat]");
        REQUIRE(make_ast("a?") == "[repeat ?]['a'][/repeat]");
    }
    SECTION("Sequence of repeats") {
        REQUIRE(
            make_ast("a*b+c?") ==
            "[seq][repeat *]['a'][/repeat][repeat +]['b'][/repeat][repeat ?]['c'][/repeat][/seq]");
    }
    SECTION("Repeat of choice") {
        REQUIRE(make_ast("(a|b)*c") ==
                "[seq][repeat *][choice]['a']['b'][/choice][/repeat]['c'][/seq]");
    }
    SECTION("Repeat of sequence") {
        REQUIRE(make_ast("c(ab)*") == "[seq]['c'][repeat *][seq]['a']['b'][/seq][/repeat][/seq]");
    }
    SECTION("Repeat of a Russian char") {
        REQUIRE(make_ast("ая+") == "[seq][\"а\"][repeat +][\"я\"][/repeat][/seq]");
        REQUIRE(make_ast("а(я)+") == "[seq][\"а\"][repeat +][\"я\"][/repeat][/seq]");
    }
    SECTION("Special whitespace symbols") {
        REQUIRE(make_ast("\\r") == "['\\r']");
        REQUIRE(make_ast("\\f") == "['\\f']");
        REQUIRE(make_ast("\\v") == "['\\v']");
    }
    SECTION("Special char classes") {
        REQUIRE(make_ast("\\w") == "[char_class \\w]");
        REQUIRE(make_ast("\\W") == "[char_class \\W]");
        REQUIRE(make_ast("\\d") == "[char_class \\d]");
        REQUIRE(make_ast("\\D") == "[char_class \\D]");
        REQUIRE(make_ast("\\s") == "[char_class \\s]");
        REQUIRE(make_ast("\\S") == "[char_class \\S]");
        REQUIRE(make_ast(".") == "[char_class .]");
    }
    SECTION("Char sets") {
        SECTION("Dashes") {
            REQUIRE(make_ast("[-]") == "[char_set]['-'][/char_set]");
            REQUIRE(make_ast("[--]") == "[char_set]['-'][/char_set]");
            REQUIRE(make_ast("[-a]") == "[char_set]['a']['-'][/char_set]");
            REQUIRE(make_ast("[a-]") == "[char_set]['a']['-'][/char_set]");
            REQUIRE(make_ast("[-a-]") == "[char_set]['a']['-'][/char_set]");
            REQUIRE(make_ast("[-a-z-]") == "[char_set]['a'-'z']['-'][/char_set]");
        }
        SECTION("All") {
            REQUIRE(make_ast("[^]") == "[char_set ^][/char_set]");
        }
        SECTION("Simple") {
            REQUIRE(make_ast("[a]") == "[char_set]['a'][/char_set]");
            REQUIRE(make_ast("[a-z]") == "[char_set]['a'-'z'][/char_set]");
            REQUIRE(make_ast("[A-Z]") == "[char_set]['A'-'Z'][/char_set]");
            REQUIRE(make_ast("[a-zA-Z0-9_]") ==
                    "[char_set]['0'-'9']['A'-'Z']['_']['a'-'z'][/char_set]");
        }
        SECTION("Ranges with two chars") {
            REQUIRE(make_ast("[a-bdeg]") == "[char_set]['a']['b']['d']['e']['g'][/char_set]");
            REQUIRE(make_ast("[gdea-b]") == "[char_set]['a']['b']['d']['e']['g'][/char_set]");
        }
        SECTION("Special symbols") {
            REQUIRE(make_ast("[*+?().]") == "[char_set]['('-'+']['.']['?'][/char_set]");
            REQUIRE(make_ast("[[]") == "[char_set]['['][/char_set]");
            REQUIRE(make_ast("[\\]]") == "[char_set][']'][/char_set]");
        }
        SECTION("Char classes") {
            REQUIRE(make_ast("[\\w]") == "[char_set]['0'-'9']['A'-'Z']['_']['a'-'z'][/char_set]");
            REQUIRE(make_ast("[\\d]") == "[char_set]['0'-'9'][/char_set]");
            REQUIRE(make_ast("[\\s]") == "[char_set]['\\t'-'\\r'][' '][/char_set]");
            REQUIRE(make_ast("[\\W]") == "[char_set][(0)-',']['.']['/'][':'-'@']['['-'^']['`']['{'-(255)]['-'][/char_set]");
            REQUIRE(make_ast("[\\D]") == "[char_set][(0)-',']['.']['/'][':'-(255)]['-'][/char_set]");
            REQUIRE(make_ast("[\\S]") == "[char_set][(0)-(8)][(14)-(31)]['!'-',']['.'-(255)]['-'][/char_set]");
            REQUIRE(make_ast("[^\\w]") == "[char_set ^]['0'-'9']['A'-'Z']['_']['a'-'z'][/char_set]");
            REQUIRE(make_ast("[^\\d]") == "[char_set ^]['0'-'9'][/char_set]");
            REQUIRE(make_ast("[^\\s]") == "[char_set ^]['\\t'-'\\r'][' '][/char_set]");
            REQUIRE(make_ast("[^\\W]") == "[char_set ^][(0)-',']['.']['/'][':'-'@']['['-'^']['`']['{'-(255)]['-'][/char_set]");
            REQUIRE(make_ast("[^\\D]") == "[char_set ^][(0)-',']['.']['/'][':'-(255)]['-'][/char_set]");
            REQUIRE(make_ast("[^\\S]") == "[char_set ^][(0)-(8)][(14)-(31)]['!'-',']['.'-(255)]['-'][/char_set]");
        }
        SECTION("Mixed") {
            REQUIRE(make_ast("[\\d?]") == "[char_set]['0'-'9']['?'][/char_set]");
            REQUIRE(make_ast("[?\\d]") == "[char_set]['0'-'9']['?'][/char_set]");
        }
        SECTION("Duplicated chars") {
            REQUIRE(make_ast("[?????]") == "[char_set]['?'][/char_set]");
            REQUIRE(make_ast("[?a?b?c?d?]") == "[char_set]['?']['a'-'d'][/char_set]");
        }
        SECTION("Escape sequences") {
            REQUIRE(make_ast("[\\n\\t]") == "[char_set]['\\t']['\\n'][/char_set]");
        }
        SECTION("Regex priorities") {
            REQUIRE(make_ast("[a-z0]+") == "[repeat +][char_set]['0']['a'-'z'][/char_set][/repeat]");
        }
        SECTION("Negative modifier escape sequence") {
            REQUIRE(make_ast("[^^]") == "[char_set ^]['^'][/char_set]");
            REQUIRE(make_ast("[\\^]") == "[char_set]['^'][/char_set]");
        }
    }
}
